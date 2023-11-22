#ifndef LOX_CALLABLE_H
#define LOX_CALLABLE_H

#include <string>
#include <vector>
#include "types.h"

class Interpreter;

class LoxCallable{
    public:
        virtual int arity() = 0;
		virtual rv call(Interpreter* interpreter, std::vector<Exprvp> arguments, Token calleeToken) = 0;
};

#endif