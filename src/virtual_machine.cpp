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

#include <memory>

#include "loki/value.hpp"
#include "loki/bytecode.hpp"
#include "loki/bytecode_istream.hpp"
#include "loki/stack_action.hpp"
#include "loki/virtual_machine.hpp"

namespace loki {
  template <class T>
  inline std::shared_ptr<stack_action>
  make_action(bytecode_istream& input, std::stack<value, std::deque<value>> stack) {
    return std::make_shared<stack_action>(T(input, stack));
  }

  extern virtual_machine::virtual_machine(const std::string& path)
    : _input(path)
    , _stack()
    , _actions() {
      _actions[bytecode::PUSH] = make_action<vm_push>(_input, _stack);
      _actions[bytecode::PRINT] = make_action<vm_print>(_input, _stack);
      _actions[bytecode::ADD] = make_action<vm_add>(_input, _stack);
      _actions[bytecode::MUL] = make_action<vm_mul>(_input, _stack);
      _actions[bytecode::SUB] = make_action<vm_sub>(_input, _stack);
      _actions[bytecode::DIV] = make_action<vm_div>(_input, _stack);
    }

  extern void virtual_machine::evaluate() {
    bytecode code;
    do {
      _input >> code;
      if (code != bytecode::EXIT) {
        _actions[code]->act();
      }
    } while(code != bytecode::EXIT);
  }
}
