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

#include "loki/bytecode.hpp"
#include "loki/value.hpp"
#include "loki/bytecode_ostream.hpp"

namespace loki {
  template <typename T>
  static inline void
  value_write(std::ofstream& file, const value& value) {
    file.write(
      reinterpret_cast<const char*>(&std::get<T>(value.target)),
      sizeof(T)
    );
  }

  extern bytecode_ostream&
  bytecode_ostream::operator<<(bytecode code) {
    _file.write(reinterpret_cast<const char*>(&code), sizeof(bytecode));
    return *this;
  }

  extern bytecode_ostream&
  bytecode_ostream::operator<<(size_type size) {
    _file.write(reinterpret_cast<const char*>(&size), sizeof(size_type));
    return *this;
  }

  extern bytecode_ostream&
  bytecode_ostream::operator<<(const value& value) {
    _file.write(
      reinterpret_cast<const char*>(&value.type),
      sizeof(value::type)
    );

    switch (value.type) {
      case value_type::NIL:
        break;
      case value_type::BOOL:
        value_write<bool>(_file, value);
        break;
      case value_type::CHR:
        value_write<char>(_file, value);
        break;
      case value_type::I8:
        value_write<i8>(_file, value);
        break;
      case value_type::I16:
        value_write<i16>(_file, value);
        break;
      case value_type::I32:
        value_write<i32>(_file, value);
        break;
      case value_type::I64:
        value_write<i64>(_file, value);
        break;
      case value_type::U8:
        value_write<u8>(_file, value);
        break;
      case value_type::U16:
        value_write<u16>(_file, value);
        break;
      case value_type::U32:
        value_write<u32>(_file, value);
        break;
      case value_type::U64:
        value_write<u64>(_file, value);
        break;
      case value_type::F32:
        value_write<f32>(_file, value);
        break;
      case value_type::F64:
        value_write<f64>(_file, value);
        break;
      case value_type::STR: {
        const auto& target = std::get<std::string>(value.target);
        std::string::size_type size = target.size();
        _file.write(
          reinterpret_cast<const char*>(&size),
          sizeof(std::string::size_type)
        );
        _file.write(target.c_str(), target.size());
        break;
      }
    }
    return *this;
  }
}
