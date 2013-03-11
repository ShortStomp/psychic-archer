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
#include "encoded_value.hpp"
#include <climits>

psy::utf8::encoded_value::encoded_value(
	void
	) : value(0U), octet_count(0U)
{
}


psy::utf8::encoded_value::encoded_value(
  const std::uint32_t val,
  const std::uint32_t count
  ) : value(val),
  octet_count(count)
{

}


psy::utf8::encoded_value::encoded_value(
  const octet octet1
  ) : value(octet1.value),
  octet_count(1)
{

}


psy::utf8::encoded_value::encoded_value(
  const octet octet1,
  const octet octet2
  ) : value(octet2.value | (octet1.value << CHAR_BIT)),
  octet_count(2)
{
}


psy::utf8::encoded_value::encoded_value(
  const octet octet1,
  const octet octet2,
  const octet octet3
  ) : value(octet3.value | (octet2.value << CHAR_BIT) | (octet1.value << (2 * CHAR_BIT))),
  octet_count(3)
{

}


psy::utf8::encoded_value::encoded_value(
  const octet octet1,
  const octet octet2,
  const octet octet3,
  const octet octet4
  ) : value(octet4.value | (octet3.value << CHAR_BIT) | (octet2.value << (2 * CHAR_BIT)) | (octet1.value << (3 * CHAR_BIT))),
  octet_count(4)
{

}
