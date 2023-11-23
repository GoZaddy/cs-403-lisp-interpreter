# Lisp Interpreter

## What's left??
- Cons function - checkk
- Cons cell concepts - checkk
- List concept - closely tied to literals - checkk
- Literals - checkk
- car - checkk
- cdr - checkk
- List  -> function to make a list out of arguments - checkk
- using minus to make a negative number => (- 20) => -20


# shortcomings
(- - 2) => doesn't get evaluated - throws runtime error




# Run instructions
```
g++ -std=c++11 main.cpp scanner.cpp token.cpp util.cpp parser.cpp expr.cpp interpreter.cpp lox_function.cpp native_funcs.cpp environment.cpp resolver.cpp
```

To run AST (Abstract Syntax Tool) generator tool:
```
g++ -std=c++11 tool/GenerateAst.cpp
```

# What we learned
