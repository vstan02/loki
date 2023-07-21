#ifndef _LOKI_DEMO_COMPILER_HPP_
#define _LOKI_DEMO_COMPILER_HPP_

#include "token.hpp"
#include <string>
#include <fstream>

#include <loki/bytecode_ostream.hpp>

namespace demo {
  class compiler {
    public:
      compiler(const std::string& in, const std::string out)
        : _input(in)
        , _output(out) {}

      void compile();

    private:
      std::ifstream _input;
      loki::bytecode_ostream _output;

    private:
      void compile_line(const std::string& line);

      // Returns true if the next token is the type of the integer
      bool write_int(const token& current, const token& next);
  };
}

#endif // _LOKI_DEMO_COMPILER_HPP_
