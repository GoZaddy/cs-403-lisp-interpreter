#include "interpreter.h"

rv Interpreter::evaluate(Exprvp expr){
    rv value = expr->accept(this);
    // delete expr; // TODO: test this out
    return value;
}
bool Interpreter::isTruthy(rv object){
    if (object == "()") return false; // TODO: what other values could return false
    if (object == "'t") return true;
    if (object == "'f") return false;
    return true;
}

bool Interpreter::isStringLiteral(string literal){
    return literal[0] == '\"' && literal[literal.size()-1] == '\"';
}

bool Interpreter::isNumberLiteral(string literal){
    char* end = nullptr;
    double val = strtod(literal.c_str(), &end);
    return end != literal.c_str() && *end == '\0';
}

bool Interpreter::isCallable(string expr){
    if (expr.size() > 2){
        if (expr[0] == '(' && expr[1] == ')'){
            return true;
        }
    }
    return false;
}

bool Interpreter::isEqual(rv a, rv b){
    return a == b;
}

void Interpreter::checkNumberOperand(Token operatorToken, rv operand){
    if (isNumberLiteral(operand)) return;
    throw Util::runtimeError(operatorToken, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(Token operatorToken, rv left, rv right){
    if (isNumberLiteral(left) && isNumberLiteral(right)) return;
    throw Util::runtimeError(operatorToken, "Operands must be numbers");
}

string Interpreter::stripTrailingZeroes(rv text){
    if (text.size() > 7 && text.substr(text.size()-7) == ".000000"){
        text = text.substr(0, text.size()-7);
    }
    return text;
}


void Interpreter::resolve(Exprvp expr, int depth) {
    locals[expr] = depth;
}

Interpreter::Interpreter() {
    globals = new Environment();
    environment = globals;
    LoxCallable* clockFunc = new Clock();

    globals->defineFunc("clock", clockFunc); // TODO: figure this out, consider using a new map in Environment for just functions

    globals->defineFunc("operator<+>", new Add());
    // globals->defineFunc("-", new Sub());
    // globals->defineFunc("*", new Mul());
    // globals->defineFunc("/", new Divide());
    // globals->defineFunc("==", new Equal());
    // globals->defineFunc(">", new Greater());
    // globals->defineFunc(">=", new GreaterEqual());
    // globals->defineFunc("<=", new LessEqual());
    // globals->defineFunc("<", new Less());
    
}
void Interpreter::interpret(std::vector<Exprvp> expr){
    rv res;
    try{
        for (int i = 0; i < expr.size(); ++i){
            res = evaluate(expr[i]);
            if (res != ""){
                cout << res << endl;
            }
            // delete statements[i]; // i was testing something
        }
    } catch(string error){std::cerr << error << endl;};
}

rv Interpreter::executeBlock(
    Exprvp expr,
    Environment* currentEnv
) {
    Environment* previous = this->environment;
    rv result = "";
    try {
        this->environment = currentEnv;

        result = evaluate(expr);
    } 
    catch(string error){
        std::cerr << error << endl;
    }
    catch(...){}

    this->environment = previous;

    return result;

    
}


rv Interpreter::visit(Litv* expr){
    return expr->value;
}


rv Interpreter::visit(Groupv* expr){
    return evaluate(expr->expression);
}

rv Interpreter::visit(Opvp expr){
    return "operator<" + expr->operatorToken.lexeme+">";
}


// rv Interpreter::visit(Binv* expr){
//     rv left = evaluate(expr->left);
//     rv right = evaluate(expr->right);

//     switch(expr->operatorToken.type){
//         case MINUS:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return stripTrailingZeroes(std::to_string(Util::doub(left) - Util::doub(right)));
//         case SLASH:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return stripTrailingZeroes(std::to_string(Util::doub(left) / Util::doub(right)));
//         case STAR:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return stripTrailingZeroes(std::to_string(Util::doub(left) * Util::doub(right)));
//         case PLUS:
//             if (isStringLiteral(left) && isStringLiteral(right)){
//                 left.pop_back();
//                 return left + right.substr(1);
//             }
            
//             if (isNumberLiteral(left) && isNumberLiteral(right)){
//                 return stripTrailingZeroes(std::to_string(Util::doub(left) + Util::doub(right)));
//             }

//             throw Util::runtimeError(expr->operatorToken, "Operands must be two numbers or two strings.");
            
//         case GREATER:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return (Util::doub(left) > Util::doub(right)) ? "true" : "false";
//         case GREATER_EQUAL:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return (Util::doub(left) >= Util::doub(right)) ? "true" : "false";
//         case LESS:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return (Util::doub(left) < Util::doub(right)) ? "true" : "false";
//         case LESS_EQUAL:
//             checkNumberOperands(expr->operatorToken, left, right);
//             return (Util::doub(left) <= Util::doub(right)) ? "true" : "false";
            
//         case BANG_EQUAL:
//             return isEqual(left, right) ? "false" : "true";
//         case EQUAL_EQUAL:
//             return isEqual(left, right) ? "true" : "false";
            

//         default:
//             //unreachable
//             return "";
//     }
// }

rv Interpreter::visit(Callvp expr) {
    rv callee = evaluate(expr->callee);

    cout << "callee: " << callee << endl;

    Token calleeToken;
    if (expr->callee->getType() == "Variable"){
        calleeToken = ((Variablevp) (expr->callee))->name;
    } else if (expr->callee->getType() == "Op"){
        callee = "()"+callee;
        calleeToken = ((Opvp) (expr->callee))->operatorToken;
    } else {
        cerr << "callee type: " << expr->callee->getType() << endl;
        throw Util::runtimeError(calleeToken, "Can only call functions and operators.");
    }

    if (!isCallable(callee)){
        throw Util::runtimeError(calleeToken, "Can only call functions and operators.");
    }

    std::vector<rv> arguments;
    for (auto argument : expr->arguments) { 
        arguments.push_back(evaluate(argument));
    }


    LoxCallable* func = environment->getCallable(callee); // figure this out

    

    if (arguments.size() != func->arity()) {
        throw Util::runtimeError(calleeToken, "Expected " +
            std::to_string(func->arity()) + " arguments but got " +
            std::to_string(arguments.size()) + ".");
    }
    return func->call(this, arguments, calleeToken);
}

rv Interpreter::visit(Variablevp expr){
    return lookUpVariable(expr->name, expr);
}

rv Interpreter::lookUpVariable(Token name, Exprvp expr) {
    if (locals.find(expr) != locals.end()) {
        int distance = locals[expr];
        return environment->getAt(distance, name.lexeme);
    } else {
        return globals->get(name);
    }
}


rv Interpreter::visit(Functionvp expr){
    LoxCallable* func = new LoxFunction(expr, environment);
    environment->defineFunc(expr->name.lexeme, func); // come up with our solution for this
    return "";
}

// rv Interpreter::visit(Ifvp stmt) {
//     if (isTruthy(evaluate(stmt->condition))) {
//         execute(stmt->thenBranch);
//     } else if (stmt->elseBranch != nullptr) {
//         execute(stmt->elseBranch);
//     }
//     return "";
// }


rv Interpreter::visit(Setvp stmt){
    string value = "";
    if (stmt->initializer != nullptr){
        value = evaluate(stmt->initializer);
    }

    environment->define(stmt->name.lexeme, value);
    return "";
}