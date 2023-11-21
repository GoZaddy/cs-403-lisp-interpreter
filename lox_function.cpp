#include "lox_function.h"

LoxFunction::LoxFunction(Functionvp declaration, Environment* closure){
    this->closure = closure;
    this->declaration = declaration;
}

rv LoxFunction::call(Interpreter* interpreter, std::vector<rv> arguments, Token calleeToken){
    Environment* environment = new Environment(closure);
    
    for (int i = 0; i < declaration->params.size(); i++) {
        environment->define(
            declaration->params[i].lexeme,
            arguments[i]
        );
    }

    return interpreter->executeBlock(declaration->body, environment);
}

int LoxFunction::arity(){
    return declaration->params.size();
}

std::string LoxFunction::toString() {
    return "<fn " + declaration->name.lexeme + ">";
}