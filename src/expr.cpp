#ifndef EXPR
#define EXPR
#include <string>
#include <vector>
#include "../include/token.h"

using namespace std;

template <typename T>
class Expr;

template <typename T>
class ExprVisitor;


template <typename T>
class Call;


template <typename T>
class Grouping;


template <typename T>
class Literal;


template <typename T>
class Op;


template <typename T>
class Print;


template <typename T>
class Variable;


template <typename T>
class Set;


template <typename T>
class Function;


template <typename T>
class Call: public Expr<T> {
	public:
		Expr<T>* callee;
		std::vector<Expr<T>*> arguments;
		Call(Expr<T>* callee, std::vector<Expr<T>*> arguments) {
			this->callee = callee;
			this->arguments = arguments;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Call";
		}
};

template <typename T>
class Grouping: public Expr<T> {
	public:
		Expr<T>* expression;
		Grouping(Expr<T>* expression) {
			this->expression = expression;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Grouping";
		}
};

template <typename T>
class Literal: public Expr<T> {
	public:
		string value;
		Literal(string value) {
			this->value = value;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Literal";
		}
};

template <typename T>
class Op: public Expr<T> {
	public:
		Token operatorToken;
		Op(Token operatorToken) {
			this->operatorToken = operatorToken;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Op";
		}
};

template <typename T>
class Print: public Expr<T> {
	public:
		Expr<T>* expr;
		Print(Expr<T>* expr) {
			this->expr = expr;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Print";
		}
};

template <typename T>
class Variable: public Expr<T> {
	public:
		Token name;
		Variable(Token name) {
			this->name = name;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Variable";
		}
};

template <typename T>
class Set: public Expr<T> {
	public:
		Token name;
		Expr<T>* initializer;
		Set(Token name, Expr<T>* initializer) {
			this->name = name;
			this->initializer = initializer;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Set";
		}
};

template <typename T>
class Function: public Expr<T> {
	public:
		Token name;
		std::vector<Token> params;
		Expr<T>* body;
		Function(Token name, std::vector<Token> params, Expr<T>* body) {
			this->name = name;
			this->params = params;
			this->body = body;
		}

		T accept(ExprVisitor<T>* visitor) {
			return visitor->visit(this);
		}

		string getType() {
			return "Function";
		}
};

// visitor interface
template <typename T>
class ExprVisitor {
	public:
		virtual T visit(Call<T>* expr) = 0;
		virtual T visit(Grouping<T>* expr) = 0;
		virtual T visit(Literal<T>* expr) = 0;
		virtual T visit(Op<T>* expr) = 0;
		virtual T visit(Print<T>* expr) = 0;
		virtual T visit(Variable<T>* expr) = 0;
		virtual T visit(Set<T>* expr) = 0;
		virtual T visit(Function<T>* expr) = 0;
};

template <typename T>
class Expr {
	public:
		virtual T accept(ExprVisitor<T>* visitor) = 0;
		virtual string getType() = 0;
};

#endif
