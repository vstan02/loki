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

#ifndef _LOKI_BYTECODE_HPP_
#define _LOKI_BYTECODE_HPP_

#include <cstddef>
#include <cstdint>

namespace loki {
  using size_type = std::size_t;

  enum class bytecode: std::int8_t {
    PUSH,
    PRINT,
    ADD,
    SUB,
    MUL,
    DIV,
    EXIT
  };
}

#endif // _LOKI_BYTECODE_HPP_
