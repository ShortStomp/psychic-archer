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
#include <vector>
#include <cstdint>
#include "../codepoint.hpp"
#include "../utf8/encoded_byte.hpp"
//
// namespace declaration
namespace psy
{
namespace ucn
{
	//
	// class declaration
	class decoder
	{
		//
		// members
    std::vector<lex::codepoint> _buffer;

		//
		// methods
//		bool check_first_digit(const std::uint32_t code_point) const;
//		bool check_second_digit(const std::uint32_t code_point) const;
//		bool check_third_plus_digit(const std::uint32_t code_point) const;
//		bool is_shortname(const std::uint32_t code_point) const;

//		std::uint32_t convert_ucn(void) const;

	public:
	
		//
		// methods
    void read(const lex::codepoint cp);
    void reset();
    
    bool ready() const;
    bool maybe_ucn() const;
    lex::codepoint get_codepoint() const;
    std::vector<utf8::encoded_byte> get_encoded_bytes() const;
	};
  
}
}
