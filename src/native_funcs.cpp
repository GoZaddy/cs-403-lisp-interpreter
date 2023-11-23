#include "include/native_funcs.h"
#include <sstream>

typedef std::chrono::milliseconds milliseconds;






int Clock::arity() { return 0; }

rv Clock::call(
    Interpreter* interpreter,
    std::vector<Exprvp> arguments,
    Token calleeToken
) {
    milliseconds ms = std::chrono::duration_cast< milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    return std::to_string(ms.count());
}











int Add::arity() { return 2; }

rv Add::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);

    interpreter->checkNumberOperands(calleeToken, left, right);
    return interpreter->stripTrailingZeroes(std::to_string(Util::doub(left) + Util::doub(right)));
}








int Sub::arity() { return -1; }

rv Sub::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    if (args.size() == 0){
        throw Util::runtimeError(calleeToken, "operator '-' requires at least one argument");
    }
    
    rv left = interpreter->evaluate(args[0]);

    if (args.size() == 1){
        interpreter->checkNumberOperands(calleeToken, left, "0");
        return interpreter->stripTrailingZeroes(std::to_string(-1 * Util::doub(left)));
    }
    rv right = interpreter->evaluate(args[1]);
    

    interpreter->checkNumberOperands(calleeToken, left, right);
    return interpreter->stripTrailingZeroes(std::to_string(Util::doub(left) - Util::doub(right)));
}











int Mul::arity() { return 2; }

rv Mul::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);

    interpreter->checkNumberOperands(calleeToken, left, right);
    return interpreter->stripTrailingZeroes(std::to_string(Util::doub(left) * Util::doub(right)));
}











int Divide::arity() { return 2; }

rv Divide::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);

    interpreter->checkNumberOperands(calleeToken, left, right);
    return interpreter->stripTrailingZeroes(std::to_string(Util::doub(left) / Util::doub(right)));
}










int Equal::arity() { return 2; }

rv Equal::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return interpreter->isEqual(left, right) ? "t" : "()";
}










int Greater::arity() { return 2; }

rv Greater::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) > Util::doub(right)) ? "t" : "()";
}









int Less::arity() { return 2; }

rv Less::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) < Util::doub(right)) ? "t" : "()";
}









int GreaterEqual::arity() { return 2; }

rv GreaterEqual::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) >= Util::doub(right)) ? "t" : "()";
}









int LessEqual::arity() { return 2; }

rv LessEqual::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) <= Util::doub(right)) ? "t" : "()";
}








int And::arity() { return 2; }

rv And::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    

    if (interpreter->isTruthy(left)){
        return interpreter->evaluate(args[1]);
    } 

    return left; 
}








int Or::arity() { return 2; }

rv Or::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    

    if (interpreter->isTruthy(left)){
        return left;
    } 

    return interpreter->evaluate(args[1]); 
}








int Number::arity() { return 1; }

rv Number::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    
    
    return interpreter->isNumberLiteral(left) ? "t" : "()";
}







// TODO: need to implement quoted literals
int Symbol::arity() { return 1; }

rv Symbol::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv arg = interpreter->evaluate(args[0]);
    
    return interpreter->isSymbol(arg) ? "t" : "()";
}








int Nil::arity() { return 1; }

rv Nil::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);

    return left == "()" ? "t" : "()";
}






int List::arity() { return 1; }

rv List::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv arg = interpreter->evaluate(args[0]);
    
    return (arg == "()" || interpreter->isList(arg)) ? "t" : "()";
}






int Not::arity() { return 1; }

rv Not::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    
    return interpreter->isTruthy(left) ? "()" : "t";
}






int Cond::arity() { return -1; }

rv Cond::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    if ((args.size() % 2) != 0){
        throw Util::runtimeError(calleeToken, "Cond has non-even number of arguments");
    }

    rv expression;
    rv res;

    for(int i = 0; i < args.size(); i = i+2){
        expression = interpreter->evaluate(args[i]);
        


        if (interpreter->isTruthy(expression)){
            return interpreter->evaluate(args[i+1]);;
        }
    }
    
    return "()";
}








int MakeList::arity() { return -1; }

rv MakeList::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {

    if (args.size() == 0){
        throw Util::runtimeError(calleeToken, "List function should have at least one argument. Got 0");
    }
    string list = "(";

    for(auto arg: args){
        list += interpreter->evaluate(arg) + " ";
    }

    list.pop_back();
    list += ")";
    
    return list;
}






int Car::arity() { return 1; }

rv Car::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {

    rv val = interpreter->evaluate(args[0]);
    if (val == "()"){
        throw Util::runtimeError(calleeToken, "cannot call car on empty list");
    }

    if (!interpreter->isList(val)){
        throw Util::runtimeError(calleeToken, "cannot call car on non-list: "+val);
    }

    

    stringstream ss;

    ss << val;

    rv result;

    ss >> result;

    if (result.size() == val.size()){
        result.pop_back();
    }
    
    return result.substr(1);
}







int Cdr::arity() { return 1; }

rv Cdr::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv val = interpreter->evaluate(args[0]);

    if (val == "()"){
        throw Util::runtimeError(calleeToken, "cannot call cdr on empty list");
    }


    if (!interpreter->isList(val)){
        throw Util::runtimeError(calleeToken, "cannot call cdr on non-list: "+val);
    }

    
    stringstream ss;


    ss << val;

    rv token;

    ss >> token;

    if (token.size() == ss.str().size()){
        return "()";
    }
    
    return "(" + ss.str().substr(token.size()+1);
}









int Cons::arity() { return 2; }

rv Cons::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv first = interpreter->evaluate(args[0]);
    rv second = interpreter->evaluate(args[1]);

    if (second == "()"){
        return "(" + first + ")";

    }

    if (interpreter->isList(second)){
        return "(" + first + " " + second.substr(1);
    }
    
    return "(" + first + " . " + second + ")";
}
