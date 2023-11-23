#include "include/resolver.h"



rv null = "";

Resolver::Resolver(Interpreter* interpreter) {
    this->interpreter = interpreter;
    this->currentFunction = NONE;
    this->scopes = new Stack<Mapsb*>();
}

void Resolver::resolve(Exprvp expr){
    expr->accept(this);
}

void Resolver::resolve(std::vector<Exprvp> exprs){
    for (auto expr : exprs) {
        resolve(expr);
    }
}

void Resolver::beginScope(){
    Mapsb* map = new Mapsb();
    scopes->push(map);
}

void Resolver::endScope(){
    scopes->pop();
}

rv Resolver::visit(Setvp stmt) {
    if (scopes->size() > 0){
        Util::error(stmt->name, "set can only be used in the global scope");
    } else {
        declare(stmt->name);
        if (stmt->initializer != nullptr) {
            resolve(stmt->initializer);
        }
        define(stmt->name);
    }
    return null;
}

void Resolver::declare(Token name) {
    if (scopes->empty()) return;

    Mapsb* scope = scopes->peek();
    if (scope->find(name.lexeme) != scope->end()){
        Util::error(name, "Already a variable with this name in this scope.");
    } else {
        (*scope)[name.lexeme] =  false;
    }
    
}

void Resolver::define(Token name) {
    if (scopes->empty()) return;
    (*(scopes->peek()))[name.lexeme] = true;
}

rv Resolver::visit(Variablevp expr) {
    if (
        !scopes->empty() &&
        (
            scopes->peek()->find(expr->name.lexeme) != scopes->peek()->end() &&
            (*(scopes->peek()))[expr->name.lexeme] == false
        )
    ) {
        Util::error(expr->name,
            "Can't read local variable in its own initializer.");
    }

    resolveLocal(expr, expr->name);
    return null;
}

void Resolver::resolveLocal(Exprvp expr, Token name) {
    if (!scopes->empty()){
        Mapsb* currScope = scopes->peek();
        for (int i = scopes->size() - 1; i >= 0; i--) {
            if (scopes->at(i)->find(name.lexeme) != scopes->at(i)->end()) {
                interpreter->resolve(expr, scopes->size() - 1 - i);
                return;
            }
        }
    }
}


rv Resolver::visit(Functionvp stmt){
    declare(stmt->name);
    define(stmt->name);

    resolveFunction(stmt, FUNCTION);
    return null;
}



void Resolver::resolveFunction(Functionvp func, FunctionType type) {
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;

    beginScope();
    for (auto param : func->params) {
      declare(param);
      define(param);
    }
    resolve(func->body);
    endScope();

    currentFunction = enclosingFunction;
}


rv Resolver:: visit(Callvp expr) {
    resolve(expr->callee);

    for (auto argument : expr->arguments) {
      resolve(argument);
    }

    return null;
}

rv Resolver:: visit(Groupvp expr) {
    resolve(expr->expression);
    return null;
}

rv Resolver:: visit(Litvp expr) {
    return null;
}

rv Resolver:: visit(Opvp expr) {
    return null;
}

rv Resolver::visit(Printvp expr){
    return null;
}

