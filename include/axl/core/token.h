#ifndef AXL_TOKEN_H
#define AXL_TOKEN_H

/// Token types for lexical analysis
typedef enum TokenType {
    TOKEN_UNKNOWN = 0,
    
    // Keywords
    TOKEN_LET,
    TOKEN_CONST,
    TOKEN_VAR,
    
    // Operators
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    
    // Identifiers and literals
    TOKEN_IDENT,
    TOKEN_LITERAL,
    
    // Syntax elements
    TOKEN_SEMICOLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN
} TokenType;

#endif // AXL_TOKEN_H
