/* Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Loki.
 *
 * Loki is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _LOKI_STACK_ACTION_HPP_
#define _LOKI_STACK_ACTION_HPP_

#include <stack>
#include <deque>

#include "loki/value.hpp"
#include "loki/bytecode_istream.hpp"

namespace loki {
  class stack_action {
    public:
      stack_action(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : _input(input)
        , _stack(stack) {}

      virtual void act() = 0;

    protected:
      bytecode_istream& _input;
      std::stack<value, std::deque<value>>& _stack;
  };

  class vm_push: public stack_action {
    public:
      vm_push(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : stack_action(input, stack) {}

      void act() override;
  };

  class vm_print: public stack_action {
    public:
      vm_print(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : stack_action(input, stack) {}

      void act() override;
  };

  class vm_add: public stack_action {
    public:
      vm_add(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : stack_action(input, stack) {}

      void act() override;
  };

  class vm_sub: public stack_action {
    public:
      vm_sub(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : stack_action(input, stack) {}

      void act() override;
  };

  class vm_mul: public stack_action {
    public:
      vm_mul(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : stack_action(input, stack) {}

      void act() override;
  };

  class vm_div: public stack_action {
    public:
      vm_div(
        bytecode_istream& input,
        std::stack<value, std::deque<value>>& stack
      ) : stack_action(input, stack) {}

      void act() override;
  };
}

#endif // _LOKI_STACK_ACTION_HPP_
