#ifndef _LOKI_DEMO_LEXER_HPP_
#define _LOKI_DEMO_LEXER_HPP_

#include <string>

#include "token.hpp"

namespace demo {
  class lexer {
    public:
      lexer(const std::string& code)
        : _end(code.cend())
        , _start()
        , _current(code.cbegin()) {}

      token next();

    private:
      std::string::const_iterator _end;
      std::string::const_iterator _start;
      std::string::const_iterator _current;

    private:
      void skip_whitespaces();

      token make_kw_or_id();
      token make_number();
  };
}

#endif // _LOKI_DEMO_LEXER_HPP_
