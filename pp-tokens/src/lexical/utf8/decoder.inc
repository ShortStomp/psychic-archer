/*
  * Copyright (c) 2013 Benjamin Adamson
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
  * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  * IN THE SOFTWARE.
*/
#pragma once
#include <climits>
#include <bitset>
#include <algorithm>
#include "../codepoint.hpp"

template<std::uint32_t T>
psy::lex::codepoint
psy::utf8::decoder::decode_value(
  const std::vector<std::uint32_t> &x_positions
  ) const
{
  const auto val0 = _buffer.at(0).get().get();
  const auto val1 = _buffer.size() > 1 ? _buffer.at(1).get().get() : 0;
  const auto val2 = _buffer.size() > 2 ? _buffer.at(2).get().get() : 0;
  const auto val3 = _buffer.size() > 3 ? _buffer.at(3).get().get() : 0;
  const auto encoded_value = ((((val3 << (CHAR_BIT * 3)) | (val2 << (CHAR_BIT * 2))) | (val1 << CHAR_BIT)) | (val0)); 

  std::bitset<T> encoded_bitset(encoded_value);
  std::bitset<T> bit_buffer;
  for(auto i(0U), j(0U); i < encoded_bitset.size(); ++i) {
    if(std::find(x_positions.cbegin(), x_positions.cend(), i) != x_positions.cend()) {
      bit_buffer[j] = encoded_bitset[i];
      ++j;
    }
  }

  lex::codepoint result;
  result.Value = static_cast<std::int32_t>(bit_buffer.to_ulong());
  
  return result;
}
