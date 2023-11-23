#pragma once

#include "../src/expr.cpp"



typedef string rv; // rv - return value for visitor

extern rv null;




typedef ExprVisitor<rv> ExprVisv;
// typedef StmtVisitor<rv> StmtVisv;
typedef Literal<rv> Litv;
typedef Literal<rv>* Litvp;
typedef Op<rv> Opv;
typedef Opv* Opvp;
typedef Grouping<rv> Groupv;
typedef Grouping<rv>* Groupvp;
typedef Expr<rv> Exprv;
typedef Expr<rv>* Exprvp;
typedef Call<rv> Callv;
typedef Callv* Callvp;
typedef Variable<rv> Variablev;
typedef Variablev* Variablevp;
typedef Print<rv> Printv;
typedef Printv* Printvp;
typedef Set<rv> Setv;
typedef Setv* Setvp;
typedef Function<rv> Functionv;
typedef Functionv* Functionvp;