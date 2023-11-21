#include "native_funcs.h"

typedef std::chrono::milliseconds milliseconds;






int Clock::arity() { return 0; }

rv Clock::call(
    Interpreter* interpreter,
    std::vector<rv> arguments,
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
    std::vector<rv> args,
    Token calleeToken
) {
    rv left = args[0];
    rv right = args[1];
    
    if (interpreter->isNumberLiteral(left) && interpreter->isNumberLiteral(right)){
        return interpreter->stripTrailingZeroes(std::to_string(Util::doub(left) + Util::doub(right)));
    }

    throw Util::runtimeError(calleeToken, "Operands must be two numbers or two strings.");
}




