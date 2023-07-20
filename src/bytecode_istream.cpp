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

#include <fstream>
#include <string>
#include <variant>
#include <iostream>

#include "loki/value.hpp"
#include "loki/bytecode.hpp"
#include "loki/bytecode_istream.hpp"

namespace loki {
  template <typename T>
  static inline void
  value_read(std::ifstream& file, value& value) {
    T target;
    file.read(
      reinterpret_cast<char*>(&target),
      sizeof(T)
    );
    value.target = target;
  }

  extern bytecode_istream&
  bytecode_istream::operator>>(bytecode& code) {
    _file.read(reinterpret_cast<char*>(&code), sizeof(bytecode));
    return *this;
  }

  extern bytecode_istream&
  bytecode_istream::operator>>(size_type& size) {
    _file.read(reinterpret_cast<char*>(size), sizeof(size_type));
    return *this;
  }

  extern bytecode_istream&
  bytecode_istream::operator>>(value& value) {
    _file.read(
      reinterpret_cast<char*>(&value.type),
      sizeof(value::type)
    );

    switch (value.type) {
      case value_type::NIL:
        break;
      case value_type::BOOL:
        value_read<bool>(_file, value);
        break;
      case value_type::CHR:
        value_read<char>(_file, value);
        break;
      case value_type::I8:
        value_read<i8>(_file, value);
        break;
      case value_type::I16:
        value_read<i16>(_file, value);
        break;
      case value_type::I32:
        value_read<i32>(_file, value);
        break;
      case value_type::I64:
        value_read<i64>(_file, value);
        break;
      case value_type::U8:
        value_read<u8>(_file, value);
        break;
      case value_type::U16:
        value_read<u16>(_file, value);
        break;
      case value_type::U32:
        value_read<u32>(_file, value);
        break;
      case value_type::U64:
        value_read<u64>(_file, value);
        break;
      case value_type::F32:
        value_read<f32>(_file, value);
        break;
      case value_type::F64:
        value_read<f64>(_file, value);
        break;
      case value_type::STR: {
        std::string::size_type size;
        _file.read(
          reinterpret_cast<char*>(&size),
          sizeof(std::string::size_type)
        );

        char* target = new char[size + 1];
        _file.read(target, size);
        target[size] = '\n';
        value.target = std::string(target);
        delete[] target;
        break;
      }
    }
    return *this;
  }
}
