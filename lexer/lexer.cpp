#include "lexer.h"
#include <iostream>

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while(current_idx < source_code.length()) {
        char current = source_code[current_idx];

        if(current == '\n') {
            ++row;
            ++current_idx;
            col = 1;
            continue;
        }

        if(isspace(current)) {
            ++current_idx;
            ++col;
            continue;
        }

        // check identifier pattern
        if(isalpha(current) || current == '_') {
            std::string word;
            while(isalnum(current) || current == '_') {
                word += current;
                current = source_code[++current_idx];
            }

            if(token_map.find(word) != token_map.end())
                tokens.push_back({word, token_map[word], row, col});
            else
                tokens.push_back({word, IDENTIFIER, row, col});

            col += word.length();
            continue;
        }

        // integer literal
        if(isdigit(current)) {
            std::string literal;
            size_t last_idx = current_idx;
            while(isdigit(current)) {
                literal += current;
                current = source_code[++current_idx];
            }
            tokens.push_back({literal, LIT_INTEGER, row, col});
            col += literal.length();
            continue;
        }

        // float literal
        if(isdigit(current)) {
            std::string literal;
            while(isdigit(current) && current != '.') {
                literal += current;
                current = source_code[++current_idx];
            }
            literal += current;
            ++current_idx;
            if(check_bounds()) {
                //TODO handle error
                continue;
            }
            current = source_code[current_idx];
            if(current == '.') {
                //TODO handle error
                continue;
            }
            while(isdigit(current)) {
                literal += current;
                current = source_code[++current_idx];
            }
            if(current == '.') {
                //TODO handle error
                continue;
            }
            tokens.push_back({literal, LIT_FLOAT, row, col});
            col += literal.length();
            continue;
        }

        // string literal
        if(current == '"') {
            std::string literal;
            literal += current;
            ++current_idx;
            if(current_idx >= source_code.size()) {
                //TODO handle error
                continue;
            }
            current = source_code[current_idx];
            while(current != '"') {
                literal += current;
                ++current_idx;
                if(current_idx >= source_code.size()) {
                    //TODO handle error
                    continue;
                }
                current = source_code[current_idx];
            }
            literal += current;
            tokens.push_back({literal, LIT_STRING, row, col});
            col += literal.length();
            continue;
        }

        // char literal
        if(current == '\'') {
            std::string literal = "'";
            ++current_idx;
            if(current_idx >= source_code.size()) {
                //TODO handle error
                continue;
            }
            current = source_code[current_idx];
            if(current != '\'') {
                literal += current;
                ++current_idx;
                if(current_idx >= source_code.size()) {
                    //TODO handle error
                    continue;
                }
                current = source_code[current_idx];
            }
            if(current == '\'') {
                literal += '\'';
                tokens.push_back({literal, LIT_CHAR, row, col});
                ++current_idx;
                col += 3;
                continue;
            }

            //TODO handle error
            continue;
        }

        // operator ::
        if(current == ':' && current_idx + 1 < source_code.size() && source_code[current_idx + 1] == ':') {
            tokens.push_back({"::", OP_COLONCOLON, row, col});
            current_idx += 2;
            col += 2;
            continue;
        }

        // operator &&
        if(current == '&' && current_idx + 1 < source_code.size() && source_code[current_idx + 1] == '&') {
            tokens.push_back({"&&", OP_LOGAND, row, col});
            current_idx += 2;
            col += 2;
            continue;
        }

        // operator ||
        if(current == '|' && current_idx + 1 < source_code.size() && source_code[current_idx + 1] == '|') {
            tokens.push_back({"||", OP_LOGOR, row, col});
            current_idx += 2;
            col += 2;
            continue;
        }

        // operator ->
        if(current == '-' && current_idx + 1 < source_code.size() && source_code[current_idx + 1] == '>') {
            tokens.push_back({"->", OP_ARROW, row, col});
            current_idx += 2;
            col += 2;
            continue;
        }

        if(token_map.find(std::string(1, current)) != token_map.end()) {
            std::string character(1, current);
            tokens.push_back({character, token_map[character], row, col});
            ++current_idx;
            ++col;
            continue;
        }

        ++current_idx;
    }
    tokens.push_back({"", END_OF_FILE, row, col});
    return tokens;
}