#!/bin/bash

g++ -std=c++11 src/main.cpp src/scanner.cpp src/token.cpp src/util.cpp src/parser.cpp src/expr.cpp src/interpreter.cpp src/lisp_function.cpp src/native_funcs.cpp src/environment.cpp src/resolver.cpp