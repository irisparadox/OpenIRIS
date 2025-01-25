#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "lexer/lexer.h"

std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;

    if(file.is_open()) {
        buffer << file.rdbuf();
    } else {
        std::cerr << "Could not open file " << filename << '\n';
    }

    return buffer.str();
}

int main() {
    std::string filename = "../example_code/example.oir";
    std::string source   = read_file(filename);
    Lexer lex(source);
    std::vector<Token> tokens = lex.tokenize();
    for(const auto& token : tokens) {
        std::cout << token.value << ' ' << token.row << ',' << token.col << '\n';
    }
    return 0;
}
