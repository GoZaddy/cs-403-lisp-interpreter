#include "../include/lisp_function.h"

LispFunction::LispFunction(Functionvp declaration, Environment* closure){
    this->closure = closure;
    this->declaration = declaration;
}

rv LispFunction::call(Interpreter* interpreter, std::vector<Exprvp> arguments, Token calleeToken){
    Environment* environment = new Environment(closure);
    
    for (int i = 0; i < declaration->params.size(); i++) {
        environment->define(
            declaration->params[i].lexeme,
            interpreter->evaluate(arguments[i])
        );
    }

    return interpreter->executeBlock(declaration->body, environment);
}

int LispFunction::arity(){
    return declaration->params.size();
}

std::string LispFunction::toString() {
    return "<fn " + declaration->name.lexeme + ">";
}