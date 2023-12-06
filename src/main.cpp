#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/scanner.h"
#include "parser.cpp"
// #include "src/ast_printer.cpp"
#include "../include/util.h"
#include "../include/interpreter.h"
#include "../include/resolver.h"

using namespace std;

bool Util::hadError = false;
bool Util::hadRuntimeError = false;

Interpreter interpreter;
 
void run(string source){
    // get tokens
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();

    // For now, just print the tokens.
    // for (Token token : tokens) {
    //   cout << token.toString() << endl;
    // }

    if (Util::hadError) return;



    Parser parser(tokens);

    vector<Exprvp> exprs = parser.parse();
    

    if (Util::hadError) return;

    // AstPrinter asp;
    

    // for(auto expr : exprs){
    //     cout << asp.print(expr) << endl;
    // }


    

    Resolver resolver(&interpreter);
    resolver.resolve(exprs);

    // Stop if there was a resolution error.
    if (Util::hadError) return;

    interpreter.interpret(exprs);
}


int runFile(string path){
    ifstream fileStream;
    fileStream.open(path);
    if (!fileStream.is_open()){
        cout << "Could not open file: " << path << endl;
        return 74;
    }

    stringstream buffer;

    buffer << fileStream.rdbuf();

    string fileContent = buffer.str();

    fileStream.close();
    
    run(fileContent);
    
    if (Util::hadError) return 65;
    if (Util::hadRuntimeError) return 70;

    return 0;
}

void runPrompt(){
    string line = "";
    while(!cin.eof()){
        cout << "> " << endl;
        getline(cin, line);

        run(line);
        Util::hadError = false;
    }
}


int main(int argc, char *argv[]){
    if (argc > 2){
        return 64;  // https://man.freebsd.org/cgi/man.cgi?query=sysexits&apropos=0&sektion=0&manpath=FreeBSD+4.3-RELEASE&format=html
    } else if (argc == 2){
        return runFile(argv[1]);
    } else {
        runPrompt();
        
    }

    return 0;
}