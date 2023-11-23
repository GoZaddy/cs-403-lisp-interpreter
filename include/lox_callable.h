#pragma once
#include <string>
#include <vector>
#include "include/types.h"

class Interpreter;

class LoxCallable{
    public:
        virtual int arity() = 0;
		virtual rv call(Interpreter* interpreter, std::vector<Exprvp> arguments, Token calleeToken) = 0;
};
