// OTUS C++ Basic course homework skeleton.
// Lexer using example

#include <iostream>

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {

    Lexer lexer(std::cin);
    Parser parser(lexer);

    try {
        ASTNode *ast = parser.parse();
        if (ast) {
            ast->print(std::cout);
        }
        delete ast;
    }
    catch(const char *error) {
        std::cout << "Error :" << error << std::endl;
        return -1;
    }

    return 0;
}
