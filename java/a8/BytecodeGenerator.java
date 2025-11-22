package bytecode;

import java.util.ArrayDeque;
import java.util.Deque;

import ast.Node;
import ast.expressions.*;
import ast.statements.*;
import ast.types.*;
import bytecode.frames.FrameTracker;
import bytecode.instructions.*;
import constrainer.types.BoolType;
import visitor.Visitor;

public class BytecodeGenerator implements Visitor<Void, BytecodeGeneratorException> {

    private final Program program;
    private final FrameTracker frames;

    private final Deque<LoopLabels> loopStack;

    private int labelCounter;
    private boolean sessionFrameOpen;

    private record LoopLabels(String continueLabel, String breakLabel) {
    }

    public BytecodeGenerator() {
        this(new Program());
    }

    public BytecodeGenerator(Program program) {
        this.program = program;
        this.frames = new FrameTracker();
        this.loopStack = new ArrayDeque<>();
        this.labelCounter = 0;
        this.sessionFrameOpen = false;
    }

    public Program getProgram() {
        return this.program;
    }

    private void ensureSessionFrame() {
        if (!this.sessionFrameOpen) {
            this.frames.openFrame();
            this.sessionFrameOpen = true;
        }
    }

    private String newLabel(String prefix) {
        return String.format("%s_%d", prefix, ++labelCounter);
    }

    private void pushLoop(String continueLabel, String breakLabel) {
        this.loopStack.push(new LoopLabels(continueLabel, breakLabel));
    }

    private void popLoop() {
        this.loopStack.pop();
    }

    private LoopLabels currentLoop(String keyword) throws BytecodeGeneratorException {
        if (this.loopStack.isEmpty()) {
            throw new BytecodeGeneratorException(String.format("'%s' used outside of a loop", keyword));
        }

        return this.loopStack.peek();
    }

    public Program compile(Node ast) throws BytecodeGeneratorException {
        this.frames.openFrame();
        ast.accept(this);
        this.frames.closeFrame();

        this.program.emit(new Halt());

        // this.program.assertNoUnresolvedBranches();

        return this.program;
    }

    public int compileStatement(Node ast) throws BytecodeGeneratorException {
        // REPL mode needs this
        this.ensureSessionFrame();

        int currentSize = this.program.size();
        ast.accept(this);

        return currentSize;
    }

    @Override
    public Void visit(IntLiteralNode node) throws BytecodeGeneratorException {
        this.program.emit(new Lit(node.getValue()));

        return null;
    }

    @Override
    public Void visit(BinaryNode node) throws BytecodeGeneratorException {
        node.getLeft().accept(this);
        node.getRight().accept(this);

        switch (node.getOperator()) {
            case PLUS:
                this.program.emit(new Add());
                break;
            case MINUS:
                this.program.emit(new Sub());
                break;
            case STAR:
                this.program.emit(new Mul());
                break;
            case SLASH:
                this.program.emit(new Div());
                break;
            case LE:
                this.program.emit(new Le());
                break;
            case LT:
                this.program.emit(new Lt());
                break;
            case GT:
                this.program.emit(new Gt());
                break;
            case GE:
                this.program.emit(new Ge());
                break;
            case EQ:
                this.program.emit(new Eq());
                break;
            case NEQ:
                this.program.emit(new Neq());
                break;
            case AND:
                this.program.emit(new And());
                break;
            case OR:
                this.program.emit(new Or());
                break;
            default:
                throw new BytecodeGeneratorException(
                        String.format("No instruction exists for op: %s", node.getOperator()));
        }

        return null;
    }

    @Override
    public Void visit(PrintStmtNode node) throws BytecodeGeneratorException {
        ExpressionNode expr = node.getExpression();
        expr.accept(this);

        if (expr.getType() == BoolType.INSTANCE) {
            program.emit(new PrintBool());
        } else {
            program.emit(new Print());
        }

        return null;
    }

    @Override
    public Void visit(ExpressionStmtNode node) throws BytecodeGeneratorException {
        node.getExpression().accept(this);

        return null;
    }

    @Override
    public Void visit(VarDeclNode node) throws BytecodeGeneratorException {
        int slot = this.frames.getFrameSize();
        node.setFrameOffset(slot);
        this.frames.changeFrame(1);

        this.program.emit(new Decl());

        ExpressionNode initializer = node.getInitializer();
        if (initializer != null) {
            initializer.accept(this);
            this.program.emit(new Store(slot));
        }

        return null;
    }

