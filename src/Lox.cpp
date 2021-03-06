#include "Lox.h"
#include "Lexer.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Lox::run(std::string source) {
  Lexer lexer = Lexer(source);
  std::vector<Token> tokens = lexer.scanTokens();

  for (Token &token : tokens) {
    std::cout << token.type << std::endl;
  }
}

void Lox::runFile(std::string path) {
  std::ifstream stream(path);
  if (!stream.good())
    std::cout << "File not found: " << path << std::endl;

  std::stringstream sstr;
  sstr << stream.rdbuf();
  run(sstr.str());
  if (hadError)
    exit(65);
}

void Lox::runPrompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    std::cin >> line;
    if (line.empty())
      break;
    run(line);
    hadError = false;
  }
}

void Lox::error(int line, std::string message) { report(line, "", message); }

void Lox::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << std::to_string(line) << "] Error" << where << ": "
            << message << std::endl;
  hadError = true;
}