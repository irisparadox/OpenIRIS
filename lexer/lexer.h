//
//
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

enum TokenType {
    // identifiers and literals
    IDENTIFIER,
    LIT_INTEGER,
    LIT_FLOAT,
    LIT_STRING,
    LIT_CHAR,
    LIT_TRUE,
    LIT_FALSE,

    // types and modifiers
    KEY_CHAR,
    KEY_SHORT,
    KEY_INTEGER,
    KEY_LONG,
    KEY_BOOL,
    KEY_FLOAT,
    KEY_DOUBLE,
    KEY_VOID,
    KEY_OPERATOR,
    KEY_UNSIGNED,
    KEY_POINTER,
    KEY_REFERENCE,
    KEY_RENAME,
    KEY_CONSTANT,
    KEY_STATIC,
    KEY_ABSTRACT,

    // flow control
    KEY_IF,
    KEY_ELSE,
    KEY_WHILE,
    KEY_FOR,
    KEY_SWITCH,
    KEY_CASES,
    KEY_DEFAULT,
    KEY_BREAK,
    KEY_RETURN,

    // classes and structures
    KEY_CLASS,
    KEY_INTERFACE,
    KEY_PUBLIC,
    KEY_PRIVATE,
    KEY_PROTECTED,
    KEY_SHARED,
    KEY_BOX,
    KEY_ENUM,

    // operators
    OP_PLUS,
    OP_PLUSPLUS,
    OP_MINUS,
    OP_MINUSMINUS,
    OP_ASTK,
    OP_DIV,
    OP_AMPER,
    OP_BITOR,
    OP_BITNOT,
    OP_XOR,
    OP_LOGAND,
    OP_LOGOR,
    OP_LOGNOT,
    OP_LT,
    OP_GT,
    OP_LEQ,
    OP_GEQ,
    OP_EQ,
    OP_NEQ,
    OP_TERNARY,
    OP_RPARENTH,
    OP_LPARENTH,
    OP_RBRACKET,
    OP_LBRACKET,
    OP_COLONCOLON,
    OP_ASSIGN,
    OP_ARROW,
    OP_DOT,
    OP_DEPOINT,
    OP_ADDRESSOF,
    OP_ALLOC,
    OP_DEALLOC,

    // separators
    SEP_LBRACE,
    SEP_RBRACE,
    SEP_SEMICOLON,
    SEP_COLON,
    SEP_COMMA,

    END_OF_FILE,
    UNKNOWN
};

struct Token {
    std::string value;
    TokenType type;
    size_t row, col;
};

class Lexer {
public:
    explicit Lexer(std::string& source) : source_code(source), current_idx(0), col(1), row(1) {};
    std::vector<Token> tokenize();
    std::string current_token() const;

private:
    bool check_bounds() {
        return current_idx >= source_code.size();
    }

private:
    std::string source_code;
    std::unordered_map<std::string, TokenType> token_map = {
            {"true",      LIT_TRUE},
            {"false",     LIT_FALSE},
            {"char",      KEY_CHAR},
            {"short",     KEY_SHORT},
            {"int",       KEY_INTEGER},
            {"long",      KEY_LONG},
            {"bool",      KEY_BOOL},
            {"float",     KEY_FLOAT},
            {"double",    KEY_DOUBLE},
            {"void",      KEY_VOID},
            {"operator",  KEY_OPERATOR},
            {"unsigned",  KEY_UNSIGNED},
            {"pointer",   KEY_POINTER},
            {"reference", KEY_REFERENCE},
            {"rename",    KEY_RENAME},
            {"constant",  KEY_CONSTANT},
            {"static",    KEY_STATIC},
            {"abstract",  KEY_ABSTRACT},
            {"if",        KEY_IF},
            {"else",      KEY_ELSE},
            {"while",     KEY_WHILE},
            {"for",       KEY_FOR},
            {"switch",    KEY_SWITCH},
            {"cases",     KEY_CASES},
            {"default",   KEY_DEFAULT},
            {"break",     KEY_BREAK},
            {"return",    KEY_RETURN},
            {"class",     KEY_CLASS},
            {"interface", KEY_INTERFACE},
            {"public",    KEY_PUBLIC},
            {"private",   KEY_PRIVATE},
            {"protected", KEY_PROTECTED},
            {"shared",    KEY_SHARED},
            {"box",       KEY_BOX},
            {"enum",      KEY_ENUM},
            {"+",         OP_PLUS},
            {"-",         OP_MINUS},
            {"*",         OP_ASTK},
            {"/",         OP_DIV},
            {"&",         OP_AMPER},
            {"|",         OP_BITOR},
            {"~",         OP_BITNOT},
            {"^",         OP_XOR},
            {"!",         OP_LOGNOT},
            {"<",         OP_LT},
            {">",         OP_GT},
            {"?",         OP_TERNARY},
            {")",         OP_RPARENTH},
            {"(",         OP_LPARENTH},
            {"]",         OP_RBRACKET},
            {"[",         OP_LBRACKET},
            {"=",         OP_ASSIGN},
            {".",         OP_DOT},
            {"depoint",   OP_DEPOINT},
            {"addressof", OP_ADDRESSOF},
            {"alloc",     OP_ALLOC},
            {"dealloc",   OP_DEALLOC},
            {"{",         SEP_LBRACE},
            {"}",         SEP_RBRACE},
            {";",         SEP_SEMICOLON},
            {":",         SEP_COLON},
            {",",         SEP_COMMA},
    };
    size_t current_idx;
    size_t col, row;
};

#endif //COMPILER_LEXER_H
