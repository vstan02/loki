#ifndef _LOKI_DEMO_TOKEN_HPP_
#define _LOKI_DEMO_TOKEN_HPP_

#include <string>
#include <utility>

namespace demo {
  enum class token_type {
    ID,
    INT,
    I8,
    I16,
    I32,
    I64,
    PUSH,
    PRINT,
    ADD,
    SUB,
    MUL,
    DIV,
    END
  };

  struct token {
    token_type type;
    std::string value;

    token(token_type type = token_type::END)
      : type(type), value() {}

    token(token_type type, const std::string& value)
      : type(type), value(value) {}

    token(token_type type, std::string&& value)
      : type(type), value(std::move(value)) {}
  };
}

#endif // _LOKI_DEMO_TOKEN_HPP_
