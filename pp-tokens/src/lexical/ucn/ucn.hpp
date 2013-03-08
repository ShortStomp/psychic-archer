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
//
// namespace declaration
namespace psy
{
namespace lex
{
namespace ucn
{
	//
	// class declaration
	class decoder
	{
		//
		// members
		bool _begin_slash;
		bool _short_name;
		unsigned int _hex_count;

	public:
	
		//
		// methods
		unsigned int parse_ucn(const std::uint32_t code_point);

	};
  //
  // function declaration
  //std::vector<std::uint32_t> remove_all_ucn(const std::vector<std::uint32_t> &input);
  //std::vector<std::uint32_t> is_ucn(std::vector<std::uint32_t>::const_iterator it, const std::vector<std::uint32_t>::const_iterator end);
  //std::vector<std::uint32_t> parse_ucn(const std::uint32_t count, std::vector<std::uint32_t>::const_iterator it, const std::vector<std::uint32_t>::const_iterator end);
}
}
}
