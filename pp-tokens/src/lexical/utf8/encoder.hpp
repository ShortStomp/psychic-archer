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
#include <vector>
#include "encoded_value.hpp"
#include "combined_byte.hpp"
#include "utf8_encoded.hpp"
//
// namespace declarations
namespace psy
{
namespace utf8
{
  //
  // class declarations
  class encoder
  {
    //
    // methods
    template<std::uint32_t T>
    void encode_value(std::uint64_t &value, std::bitset<T> &bitset, const std::uint32_t position) const;

  public:
 
    //
    // methods
    //encoded_value encode_utf8(const std::uint64_t value) const;
		std::vector<utf8_encoded> encode(const std::vector<combined_byte> &bytes);
  };
}
}
#include "encoder.inc"
