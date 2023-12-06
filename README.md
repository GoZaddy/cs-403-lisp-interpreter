# Yisp Interpreter

##  Building executable for interpreter

- Make sure you're in the root directory of the project
- Make sure you have g++ compiler installed

If you're not sure:
Run `g++ --version` in command line to find out. You should get something like this:
```
g++.exe (x86_64-posix-seh, Built by strawberryperl.com project) 8.3.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

- Now Run:
```
g++ -w -std=c++11 src/main.cpp src/scanner.cpp src/token.cpp src/util.cpp src/parser.cpp src/expr.cpp src/interpreter.cpp src/lisp_function.cpp src/native_funcs.cpp src/environment.cpp src/resolver.cpp
```


## Testing

In the root directory, you will find my solution to the blackjack and bowling problems assigned earlier in the semester. You can run these files using the following shell command:

(blackjack.lsp and bowling.lsp are file names. Replace these with a suitable file name to run that file)

For windows:
```
./a.exe blackjack.lsp

./a.exe bowling.lsp
```


For mac/linux:
```
./a.out blackjack.lsp

./a.out bowling.lsp
```

## REPL

You can also spin up a yisp REPL session by running:

(Windows)
```
a.exe
```

(Mac/Linux)
```
a.out
```

## What doesn't work / what works differently than you might expect
Here's a list of things that are not supported or might not work as you might expect
- Double minus sign
```
(- - 3) ;; you might expect this to give evaluate as -(-3) and give you 3. However this will throw an error

(- (- 3)) ;; this is the correct way
```

- Writing lists in your code
The only supported ways to work with lists are
    - List literals: `(car '(1 2 3))`
    - Functions that return lists: `(car (get_list))`
    - Through the `list` function: `(car (list 1 2 3))`

`(1 2 3)` is evaluated as calling the function 1 with arguments 2 and 3 which will throw an error


- `if` is not supported but `cond` is
- Unnecessary nesting will throw errors. For example: `(((((+ 1 2)))))` should be written as `(+ 1 2)`

- A cons operation with a valid list output will simply return a list:
```
(cons 1 ()) ;; returns (1)
(cons 1 2) ;; returns (1 . 2)

```
