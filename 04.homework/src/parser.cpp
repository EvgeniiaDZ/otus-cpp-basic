#include "parser.hpp"
#include "number.hpp"
#include "variable.hpp"
#include "mul.hpp"
#include "div.hpp"
#include "add.hpp"
#include "sub.hpp"

using Token = Lexer::Token;

Parser::Parser(Lexer &lexer)
    : lexer_(lexer) {}

ASTNode *Parser::parse() { return expr(); }

void Parser::next_token() { tok_ = lexer_.next_token(); }

ASTNode *Parser::check_term() {
    ASTNode *node = term();
    if (node == nullptr) {
        throw "unexpected end of expression";
    }    
    return node;
}

ASTNode *Parser::check_prim() {
    ASTNode *node = prim();
    if (node == nullptr) {
        throw "unexpected end of expression";
    }    
    return node;
}

ASTNode *Parser::expr() {
    // parse addition and subsctruction
    ASTNode *root = term();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            switch (op.front()) {
            case '+':
                try {
                    root = new Add(root, check_term());
                }
                catch(const char *error) {
                    throw error;
                }
                break;
            case '-':
                try { 
                    root = new Sub(root, check_term());
                }
                catch(const char *error) {
                    throw error;
                }
                break;
            default:
                return root;
            }
            break;
        }
        default:
            return root;
        }
    }
}

ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            switch (op.front()) {
            case '*': {  
                try {
                    root = new Mul(root, check_prim());
                }
                catch(const char *error) {
                    throw error;
                }
                break;
            }
            case '/': {
                try {
                    root = new Div(root, check_prim());
                }
                catch(const char *error) {
                    throw error;
                }
                break;
            }
            default:
                return root;
            }
            break;
        }
        case Token::Name: {
            throw "expected operator";
        }
        case Token::Number: {
            throw "expected operator";
        }
        case Token::Lbrace: {
            throw "expected operator";
        }
        default:
            return root;
        }
    }
}

ASTNode *Parser::prim() {
    // parse numbers and names
    ASTNode *node = nullptr;
    next_token();
    switch (tok_) {
    case Token::Number:
        node = new Number(lexer_.get_number());
        break;
    case Token::Name:
        node = new Variable(lexer_.get_name());
        break;
    case Token::Operator: {
        std::string op = lexer_.get_operator();
        if (op.front() == '-') {
            next_token();
            if (tok_ == Token::Number) {
                node = new Number(-lexer_.get_number());
                break;
            }
            throw "expected a negative number";
        }  
        else {
            throw "expected number or variable first";
        }
    }
    case Token::Lbrace:
        node = expr();
        if (tok_ != Token::Rbrace) {
            throw "')' expected ";
        }
        break;
    default:
        break;
    }
    next_token();
    return node;
}