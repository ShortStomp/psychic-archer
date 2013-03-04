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
#include "utf8_encoder.hpp"
#include "utf8_encoded_value.hpp"
#include <stdexcept>
#include <bitset>


psy::utf8::utf8_encoder::utf8_encoder(
  void
  )
{
  const std::uint32_t single_array[7] = { 0, 1, 2, 3, 4, 5, 6};
  _single_octet_positions.assign(single_array, single_array + sizeof(single_array) / sizeof(single_array[0]));

  const std::uint32_t double_array[11] = { 0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12};
  _double_octet_positions.assign(double_array, double_array + sizeof(double_array) / sizeof(double_array[0]));

  const std::uint32_t triple_array[16] = { 0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 16, 17, 18, 19};
  _triple_octet_positions.assign(triple_array, triple_array + sizeof(triple_array) / sizeof(triple_array[0]));

  const std::uint32_t quad_array[21] = { 0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 16, 17, 18, 19, 20, 21, 24, 25, 26};
  _quadruple_octet_positions.assign(quad_array, quad_array + sizeof(quad_array) / sizeof(quad_array[0]));
}


psy::utf8::utf8_encoded_value
psy::utf8::utf8_encoder::encode_single_octet(
  const std::uint64_t value
  ) const
{
  std::bitset<8> single_octet(value);
  single_octet.set(7, false);

  const auto bitset_long = single_octet.to_ulong();
  const auto bitset_uint32 = static_cast<std::uint32_t>(bitset_long);
  return utf8_encoded_value(bitset_uint32, 1);
}


psy::utf8::utf8_encoded_value
psy::utf8::utf8_encoder::encode_double_octet(
  std::uint64_t value
  ) const
{
  std::bitset<16> double_octet;
  double_octet.set(15, true);
  double_octet.set(14, true);
  double_octet.set(13, false);
  double_octet.set(7, true);
  double_octet.set(6, false);

  for(const auto it : _double_octet_positions) {
    encode_value<16>(value, double_octet, it);
  }

  const auto bitset_long = double_octet.to_ulong();
  const auto bitset_uint32 = static_cast<std::uint32_t>(bitset_long);
  return utf8_encoded_value(bitset_uint32, 2);
}


psy::utf8::utf8_encoded_value
psy::utf8::utf8_encoder::encode_triple_octet(
  std::uint64_t value
  ) const
{
  std::bitset<24> triple_octet;
  triple_octet.set(23, true);
  triple_octet.set(22, true);
  triple_octet.set(21, true);
  triple_octet.set(20, false);

  triple_octet.set(15, true);
  triple_octet.set(14, false);

  triple_octet.set(7, true);
  triple_octet.set(6, false);

  for(const auto it : _triple_octet_positions) {
    encode_value<24>(value, triple_octet, it);
  }

  const auto bitset_long = triple_octet.to_ulong();
  const auto bitset_uint32 = static_cast<std::uint32_t>(bitset_long);
  return utf8_encoded_value(bitset_uint32, 3);
}


psy::utf8::utf8_encoded_value
psy::utf8::utf8_encoder::encode_quadruple_octet(
  std::uint64_t value
  ) const
{
  std::bitset<32> quadruple_octet;
  quadruple_octet.set(31, true);
  quadruple_octet.set(30, true);
  quadruple_octet.set(29, true);
  quadruple_octet.set(28, true);
  quadruple_octet.set(27, false);

  quadruple_octet.set(23, true);
  quadruple_octet.set(22, false);

  quadruple_octet.set(15, true);
  quadruple_octet.set(14, false);

  quadruple_octet.set(7, true);
  quadruple_octet.set(6, false);

  for(const auto it : _quadruple_octet_positions) {
    encode_value<32>(value, quadruple_octet, it);
  }

  const auto bitset_long = quadruple_octet.to_ulong();
  const auto bitset_uint32 = static_cast<std::uint32_t>(bitset_long);
  return utf8_encoded_value(bitset_uint32, 4);
}


psy::utf8::utf8_encoded_value
psy::utf8::utf8_encoder::encode_utf8(
  const std::uint64_t value
  ) const
{
  psy::utf8::utf8_encoded_value result;

  if(value <= 0x0000007F) {
    result = encode_single_octet(value);
  }
  else if(value <= 0x000007FF) {
    result = encode_double_octet(value);
  }
  else if(value <= 0x0000FFFF) {
    result = encode_triple_octet(value);
  }
  else if(value <= 0x0010FFFF) {
    result = encode_quadruple_octet(value);
  }
  else {
    throw std::runtime_error("value passed into encode_utf8 exceeds max utf8 value.");
  }

  return result;
}
