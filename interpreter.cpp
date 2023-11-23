#include "interpreter.h"

rv Interpreter::evaluate(Exprvp expr){
    rv value = expr->accept(this);
    // delete expr; // TODO: test this out
    return value;
}
bool Interpreter::isTruthy(rv object){
    if (object == "()") return false; // TODO: what other values could return false
    if (object == "t") return true;
    if (object == "f") return false;
    return true;
}

bool Interpreter::isConsCell(rv expr){
    stringstream ss(expr);
    string first, dot, second;

    ss >> first >> dot >> second;

    if ((first.size() + dot.size() + second.size()+2) == expr.size()){
        if ((first[0] == '(') && (dot == ".") && (second[second.size()-1] == ')')){
            return true;
        }
    }
    return false;
}

bool Interpreter::isStringLiteral(string literal){
    return literal[0] == '\"' && literal[literal.size()-1] == '\"';
}

bool Interpreter::isNumberLiteral(string literal){
    char* end = nullptr;
    double val = strtod(literal.c_str(), &end);
    return end != literal.c_str() && *end == '\0';
}

bool Interpreter::isSymbol(string expr){
    return !isList(expr) &&
        !isStringLiteral(expr) &&
        !isNumberLiteral(expr);
}

bool Interpreter::isCallable(string expr){
    if (expr.size() > 2){
        if (expr[0] == '(' && expr[1] == ')'){
            return true;
        }
    }
    return false;
}

bool Interpreter::isList(string expr){
    if (expr.size() > 2 && expr[0] == '(' && expr[expr.size()-1] == ')'){
        if (!isConsCell(expr)){
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
    throw Util::runtimeError(operatorToken, "Operands must be numbers. Instead: "+ left + ", "+right);
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
    LoxCallable* isEqual = new Equal();

    globals->defineFunc("clock", clockFunc); // TODO: figure this out, consider using a new map in Environment for just functions


    globals->defineFunc("operator<+>", new Add());
    globals->defineFunc("operator<->", new Sub());
    globals->defineFunc("operator<*>", new Mul());
    globals->defineFunc("operator</>", new Divide());
    globals->defineFunc("operator<==>", isEqual);
    globals->defineFunc("operator<>>", new Greater());
    globals->defineFunc("operator<>=>", new GreaterEqual());
    globals->defineFunc("operator<<=>", new LessEqual());
    globals->defineFunc("operator<<>", new Less());
    globals->defineFunc("and?", new And());
    globals->defineFunc("or?", new Or());
    globals->defineFunc("not?", new Not());
    globals->defineFunc("number?", new Number());
    globals->defineFunc("symbol?", new Symbol());
    globals->defineFunc("nil?", new Nil());
    globals->defineFunc("eq?", isEqual);
    globals->defineFunc("list?", new List());
    globals->defineFunc("list", new MakeList());
    globals->defineFunc("car", new Car());
    globals->defineFunc("cdr", new Cdr());
    globals->defineFunc("cond", new Cond());
    globals->defineFunc("cons", new Cons());

    
}
void Interpreter::interpret(std::vector<Exprvp> expr){
    rv res;
    try{
        for (int i = 0; i < expr.size(); ++i){
            res = evaluate(new Printv(expr[i]));
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


rv Interpreter::visit(Callvp expr) {
    rv callee = evaluate(expr->callee);

    // cout << "callee: " << callee << endl;

    Token calleeToken;
    if (expr->callee->getType() == "Variable"){
        calleeToken = ((Variablevp) (expr->callee))->name;
    } else if (expr->callee->getType() == "Op"){
        callee = "()"+callee;
        calleeToken = ((Opvp) (expr->callee))->operatorToken;
    } else {
        cerr << "callee type: " << expr->callee->getType() << endl;
        throw Util::runtimeError(calleeToken, "Can only call functions and operators. Can't call "+callee);
    }

    if (!isCallable(callee)){
        throw Util::runtimeError(calleeToken, "Can only call functions and operators. Can't call "+callee);
    }



    LoxCallable* func = environment->getCallable(callee); // figure this out

    

    if (func->arity() != -1 && expr->arguments.size() != func->arity()) {
        throw Util::runtimeError(calleeToken, "Expected " +
            std::to_string(func->arity()) + " arguments but got " +
            std::to_string(expr->arguments.size()) + ". Occurred when calling: " + calleeToken.lexeme);
    }
    return func->call(this, expr->arguments, calleeToken);
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
    return null;
}

rv Interpreter::visit(Printvp expr) {
    rv value = evaluate(expr->expr);
    return value;
}


rv Interpreter::visit(Setvp stmt){
    string value = "";
    if (stmt->initializer != nullptr){
        value = evaluate(stmt->initializer);
    }

    environment->define(stmt->name.lexeme, value);
    return null;
}