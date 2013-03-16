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
#include <vector>
#include "utf8_encoded.hpp"
#include "../codepoint.hpp"
//
// namespace declarations
namespace psy
{
namespace utf8
{
  //
  // class declaration
  class decoder
  {
    //
    // members
    unsigned int _required;
    std::vector<utf8_encoded> _buffer;
  
    //
    // methods
    lex::codepoint internal_decode() const; 
        
    template<std::uint32_t T>
    lex::codepoint decode_value(const std::vector<std::uint32_t> &x_positions) const;

  public:

    //
    // constructors
    decoder(void);

    //
    // methods 
    void read(const utf8_encoded &encoded_byte);
    void reset();

    bool ready() const;
    lex::codepoint get_codepoint() const;
    std::vector<unsigned char> get_bytes() const;
  }; 
}
}
#include "decoder.inc"
