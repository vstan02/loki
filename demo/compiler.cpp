#include <string>
#include <iostream>
#include <cstdlib>

#include <loki/value.hpp>
#include <loki/bytecode.hpp>

#include "token.hpp"
#include "lexer.hpp"
#include "compiler.hpp"

namespace demo {
  extern void compiler::compile() {
    if (!_input.is_open()) {
      std::cerr << "ERROR: Couldn't open the input file.\n";
      std::exit(1);
    }

    std::string line;
    while (std::getline(_input, line)) {
      compile_line(line);
    }
    _output << loki::bytecode::EXIT;
  }

  extern void compiler::compile_line(const std::string& line) {
    lexer lexer(line);
    token current(lexer.next());
    bool go_next;

    while (current.type != token_type::END) {
      go_next = true;

      switch (current.type) {
        case token_type::INT: {
          token prev = current;
          current = lexer.next();
          go_next = write_int(prev, current);
          break;
        }
        case token_type::PUSH:
          _output << loki::bytecode::PUSH;
          break;
        case token_type::PRINT:
          _output << loki::bytecode::PRINT;
          break;
        case token_type::ADD:
          _output << loki::bytecode::ADD;
          break;
        case token_type::SUB:
          _output << loki::bytecode::SUB;
          break;
        case token_type::MUL:
          _output << loki::bytecode::MUL;
          break;
        case token_type::DIV:
          _output << loki::bytecode::DIV;
          break;
        default: return;
      }

      if (go_next) {
        current = lexer.next();
      }
    }
  }

  // Returns true if the next token is a type
  extern bool compiler::write_int(const token& current, const token& next) {
    auto literal = loki::i64(std::strtoll(current.value.data(), nullptr, 10));

    switch (next.type) {
      case token_type::I8:
        _output << loki::value(loki::i8(literal));
        return true;
      case token_type::I16:
        _output << loki::value(loki::i16(literal));
        return true;
      case token_type::I32:
        _output << loki::value(loki::i32(literal));
        return true;
        case token_type::I64:
        _output << loki::value(loki::i64(literal));
        return true;
      default:
        _output << loki::value(loki::i64(literal));
        return false;
    }
  }
}
