#pragma once

#include "lisp_callable.h"
#include "types.h"
#include "interpreter.h"

class LispFunction: public LispCallable{
    private:
        Environment* closure;
    public:
        Functionvp declaration;
        

        LispFunction(Functionvp declaration, Environment* closure);

        rv call(Interpreter* interpreter, std::vector<Exprvp> arguments, Token calleeToken);

        int arity();

        std::string toString();
};