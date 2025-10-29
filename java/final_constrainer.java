package constrainer;

import java.util.*;

import ast.Node;
import ast.expressions.*;
import ast.statements.*;
import ast.types.*;
import constrainer.types.*;
import visitor.Visitor;

public class Constrainer implements Visitor<Void, ConstraintException> {

    private final Deque<SymbolTable> scopes;
    private final List<String> errors;

    public Constrainer() {
        this.scopes = new ArrayDeque<>();
        this.errors = new ArrayList<>();
    }

    public void constrain(Node node) throws ConstraintException {
        this.scopes.push(new SymbolTable());

        try {
            node.accept(this);
        } finally {
            this.scopes.pop();
        }

        if (this.hasErrors()) {
            throw new ConstraintException(this.getErrors());
        }
    }

    public boolean hasErrors() {
        return !errors.isEmpty();
    }

    public List<String> getErrors() {
        return Collections.unmodifiableList(this.errors);
    }

    /**
     * Utils
     */
    private void pushScope() {
        this.scopes.push(new SymbolTable());
    }

    private void popScope() {
        this.scopes.pop();
    }

    private VarDeclNode lookup(String id) {
        for (SymbolTable scope : scopes) {
            VarDeclNode decl = scope.get(id);

            if (decl != null) {
                return decl;
            }
        }

        return null;
    }

    /**
     * Visit methods start here
     */
    @Override
    public Void visit(BlockNode node) throws ConstraintException {
        this.pushScope();
        try {
            for (Node stmt : node.getStatements()) {
                if (stmt != null)
                    stmt.accept(this);
            }
        } finally {
            this.popScope();
        }
        return null;
    }

    @Override
    public Void visit(PrintStmtNode node) throws ConstraintException {
        node.getExpression().accept(this);

        return null;
    }

    @Override
    public Void visit(ExpressionStmtNode node) throws ConstraintException {
        node.getExpression().accept(this);

        return null;
    }

    @Override
    public Void visit(IntLiteralNode node) throws ConstraintException {
        // intentional no-op; literals set their own type
        return null;
    }

    @Override
    public Void visit(BooleanLiteralNode node) throws ConstraintException {
        // intentional no-op; literals set their own type
        return null;
    }

    @Override
    public Void visit(BinaryNode node) throws ConstraintException {
        ExpressionNode left = node.getLeft();
        left.accept(this);

        ExpressionNode right = node.getRight();
        right.accept(this);

        // If either side already errored, propagate without adding new errors
        if (left.getType() == ErrorType.INSTANCE || right.getType() == ErrorType.INSTANCE) {
            node.setType(ErrorType.INSTANCE);
            return null;
        }

        switch (node.getOperator()) {
            case PLUS:
            case MINUS:
            case STAR:
            case SLASH: {
                if (left.getType() != IntType.INSTANCE || right.getType() != IntType.INSTANCE) {
                    this.errors.add(String.format("type mismatch in '%s'", node.getToken().getLexeme()));
                    node.setType(ErrorType.INSTANCE);
                } else {
                    node.setType(IntType.INSTANCE);
                }

                return null;
            }

            case LT:
            case GT:
            case LE:
            case GE: {
                if (left.getType() != IntType.INSTANCE || right.getType() != IntType.INSTANCE) {
                    this.errors.add(String.format("type mismatch in '%s'", node.getToken().getLexeme()));
                    node.setType(ErrorType.INSTANCE);
                } else {
                    node.setType(BoolType.INSTANCE);
                }
                return null;
            }

            case EQ:
            case NEQ: {
                if (left.getType() != right.getType()) {
                    this.errors.add(String.format("type mismatch in '%s'", node.getToken().getLexeme()));
                    node.setType(ErrorType.INSTANCE);
                } else {
                    node.setType(BoolType.INSTANCE);
                }
                return null;
            }

            case AND:
            case OR: {
                if (left.getType() != BoolType.INSTANCE || right.getType() != BoolType.INSTANCE) {
                    this.errors.add(String.format("type mismatch in '%s'", node.getToken().getLexeme()));
                    node.setType(ErrorType.INSTANCE);
                } else {
                    node.setType(BoolType.INSTANCE);
                }
                return null;
            }

            default:
                node.setType(ErrorType.INSTANCE);
                return null;
        }
    }

    @Override
    public Void visit(VarDeclNode node) throws ConstraintException {
        String id = node.getIdentifier().getToken().getLexeme();

        if (this.scopes.peek().contains(id)) {
            this.errors.add(String.format("duplicate declaration '%s'", id));
            return null;
        }

        if (node.getInitializer() != null) {
            node.getInitializer().accept(this);

            if (node.getInitializer().getType() != node.getResolvedType()) {
                this.errors.add(String.format("cannot assign %s to %s (%s)",
                        node.getInitializer().getType(), node.getResolvedType(), id));
            }
        }

        this.scopes.peek().put(id, node);
        return null;
    }

    @Override
    public Void visit(IdentifierNode node) throws ConstraintException {
        String id = node.getToken().getLexeme();

        VarDeclNode decl = this.lookup(id);
        if (decl == null) {
            this.errors.add(String.format("undeclared variable '%s'", id));
            node.setType(ErrorType.INSTANCE);
        } else {
            node.setType(decl.getResolvedType());
        }

        return null;
    }

    @Override
    public Void visit(IntTypeNode node) throws ConstraintException {
        // intentional no-op; there's nothing to do with the type node
        return null;
    }

    @Override
    public Void visit(BooleanTypeNode node) throws ConstraintException {
        // intentional no-op; there's nothing to do with the type node
        return null;
    }

    @Override
    public Void visit(AssignNode node) throws ConstraintException {
        String targetId = node.getIdentifier().getToken().getLexeme();

        VarDeclNode decl = this.lookup(targetId);
        if (decl == null) {
            this.errors.add(String.format("undeclared variable '%s'", targetId));
            return null;
        }

        node.getExpression().accept(this);

        if (node.getExpression().getType() != decl.getResolvedType()) {
            this.errors.add(String.format("cannot assign %s to %s (%s)", node.getExpression().getType(),
                    decl.getResolvedType(), targetId));
        }

        return null;
    }

}
