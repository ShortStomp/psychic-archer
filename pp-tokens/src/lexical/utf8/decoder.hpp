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
#include "encoded_value.hpp"
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
		unsigned int _bytes_required;
		std::vector<std::uint32_t> _internal_buffer;
	
  	//
  	// methods
		unsigned int bytes_required(const unsigned char byte) const;
		std::uint32_t decode_internal_buffer(void);		
		std::uint32_t decode_utf8(const psy::utf8::encoded_value encoded_value) const;	
		
  	template<std::uint32_t T>
  	std::uint32_t decode_value(const std::uint32_t encoded_value, const std::vector<std::uint32_t> &x_positions) const;

	public:

		//
		// constructors
		decoder(void);

		//
		// methods
		std::vector<std::uint32_t> decode(const unsigned char byte);
	}; 
}
}
#include "decoder.inc"
