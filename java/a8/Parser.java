package parser;

import static lexer.TokenKind.*;

import java.io.IOException;
import java.util.*;

import ast.Node;
import ast.expressions.*;
import ast.statements.*;
import ast.types.*;
import lexer.*;

public class Parser {
    private ILexer lexer;
    private Token current;
    private Token previous;

    public Parser(ILexer lexer) throws ParseException {
        this.lexer = lexer;

        this.advance();
    }

    public Node parse() throws ParseException {
        return parseProgram();
    }

    /**
     * Utility Methods
     */
    private void advance() throws ParseException {
        this.previous = this.current;
        try {
            this.current = this.lexer.nextToken();
        } catch (IOException e) {
            throw new ParseException(e.getMessage());
        }
    }

    private Token expect(TokenKind expected) throws ParseException {
        if (this.current.getTokenKind() == expected) {
            Token consumed = this.current;
            this.advance();

            return consumed;
        } else {
            throw new ParseException(this.current, expected);
        }
    }

    private boolean match(TokenKind... expected) {
        return List.of(expected).contains(this.current.getTokenKind());
    }

    private boolean isDeclStart() {
        return this.match(T_INT, T_BOOL);
    }

    /**
     * PROGRAM = BLOCK 'eof'
     */
    private Node parseProgram() throws ParseException {
        Node result = this.parseBlock();

        expect(EOF);
        return result;
    }

    /**
     * BLOCK = DECL_STMT* STMT*
     */
    private BlockNode parseBlock() throws ParseException {
        final boolean hasOpeningBrace = this.match(LBRACE);

        final Token openingBraceToken;
        if (hasOpeningBrace) {
            openingBraceToken = this.expect(LBRACE);
        } else {
            openingBraceToken = new Token(LBRACE, "{");
        }

        List<StatementNode> stmts = new ArrayList<>();
        while (this.isDeclStart()) {
            stmts.add(this.parseDeclStatement());
        }

        TokenKind blockEndToken = hasOpeningBrace ? RBRACE : EOF;
        while (!this.match(blockEndToken)) {
            stmts.add(this.parseStatement());
        }

        if (hasOpeningBrace) {
            this.expect(blockEndToken);
        }

        return new BlockNode(openingBraceToken, stmts);
    }

    /**
     * DECL_STMT = TYPE ID ('=' EXPR)?
     */
    private VarDeclNode parseDeclStatement() throws ParseException {
        TypeNode type = this.parseType();
        IdentifierNode id = this.parseIdentifier();
        ExpressionNode expr = null;

        if (this.match(ASSIGN)) {
            this.advance();

            expr = this.parseExpression();
        }

        return new VarDeclNode(type, id, expr);
    }

    /**
     * TYPE = 'int' | 'bool'
     */
    private TypeNode parseType() throws ParseException {
        switch (this.current.getTokenKind()) {
            case T_INT: {
                Token token = this.current;
                this.advance();

                return new IntTypeNode(token);
            }
            case T_BOOL: {
                Token token = this.current;
                this.advance();

                return new BooleanTypeNode(token);
            }
            default: {
                throw new ParseException(current, T_INT);
            }
        }

    }

    /**
     * ID = '<id>'
     */
    private IdentifierNode parseIdentifier() throws ParseException {
        Token id = this.current;
        this.expect(IDENTIFIER);

        return new IdentifierNode(id);
    }

    /*
     * STATEMENT = PRINT_STMT | IF_STMT | WHILE_STMT | FROM_STMT | BREAK_STMT |
     * CONTINUE_STMT | ASSIGN_STMT | EXPR
     */
    private StatementNode parseStatement() throws ParseException {
        switch (this.current.getTokenKind()) {
            case PRINT: {
                return this.parsePrintStatement();
            }
            case IF: {
                return this.parseIfStatement();
            }
            case WHILE: {
                return this.parseWhileStatement();
            }
            case FROM: {
                return this.parseFromStatement();
            }
            case BREAK: {
                return this.parseBreakStatement();
            }
            case CONTINUE: {
                return this.parseContinueStatement();
            }
            case IDENTIFIER: {
                return this.parseAssignStatement();
            }
            default: {
                return new ExpressionStmtNode(this.current, this.parseExpression());
            }

        }
    }

    /**
     * PRINT_STMT = 'print' EXPR
     */
    private PrintStmtNode parsePrintStatement() throws ParseException {
        Token printToken = this.current;
        this.advance();

        ExpressionNode expression = this.parseExpression();

        return new PrintStmtNode(printToken, expression);
    }

    /**
     * IF_STMT = 'if' '(' EXPR ')' BLOCK ('else' BLOCK)?
     */
    private IfStatementNode parseIfStatement() throws ParseException {
        Token ifToken = this.current;
        this.advance();

        this.expect(LPAREN);
        ExpressionNode condition = this.parseExpression();
        this.expect(RPAREN);

        BlockNode thenBlock = this.parseBlock();

        BlockNode elseBlock = null;
        if (this.match(ELSE)) {
            this.advance();
            elseBlock = this.parseBlock();
        }

        return new IfStatementNode(ifToken, condition, thenBlock, elseBlock);
    }

