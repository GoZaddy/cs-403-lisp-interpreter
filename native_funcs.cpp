#include "native_funcs.h"

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








int Sub::arity() { return 2; }

rv Sub::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
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
    
    return interpreter->isEqual(left, right) ? "'t" : "'f";
}










int Greater::arity() { return 2; }

rv Greater::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) > Util::doub(right)) ? "'t" : "'f";
}









int Less::arity() { return 2; }

rv Less::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) < Util::doub(right)) ? "'t" : "'f";
}









int GreaterEqual::arity() { return 2; }

rv GreaterEqual::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) >= Util::doub(right)) ? "'t" : "'f";
}









int LessEqual::arity() { return 2; }

rv LessEqual::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) <= Util::doub(right)) ? "'t" : "'f";
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
    
    
    return interpreter->isNumberLiteral(left) ? "'t" : "'f";
}







// TODO: need to implement quoted literals
int Symbol::arity() { return 1; }

rv Symbol::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) <= Util::doub(right)) ? "'t" : "'f";
}








int Nil::arity() { return 1; }

rv Nil::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);

    return left == "()" ? "'t" : "'f";
}







// TODO: need to implement lists
int List::arity() { return 1; }

rv List::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    rv right = interpreter->evaluate(args[1]);
    
    return (Util::doub(left) <= Util::doub(right)) ? "'t" : "'f";
}






int Not::arity() { return 1; }

rv Not::call(
    Interpreter* interpreter,
    std::vector<Exprvp> args,
    Token calleeToken
) {
    rv left = interpreter->evaluate(args[0]);
    
    return interpreter->isTruthy(left) ? "()" : "'t";
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
        res = interpreter->evaluate(args[i+1]);

        if (interpreter->isTruthy(expression)){
            return res;
        }
    }
    
    return "()";
}
