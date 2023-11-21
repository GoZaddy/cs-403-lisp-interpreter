#ifndef NATIVE_FUNCS_H
#define NATIVE_FUNCS_H

#include "interpreter.h"
#include "lox_callable.h"
#include <string>
#include "types.h"
#include <vector>
#include <chrono>

typedef std::chrono::milliseconds milliseconds;

class Clock : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<rv> arguments,
            Token calleeToken
        );

        std::string toString();
};

// class CallableWrapper: public LoxCallable{
//     private:
//         int arityProp;
//         std::string toStringProp;
//     public:
//         CallableWrapper (int arityProp, std::string toStringProp, rv (func*) ){

//         }
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// }


class Add : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<rv> arguments,
            Token calleeToken
        );

        std::string toString();
};

// class Sub : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class Divide : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class Mul : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class Greater : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class GreaterEqual : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class Less : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class LessEqual : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };

// class Equal : public LoxCallable{
//     public:
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<rv> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// };


#endif
