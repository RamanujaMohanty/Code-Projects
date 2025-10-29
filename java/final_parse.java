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

    private void expect(TokenKind expected) throws ParseException {
        if (this.current.getTokenKind() == expected) {
            this.advance();
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

    private boolean isAtBlockEnd() {
        return this.match(EOF, RBRACE);
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
        List<StatementNode> statements = new ArrayList<>();

        boolean isGlobalBlock = this.match(LBRACE);
        Token possibleOpeningBrace = this.current;

        while (this.isDeclStart()) {
            statements.add(this.parseDeclStatement());
        }

        while (!this.isAtBlockEnd()) {
            statements.add(this.parseStatement());
        }

        return new BlockNode(isGlobalBlock ? new Token(LBRACE, "{") : possibleOpeningBrace, statements);
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

    /**
     * STATEMENT = PRINT_STMT | ASSIGN_STMT | EXPR
     */
    private StatementNode parseStatement() throws ParseException {
        switch (this.current.getTokenKind()) {
            case PRINT: {
                return this.parsePrintStatement();
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
        ExpressionNode left = this.parseLogicalAnd();

        while (this.current.getTokenKind() == OR) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = this.parseLogicalAnd();
            left = new BinaryNode(opToken, left, right);
        }

        return left;
    }

    /**
     * LOGICAL_AND = EQUALITY ('&' EQUALITY)*
     */
    private ExpressionNode parseLogicalAnd() throws ParseException {
        ExpressionNode left = this.parseEquality();

        while (this.current.getTokenKind() == AND) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = this.parseEquality();
            left = new BinaryNode(opToken, left, right);
        }

        return left;
    }

    /**
     * EQUALITY = COMPARISON (('==' | '!=') COMPARISON)*
     */
    private ExpressionNode parseEquality() throws ParseException {
        ExpressionNode left = this.parseComparison();

        while (this.current.getTokenKind() == EQ || this.current.getTokenKind() == NEQ) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = this.parseComparison();
            left = new BinaryNode(opToken, left, right);
        }

        return left;
    }

    /**
     * COMPARISON = SIMPLE_EXPR (('<' | '<=' | '>' | '>=') SIMPLE_EXPR)*
     */
    private ExpressionNode parseComparison() throws ParseException {
        ExpressionNode left = this.parseSimpleExpr();

        while (this.match(LT, LE, GT, GE)) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = this.parseSimpleExpr();
            left = new BinaryNode(opToken, left, right);
        }

        return left;
    }

    /**
     * SIMPLE_EXPR = TERM (('+' | '-') TERM)*
     *
     * @throws ParseException
     */
    private final EnumSet<TokenKind> simpleExpOps = EnumSet.of(PLUS, MINUS);

    private ExpressionNode parseSimpleExpr() throws ParseException {
        ExpressionNode left = this.parseTerm();

        while (simpleExpOps.contains(this.current.getTokenKind())) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = this.parseTerm();

            left = new SimpleExprNode(opToken, left, right);
        }

        return left;
    }

    /**
     * TERM -> FACTOR (('*' | '/') FACTOR)
     *
     * @throws ParseException
     */
    private final EnumSet<TokenKind> termOps = EnumSet.of(STAR, SLASH);

    private ExpressionNode parseTerm() throws ParseException {
        ExpressionNode left = this.parseFactor();

        while (termOps.contains(this.current.getTokenKind())) {
            Token opToken = this.current;
            this.advance();

            ExpressionNode right = this.parseFactor();

            left = new TermNode(opToken, left, right);
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
                throw new ParseException(this.current, INT, LPAREN);
            }
        }
    }
}
