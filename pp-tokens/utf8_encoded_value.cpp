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
#include "utf8_encoded_value.hpp"
#include <climits>

psychic::utf8_encoded_value::utf8_encoded_value(
  const std::uint32_t value,
  const std::uint32_t octet_count
  ) : value(value),
  octet_count(octet_count)
{

}


psychic::utf8_encoded_value::utf8_encoded_value(
  const octet octet1
  ) : value(octet1.value),
  octet_count(1)
{

}


psychic::utf8_encoded_value::utf8_encoded_value(
  const octet octet1,
  const octet octet2
  ) : value(octet1.value | (octet2.value << CHAR_BIT)),
  octet_count(2)
{
}


psychic::utf8_encoded_value::utf8_encoded_value(
  const octet octet1,
  const octet octet2,
  const octet octet3
  ) : value(octet1.value | (octet2.value << CHAR_BIT) | (octet3.value << (2 * CHAR_BIT))),
  octet_count(3)
{

}


psychic::utf8_encoded_value::utf8_encoded_value(
  const octet octet1,
  const octet octet2,
  const octet octet3,
  const octet octet4
  ) : value(octet1.value | (octet2.value << CHAR_BIT) | (octet3.value << (2 * CHAR_BIT)) | (octet4.value << (3 * CHAR_BIT))),
  octet_count(3)
{

}