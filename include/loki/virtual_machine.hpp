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

#ifndef _LOKI_VIRTUAL_MACHINE_HPP_
#define _LOKI_VIRTUAL_MACHINE_HPP_

#include <string>
#include <stack>
#include <deque>
#include <unordered_map>
#include <memory>

#include "loki/value.hpp"
#include "loki/bytecode.hpp"
#include "loki/bytecode_istream.hpp"
#include "loki/stack_action.hpp"

namespace loki {
  class virtual_machine {
    public:
      virtual_machine(const std::string& path);

      void evaluate();

    private:
      bytecode_istream _input;
      std::stack<value, std::deque<value>> _stack;
      std::unordered_map<bytecode, std::shared_ptr<stack_action>> _actions;
  };
}

#endif // _LOKI_VIRTUAL_MACHINE_HPP_
