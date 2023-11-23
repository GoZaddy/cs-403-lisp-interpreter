#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <iostream>
#include <sstream>
#include "token.h"
#include "types.h"

using namespace std;

class AstPrinter: public ExprVisitor<string> {

    private:
        string parenthesize(string name, initializer_list<Expr<string>*> exprs) {
            stringstream builder;

            builder << "(" << name;
            for (auto expr : exprs) {
                builder << " " << expr->accept(this);
            }
            builder << ")";

            return builder.str();
        }
    public:
        string print(Expr<string>* expr) {
            return expr->accept(this);
        }


        string visit(Grouping<string>* expr) {
            return parenthesize("group", {expr->expression});
        }

        string visit(Literal<string>* expr) {
            if (expr->value == "") return "nil";
            return expr->value;
        }

        string visit(Variable<string>* expr) {
            return expr->name.lexeme;
        }

        string visit(Call<string>* expr) {
            string args = "(";
            for(auto arg : expr->arguments){
                args += print(arg) + ",";
            }
            
            if (args.size() > 1){
                args.pop_back();
            }
            args += ")";
            return print(expr->callee) + args;
        }

        string visit(Function<string>* expr) {
            string args = "(func " + expr->name.lexeme + " (";
            for(auto arg : expr->params){
                args += arg.lexeme + ",";
            }
            
            if (args.size() > 1){
                args.pop_back();
            }
            args += "))";
            return args;
        }

        string visit(Set<string>* expr) {
            return "(set " + expr->name.lexeme + ", " + print(expr->initializer) + ")";   
        }

        string visit(Op<string>* expr) {
            return expr->operatorToken.lexeme;
        }

        string visit(Printvp expr){
            return print(expr->expr);
        }



};


// int main(){
//     Expr<string>* expr;

//     Literal<string> lit1 = Literal<string>("123", LiteralTypeNS::STRING);
//     Literal<string> lit2 = Literal<string>("45.67", LiteralTypeNS::STRING);

//     Unary<string> unary(
//         Token(MINUS, "-", "", 1),
//         &lit1
//     );

//     Token mul(STAR, "*", "", 1);

//     Grouping<string> g(
//         &lit2
//     );

//     Binary<string> b(
//         &unary,
//         mul,
//         &g
//     );

//     expr = &b;

//     AstPrinter astp;

//     cout << astp.print(expr) << endl;
    
// }

#endif