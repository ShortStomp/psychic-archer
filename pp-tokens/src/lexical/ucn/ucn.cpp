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
#include <cctype>
#include <vector>
#include <algorithm>
#include "../../conversions/conversions.hpp"
#include "../utf8/decoder.hpp"
#include "../utf8/octet.hpp"
#include "../utf8/encoder.cpp"
#include "../utf8/encoded_value.hpp"
#include "ucn.hpp"

/*const unsigned int slash_u_length = 2;

const std::vector<std::uint32_t> valid_second_digits = { 'u', 'U' };


bool
psy::lex::ucn::decoder::check_first_digit(
   const std::uint32_t code_point
  ) const
{
  return (_ucn_buffer.empty() == false) || ((_ucn_buffer.empty() == true) && (code_point == '\\'));
}


bool
psy::lex::ucn::decoder::check_second_digit(
  const std::uint32_t code_point
  ) const
{
  const auto it = std::find(valid_second_digits.cbegin(), valid_second_digits.cend(), code_point);
  return (_ucn_buffer.size() != 1) || (it != valid_second_digits.cend());
}


bool
psy::lex::ucn::decoder::check_third_plus_digit(
  const std::uint32_t code_point
  ) const
{
  return (_ucn_buffer.size() < 2) || (isxdigit(code_point) != 0);
}


bool
psy::lex::ucn::decoder::is_shortname(
  const std::uint32_t code_point
  ) const
{
  return (_ucn_buffer.size() > 1) && (_ucn_buffer.at(1) == 'u');
}


std::vector<std::uint32_t>
psy::lex::ucn::decoder::decode(
  const std::uint32_t code_point
  )
{
  std::vector<std::uint32_t> result;

  if(!check_first_digit(code_point) || !check_second_digit(code_point) || !check_third_plus_digit(code_point)) { 
    //
    // invalid character detected
    std::copy(_ucn_buffer.cbegin(), _ucn_buffer.cend(), result.begin());
    _ucn_buffer.clear();

    return result;
  }

  //
  // copy the character into our internal buffer
  _ucn_buffer.emplace_back(code_point);


  if(_ucn_buffer.size() == (slash_u_length + 4) && is_shortname(code_point)) {
    //
    // unicode short-character name
    const auto converted = convert_ucn();
    _ucn_buffer.clear();  
    result.emplace_back(converted);
//    result = _ucn_buffer;
  }
  else if(_ucn_buffer.size() == (slash_u_length + 8) && (is_shortname(code_point) == false)) {
    //
    // unicode long-character name  
    const auto converted = convert_ucn();
    result.emplace_back(converted);
    _ucn_buffer.clear();
  } 

  return result;
}


std::uint32_t
psy::lex::ucn::decoder::convert_ucn(
  void
  ) const
{
  std::vector<std::uint32_t> result;
  utf8::decoder decoder;

  utf8::encoder encoder;  

  const std::uint32_t a = _ucn_buffer.at(3) | (_ucn_buffer.at(2) << 8);
  const std::uint32_t b = _ucn_buffer.at(4) | (_ucn_buffer.at(3) << 8);

  utf8::octet o1(_ucn_buffer.at(2));
  utf8::octet o2(_ucn_buffer.at(3))

  encoder.encode_utf8(octet);

  result = decoder.decode(a);
  result = decoder.decode(b);

  return result.front(); 
 
  for(const auto ucn : ucn_digits) {
    //
    // isxdigit() returns non-zero if value is a hexadecimal digit
    if(isxdigit(ucn) != 0) {
      //
      // when we get to the end of the ucn_digits result will be populated correctly.
      result = decoder.decode(ucn);
    }
  } 

  return 0;
}*/
