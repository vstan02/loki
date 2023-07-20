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

#include "loki/value.hpp"
#include "loki/stack_action.hpp"

namespace loki {
  template <typename T>
  static inline void
  add_values(value& result, const value& left, const value& right) {
    result = value(T(std::get<T>(left.target) + std::get<T>(right.target)));
  }

  extern void vm_add::act() {
    value right = _stack.top();
    _stack.pop();
    value left = _stack.top();
    _stack.pop();

    if (left.type != right.type) {
      throw std::runtime_error("Invalid operands type");
    }

    value result;
    switch (right.type) {
      case value_type::STR:
        add_values<str>(result, left, right);
        break;
      case value_type::I8:
        add_values<i8>(result, left, right);
        break;
      case value_type::I16:
        add_values<i16>(result, left, right);
        break;
      case value_type::I32:
        add_values<i32>(result, left, right);
        break;
      case value_type::I64:
        add_values<i64>(result, left, right);
        break;
      case value_type::U8:
        add_values<u8>(result, left, right);
        break;
      case value_type::U16:
        add_values<u16>(result, left, right);
        break;
      case value_type::U32:
        add_values<u32>(result, left, right);
        break;
      case value_type::U64:
        add_values<u64>(result, left, right);
        break;
      case value_type::F32:
        add_values<f32>(result, left, right);
        break;
      case value_type::F64:
        add_values<f64>(result, left, right);
        break;
      default:
        throw std::runtime_error("Invalid operands type");
    }

    _stack.push(result);
  }
}
