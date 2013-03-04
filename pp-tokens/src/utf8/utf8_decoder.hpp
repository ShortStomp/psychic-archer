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
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <string>
#include <vector>
#include "utf8_encoded_value.hpp"
//
// namespace declarations
namespace psy
{
namespace utf8
{
  //
  // class declaration
  class utf8_decoder
  {
    //
    // members
    std::vector<std::uint32_t> _single_octet_positions;
    std::vector<std::uint32_t> _double_octet_positions;
    std::vector<std::uint32_t> _triple_octet_positions;
    std::vector<std::uint32_t> _quadruple_octet_positions;

    //
    // methods
    template<std::uint32_t T>
    std::uint32_t decode_value(const std::uint32_t encoded_value, std::vector<std::uint32_t> &x_positions) const;

  public:

    //
    // constructors
    utf8_decoder(void);

    //
    // methods
    std::uint32_t decode_utf8(const psy::utf8::utf8_encoded_value encoded_value);
    std::vector<std::uint32_t> decode_file(const std::string &filename);
  };
  
}
}
#include "utf8_decoder.inc"