    @Override
    public Void visit(AssignNode node) throws BytecodeGeneratorException {
        VarDeclNode decl = node.getIdentifier().getBinding();
        int slot = decl.getFrameOffset();

        node.getExpression().accept(this);

        this.program.emit(new Store(slot));

        return null;
    }

    @Override
    public Void visit(IdentifierNode node) throws BytecodeGeneratorException {
        VarDeclNode decl = node.getBinding();
        int slot = decl.getFrameOffset();

        this.program.emit(new Load(slot));

        return null;
    }

    @Override
    public Void visit(IntTypeNode node) throws BytecodeGeneratorException {
        // intentional no-op; there's nothing to do with the type node
        return null;
    }

    @Override
    public Void visit(BlockNode node) throws BytecodeGeneratorException {
        this.frames.openBlock();

        for (StatementNode stmt : node.getStatements()) {
            stmt.accept(this);
        }

        int localsCount = this.frames.closeBlock();

        if (localsCount > 0) {
            this.program.emit(new Pop(localsCount));
        }

        return null;
    }

    @Override
    public Void visit(BooleanLiteralNode node) throws BytecodeGeneratorException {
        this.program.emit(new Lit(node.getValue() ? 1 : 0));

        return null;
    }

    @Override
    public Void visit(BooleanTypeNode node) throws BytecodeGeneratorException {
        // intentional no-op; there's nothing to do with the type node
        return null;
    }

    @Override
    public Void visit(IfStatementNode node) throws BytecodeGeneratorException {
        node.getCondition().accept(this);

        String elseLabel = this.newLabel("else");
        String endLabel = this.newLabel("if_end");

        this.program.emit(new FalseBranch(elseLabel));

        node.getThenBlock().accept(this);
        this.program.emit(new Goto(endLabel));

        this.program.emit(new Label(elseLabel));

        if (node.hasElse()) {
            node.getElseBlock().accept(this);
        }

        this.program.emit(new Label(endLabel));

        return null;
    }

    @Override
    public Void visit(WhileNode node) throws BytecodeGeneratorException {
        String conditionLabel = this.newLabel("while");
        String endLabel = this.newLabel("while_end");

        this.program.emit(new Label(conditionLabel));

        node.getCondition().accept(this);
        this.program.emit(new FalseBranch(endLabel));

        this.pushLoop(conditionLabel, endLabel);
        try {
            node.getBody().accept(this);
        } finally {
            this.popLoop();
        }
        this.program.emit(new Goto(conditionLabel));

        this.program.emit(new Label(endLabel));

        return null;
    }

    @Override
    public Void visit(FromNode node) throws BytecodeGeneratorException {
        this.frames.openBlock();

        if (node.getInit() != null) {
            node.getInit().accept(this);
        }

        String conditionLabel = this.newLabel("from_cond");
        String updateLabel = this.newLabel("from_update");
        String endLabel = this.newLabel("from_end");

        this.program.emit(new Label(conditionLabel));
        node.getCondition().accept(this);
        this.program.emit(new FalseBranch(endLabel));

        this.pushLoop(updateLabel, endLabel);
        try {
            if (node.getBody() != null) {
                node.getBody().accept(this);
            }

            this.program.emit(new Label(updateLabel));
            if (node.getUpdate() != null) {
                node.getUpdate().accept(this);
            }

            this.program.emit(new Goto(conditionLabel));
        } finally {
            this.popLoop();
        }

        this.program.emit(new Label(endLabel));

        int localsToPop = this.frames.closeBlock();
        if (localsToPop > 0) {
            this.program.emit(new Pop(localsToPop));
        }

        return null;
    }

    @Override
    public Void visit(BreakNode node) throws BytecodeGeneratorException {
        LoopLabels labels = this.currentLoop("break");
        this.program.emit(new Goto(labels.breakLabel()));

        return null;
    }

    @Override
    public Void visit(ContinueNode node) throws BytecodeGeneratorException {
        LoopLabels labels = this.currentLoop("continue");
        this.program.emit(new Goto(labels.continueLabel()));

        return null;
    }
}
