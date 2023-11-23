#ifndef RESOLVER_H
#define RESOLVER_H

#include "types.h"
#include "interpreter.h"
#include <unordered_map>
#include "helper/custom_stack.h"

typedef std::unordered_map<std::string, bool> Mapsb;

enum FunctionType {
    NONE,
    FUNCTION
};

class Resolver: ExprVisv{
    private:
        Interpreter* interpreter;

        Stack<Mapsb*>* scopes;

        FunctionType currentFunction;

        void resolve(Exprvp expr);

        void beginScope();

        void endScope();

        void declare(Token name);

        void define(Token name);

        void resolveLocal(Exprvp expr, Token name);

        void resolveFunction(Functionvp function, FunctionType type);

    public:
        Resolver(Interpreter* interpreter);

        void resolve(std::vector<Exprvp> expressions);

        rv visit(Litv* expr);

        rv visit(Groupv* expr);

        rv visit(Callvp expr);

        rv visit(Variablevp expr);

        rv visit(Setvp expr);

        rv visit(Opvp expr);

        rv visit(Functionvp stmt);

        rv visit(Printvp expr);

};


#endif