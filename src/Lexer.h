#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Token.h"

class Lexer {
private:
  std::string m_Source;
  std::vector<Token> m_Tokens{};
  int m_Start = 0;
  int m_Current = 0;
  int m_Line = 0;
  std::unordered_map<std::string, TokenType> m_Keywords = {
      {"and", AND},   {"class", CLASS}, {"else", ELSE},     {"false", FALSE},
      {"for", FOR},   {"fun", FUN},     {"if", IF},         {"nil", NIL},
      {"or", OR},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
      {"this", THIS}, {"true", TRUE},   {"var", VAR},       {"while", WHILE}};

private:
  bool isAtEnd();
  void scanToken();
  char advance();
  void addToken(TokenType type);
  bool match(char expected);
  char peek();
  char peekNext();
  bool isDigit(char c);
  void string();
  void number();
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);
  void identifier();

  template <typename T> void addToken(TokenType type, T literal);

public:
  Lexer(std::string source) : m_Source(source){};
  ~Lexer(){};
  std::vector<Token> scanTokens();
};