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
#include <climits>
#include "combined_byte.hpp"


unsigned char
combine_bytes(
	const unsigned char byte1,
	const unsigned char byte2
	)
{
	return ((byte2 << (CHAR_BIT / 2)) | byte1);
}


psy::utf8::combined_byte::combined_byte(
	const unsigned char combined_byte
	) : _byte(combined_byte)
{
}


psy::utf8::combined_byte::combined_byte(
	const unsigned char byte1,
	const unsigned char byte2
	) : _byte(combine_bytes(byte1, byte2))
{
}


unsigned char
psy::utf8::combined_byte::get(
	void
	) const
{
	return _byte; 
}
