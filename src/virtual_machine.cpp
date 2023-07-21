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
  extern virtual_machine::virtual_machine(const std::string& path)
    : _input(path)
    , _stack()
    , _actions({
      { bytecode::PUSH, std::make_shared<vm_push>(_input, _stack) },
      { bytecode::PRINT, std::make_shared<vm_print>(_input, _stack) },
      { bytecode::ADD, std::make_shared<vm_add>(_input, _stack) },
      { bytecode::SUB, std::make_shared<vm_sub>(_input, _stack) },
      { bytecode::MUL, std::make_shared<vm_mul>(_input, _stack) },
      { bytecode::DIV, std::make_shared<vm_div>(_input, _stack) }
    }) {}

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
