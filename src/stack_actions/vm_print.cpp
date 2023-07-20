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

#include <iostream>
#include <iomanip>

#include "loki/value.hpp"
#include "loki/stack_action.hpp"

namespace loki {
  extern void vm_print::act() {
    value args;
    _input >> args;
    if (args.type != value_type::I64) {
      throw std::runtime_error("Invalid size type for 'print'");
    }

    i64 size = std::get<i64>(args.target);
    for (i64 i = 0; i < size && !_stack.empty(); ++i) {
      const auto& value = _stack.top();
      switch (value.type) {
        case value_type::NIL:
          std::cout << "nil";
          break;
        case value_type::CHR:
          std::cout << std::get<char>(value.target);
          break;
        case value_type::BOOL:
          std::cout << std::boolalpha << std::get<bool>(value.target);
          break;
        case value_type::STR:
          std::cout << std::get<str>(value.target);
          break;
        case value_type::I8:
          std::cout << (int) std::get<i8>(value.target);
          break;
        case value_type::I16:
          std::cout << std::get<i16>(value.target);
          break;
        case value_type::I32:
          std::cout << std::get<i32>(value.target);
          break;
        case value_type::I64:
          std::cout << std::get<i64>(value.target);
          break;
        case value_type::U8:
          std::cout << (int) std::get<u8>(value.target);
          break;
        case value_type::U16:
          std::cout << std::get<u16>(value.target);
          break;
        case value_type::U32:
          std::cout << std::get<u32>(value.target);
          break;
        case value_type::U64:
          std::cout << std::get<u64>(value.target);
          break;
        case value_type::F32:
          std::cout << std::get<f32>(value.target);
          break;
        case value_type::F64:
          std::cout << std::get<f64>(value.target);
          break;
      }
      _stack.pop();
      std::cout << ' ';
    }

    std::cout << '\n';
  }
}
