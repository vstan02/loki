#include <string>
#include <cctype>
#include <iostream>

#include "token.hpp"
#include "lexer.hpp"

namespace demo {
  struct keyword {
    token_type type;
    std::string target;
  };

  static keyword keywords[] = {
    { token_type::I8, "i8" },
    { token_type::I16, "i16" },
    { token_type::I32, "i32" },
    { token_type::I64, "i64" },
    { token_type::PUSH, "push" },
    { token_type::PRINT, "print" },
    { token_type::ADD, "add" },
    { token_type::SUB, "sub" },
    { token_type::MUL, "mul" },
    { token_type::DIV, "div" }
  };

  extern token lexer::next() {
    skip_whitespaces();

    _start = _current;
    if (_current == _end) {
      return token();
    }

    char ch = *(_current++);
    if (std::isdigit(ch)) {
      return make_number();
    }

    if (std::isalnum(ch) || ch == '_') {
      return make_kw_or_id();
    }

    std::cerr << "ERROR: Unexpected token.\n";
    std::exit(1);
  }

  extern void lexer::skip_whitespaces() {
    while (true) {
      switch (*_current) {
        case ' ':
        case '\r':
        case '\t':
        case '\n':
          ++_current;
          break;
        default: return;
      }
    }
  }

  extern token lexer::make_number() {
    while (std::isdigit(*_current)) {
      ++_current;
    }
    return token(token_type::INT, std::string(_start, _current));
  }

  extern token lexer::make_kw_or_id() {
    while (std::isalnum(*_current) || *_current == '_') {
      ++_current;
    }

    std::string value(_start, _current);
    for (const auto& kw: keywords) {
      if (kw.target == value) {
        return token(kw.type);
      }
    }
    return token(token_type::ID, std::string(_start, _current));
  }
}
