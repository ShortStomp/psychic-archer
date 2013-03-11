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
#include <bitset>
#include <algorithm>

template<std::uint32_t T>
std::uint32_t
psy::utf8::decoder::decode_value(
  const std::uint32_t encoded_value,
  const std::vector<std::uint32_t> &x_positions
  ) const
{
  std::bitset<T> encoded_bitset(encoded_value);
  std::bitset<T> result;
  for(auto i(0U), j(0U); i < encoded_bitset.size(); ++i) {
    if(std::find(x_positions.cbegin(), x_positions.cend(), i) != x_positions.cend()) {
      result[j] = encoded_bitset[i];
      ++j;
    }
  }

  return static_cast<std::uint32_t>(result.to_ulong());
}