    /**
     * WHILE_STMT = 'while' '(' EXPR ')' BLOCK
     */
    private WhileNode parseWhileStatement() throws ParseException {
        Token whileToken = this.current;
        this.advance();

        this.expect(LPAREN);
        ExpressionNode expr = this.parseExpression();
        this.expect(RPAREN);

        BlockNode block = this.parseBlock();

        return new WhileNode(whileToken, expr, block);
    }

    /**
     * FROM_STMT = 'from' '(' VAR_DECL_STMT ';' EXPR ';' STMT ')' BLOCK
     */
    private FromNode parseFromStatement() throws ParseException {
        Token fromToken = this.current;
        this.advance();

        this.expect(LPAREN);
        StatementNode init = this.parseDeclStatement();
        this.expect(SEMICOLON);

        ExpressionNode condition = this.parseExpression();
        this.expect(SEMICOLON);

        StatementNode update = this.parseStatement();
        this.expect(RPAREN);

        BlockNode body = this.parseBlock();

        return new FromNode(fromToken, init, condition, update, body);
    }

    /**
     * BREAK_STMT = 'break'
     */
    private BreakNode parseBreakStatement() throws ParseException {
        Token breakToken = this.current;
        this.advance();

        return new BreakNode(breakToken);
    }

    /**
     * CONTINUE_STMT = 'continue'
     */
    private ContinueNode parseContinueStatement() throws ParseException {
        Token continueToken = this.current;
        this.advance();

        return new ContinueNode(continueToken);
    }

    /**
     * ASSIGN_STMT = ID '=' EXPR
     */
    private AssignNode parseAssignStatement() throws ParseException {
        IdentifierNode id = this.parseIdentifier();

        this.expect(ASSIGN);

        ExpressionNode expr = this.parseExpression();

        return new AssignNode(id, expr);
    }

    /**
     * EXPR = LOGICAL_OR
     */
    private ExpressionNode parseExpression() throws ParseException {
        return this.parseLogicalOr();
    }

    /**
     * LOGICAL_OR = LOGICAL_AND ('|' LOGICAL_AND)*
     */
    private ExpressionNode parseLogicalOr() throws ParseException {
        return this.parseBinaryExpression(this::parseLogicalAnd, OR);
    }

    /**
     * LOGICAL_AND = EQUALITY ('&' EQUALITY)*
     */
    private ExpressionNode parseLogicalAnd() throws ParseException {
        return parseBinaryExpression(this::parseEquality, AND);
    }

    /**
     * EQUALITY = COMPARISON (('==' | '!=') COMPARISON)*
     */
    private ExpressionNode parseEquality() throws ParseException {
        return parseBinaryExpression(this::parseComparison, EQ, NEQ);
    }

    /**
     * COMPARISON = SIMPLE_EXPR (('<' | '<=' | '>' | '>=') SIMPLE_EXPR)*
     */
    private ExpressionNode parseComparison() throws ParseException {
        return this.parseBinaryExpression(this::parseSimpleExpr, LT, LE, GT, GE);
    }

    /**
     * SIMPLE_EXPR = TERM (('+' | '-') TERM)*
     *
     * @throws ParseException
     */
    private ExpressionNode parseSimpleExpr() throws ParseException {
        return this.parseBinaryExpression(this::parseTerm, PLUS, MINUS);
    }

    /**
     * TERM -> FACTOR (('*' | '/') FACTOR)
     *
     * @throws ParseException
     */
    private ExpressionNode parseTerm() throws ParseException {
        return this.parseBinaryExpression(this::parseFactor, STAR, SLASH);
    }

    @FunctionalInterface
    private interface ParseFunction {
        ExpressionNode parse() throws ParseException;
    }

    private ExpressionNode parseBinaryExpression(ParseFunction fn, TokenKind... validTokenKinds) throws ParseException {
        List<TokenKind> validKinds = List.of(validTokenKinds);
        ExpressionNode left = fn.parse();

        while (validKinds.contains(this.current.getTokenKind())) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = fn.parse();

            left = new BinaryNode(opToken, left, right);
        }

        return left;
    }

    /**
     * FACTOR -> <int> | '(' EXPR ')'
     *
     * @throws ParseException
     */
    private ExpressionNode parseFactor() throws ParseException {
        switch (this.current.getTokenKind()) {
            case INT: {
                this.advance();

                // Moved past int so use previous!
                return new IntLiteralNode(this.previous);
            }
            case BOOL: {
                Token lit = this.current;
                this.advance();

                return new BooleanLiteralNode(lit);
            }
            case LPAREN: {
                this.advance();

                ExpressionNode expr = this.parseExpression();
                this.expect(RPAREN);
                return expr;
            }
            case IDENTIFIER: {
                return this.parseIdentifier();
            }
            default: {
                throw new ParseException(this.current, INT, BOOL, LPAREN, IDENTIFIER);
            }
        }
    }
}
