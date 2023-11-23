#pragma once

#include "interpreter.h"
#include "lisp_callable.h"
#include <string>
#include "types.h"
#include <vector>
#include <chrono>

typedef std::chrono::milliseconds milliseconds;

class Clock : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Add : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Sub : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Divide : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Mul : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Greater : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class GreaterEqual : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Less : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class LessEqual : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Equal : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class And : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Or : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Not : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Number : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Symbol : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Nil : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};



class List : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};



class Cond : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class MakeList : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Car : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Cdr : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};



class Cons : public LispCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};
