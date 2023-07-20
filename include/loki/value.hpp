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

#ifndef _LOKI_VALUE_HPP_
#define _LOKI_VALUE_HPP_

#include <cstdint>
#include <string>
#include <variant>

namespace loki {
  using i8 = std::int8_t;
  using i16 = std::int16_t;
  using i32 = std::int32_t;
  using i64 = std::int64_t;
  using u8 = std::uint8_t;
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  using f32 = float;
  using f64 = double;
  using str = std::string;

  enum class value_type {
    NIL,
    BOOL,
    CHR,
    I8,
    I16,
    I32,
    I64,
    U8,
    U16,
    U32,
    U64,
    F32,
    F64,
    STR
  };

  struct value {
    value_type type;
    std::variant<
      bool,
      char,
      i8,
      i16,
      i32,
      i64,
      u8,
      u16,
      u32,
      u64,
      f32,
      f64,
      str
    > target;

    value()
      : type(value_type::NIL)
      , target() {}

    value(bool target)
      : type(value_type::BOOL)
      , target(target) {}

    value(char target)
      : type(value_type::CHR)
      , target(target) {}

    value(i8 target)
      : type(value_type::I8)
      , target(target) {}

    value(i16 target)
      : type(value_type::I16)
      , target(target) {}

    value(i32 target)
      : type(value_type::I32)
      , target(target) {}

    value(i64 target)
      : type(value_type::I64)
      , target(target) {}

    value(u8 target)
      : type(value_type::U8)
      , target(target) {}

    value(u16 target)
      : type(value_type::U16)
      , target(target) {}

    value(u32 target)
      : type(value_type::U32)
      , target(target) {}

    value(u64 target)
      : type(value_type::U64)
      , target(target) {}

     value(f32 target)
      : type(value_type::F32)
      , target(target) {}

    value(f64 target)
      : type(value_type::F64)
      , target(target) {}

    value(const str& target)
      : type(value_type::F64)
      , target(target) {}

    value(str&& target)
      : type(value_type::F64)
      , target(std::move(target)) {}
  };
}

#endif // _LOKI_VALUE_HPP_
