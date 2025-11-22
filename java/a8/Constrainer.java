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
    private int loopDepth;

    public Constrainer() {
        this.scopes = new ArrayDeque<>();
        this.errors = new ArrayList<>();
        this.loopDepth = 0;
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

    private void enterLoop() {
        this.loopDepth++;
    }

    private void exitLoop() {
        this.loopDepth--;
    }

    private boolean inLoop() {
        return this.loopDepth > 0;
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
                if (stmt != null) {
                    stmt.accept(this);
                }
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

    private void createTypeError(BinaryNode parent) {
        this.errors.add(String.format("type mismatch in '%s'", parent.getToken().getLexeme()));
        parent.setType(ErrorType.INSTANCE);
    }

    private boolean checkTypes(BinaryNode parent, Type expectedType) {
        return parent.getLeft().getType() == expectedType && parent.getRight().getType() == expectedType;
    }

    private boolean checkTypesAndError(BinaryNode parent, Type expectedType) {
        boolean typesMatch = this.checkTypes(parent, expectedType);

        if (!typesMatch) {
            this.createTypeError(parent);
        }

        return typesMatch;
    }

    @Override
    public Void visit(BinaryNode node) throws ConstraintException {
        ExpressionNode left = node.getLeft();
        left.accept(this);

        ExpressionNode right = node.getRight();
        right.accept(this);

        switch (node.getOperator()) {
            case PLUS:
            case MINUS:
            case STAR:
            case SLASH: {
                if (this.checkTypesAndError(node, IntType.INSTANCE)) {
                    node.setType(IntType.INSTANCE);
                }
                return null;
            }
            case AND:
            case OR: {
                if (this.checkTypesAndError(node, BoolType.INSTANCE)) {
                    node.setType(BoolType.INSTANCE);
                }
                return null;
            }
            case EQ:
            case NEQ: {
                boolean bothInts = this.checkTypes(node, IntType.INSTANCE);
                boolean bothBools = this.checkTypes(node, BoolType.INSTANCE);

                if (bothInts || bothBools) {
                    node.setType(BoolType.INSTANCE);
                } else {
                    this.createTypeError(node);
                }

                return null;
            }
            case LT:
            case LE:
            case GT:
            case GE: {
                if (this.checkTypesAndError(node, IntType.INSTANCE)) {
                    node.setType(BoolType.INSTANCE);
                }
                return null;
            }
            default: {
                node.setType(ErrorType.INSTANCE);

                return null;
            }

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
                this.errors.add(String.format("cannot assign %s to %s (%s)", node.getInitializer().getType(),
                        node.getResolvedType(), id));
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
            node.setBinding(decl);
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

        node.getIdentifier().setBinding(decl);

        node.getExpression().accept(this);

        if (node.getExpression().getType() != decl.getResolvedType()) {
            this.errors.add(String.format("cannot assign %s to %s (%s)", node.getExpression().getType(),
                    decl.getResolvedType(), targetId));
        }

        return null;
    }

    @Override
    public Void visit(IfStatementNode node) throws ConstraintException {
        ExpressionNode cond = node.getCondition();
        cond.accept(this);

        if (cond.getType() != BoolType.INSTANCE) {
            this.errors.add("if condition must be boolean");
        }

        node.getThenBlock().accept(this);
        if (node.hasElse()) {
            node.getElseBlock().accept(this);
        }

        return null;
    }

    @Override
    public Void visit(WhileNode node) throws ConstraintException {
        ExpressionNode cond = node.getCondition();
        cond.accept(this);

        if (cond.getType() != BoolType.INSTANCE) {
            this.errors.add("while condition must be boolean");
        }

        this.enterLoop();
        try {
            node.getBody().accept(this);
        } finally {
            this.exitLoop();
        }

        return null;
    }

    @Override
    public Void visit(FromNode node) throws ConstraintException {
        this.pushScope();
        try {
            if (node.getInit() != null) {
                node.getInit().accept(this);
            }

            ExpressionNode condition = node.getCondition();
            if (condition != null) {
                condition.accept(this);

                if (condition.getType() != BoolType.INSTANCE) {
                    this.errors.add("from condition must be boolean");
                }
            }

            this.enterLoop();
            try {
                if (node.getBody() != null) {
                    node.getBody().accept(this);
                }

                if (node.getUpdate() != null) {
                    node.getUpdate().accept(this);
                }
            } finally {
                this.exitLoop();
            }
        } finally {
            this.popScope();
        }

        return null;
    }

    @Override
    public Void visit(BreakNode node) throws ConstraintException {
        if (!this.inLoop()) {
            this.errors.add("break not allowed outside of a loop");
        }

        return null;
    }

    @Override
    public Void visit(ContinueNode node) throws ConstraintException {
        if (!this.inLoop()) {
            this.errors.add("continue not allowed outside of a loop");
        }

        return null;
    }

}
