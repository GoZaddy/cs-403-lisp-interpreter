#pragma once
#include <string>
#include <vector>
#include "types.h"

class Interpreter;

class LispCallable{
    public:
        virtual int arity() = 0;
		virtual rv call(Interpreter* interpreter, std::vector<Exprvp> arguments, Token calleeToken) = 0;
};
