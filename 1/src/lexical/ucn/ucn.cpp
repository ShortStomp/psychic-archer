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
#include "../codepoint.hpp"
#include "../../conversions/conversions.hpp"
#include "../utf8/decoder.hpp"
#include "../utf8/octet.hpp"
#include "../utf8/encoder.hpp"
#include "ucn.hpp"

const unsigned int slash_u_length = 2;

const std::vector<std::uint32_t> valid_second_digits = { 'u', 'U' };


bool
check_first_digit(
  const psy::lex::codepoint code_point
  )
{
  return code_point.Value == '\\';
}


bool
check_second_digit(
  const psy::lex::codepoint code_point
  )
{
  const auto it = std::find(valid_second_digits.cbegin(), valid_second_digits.cend(), code_point.Value);
  return it != valid_second_digits.cend();
}


bool
check_third_plus_digit(
  const psy::lex::codepoint code_point
  )
{
  return isxdigit(code_point.Value) != 0;
}


bool
is_shortname(
  const psy::lex::codepoint code_point
  )
{
  return code_point.Value == 'u';
}

/*
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


void
psy::ucn::decoder::read(
  const lex::codepoint cp
  )
{
  _buffer.emplace_back(cp);
}


void
psy::ucn::decoder::reset(
  )
{
  _buffer.clear();
}

 
bool
psy::ucn::decoder::maybe_ucn(
  void
  ) const
{
  bool result(false);

  /*if(_buffer.size() == 1) {
    result = check_first_digit(_buffer.front());
  }
  else if(_buffer.size() == 2) {
    result = check_second_digit(_buffer.at(1));
  }
  else if((_buffer.size() > 2) && (is_shortname(_buffer.at(1)))) {
    for(auto i(2U); i < _buffer.size(); ++i) {
      result |= check_third_plus_digit(_buffer.at(i));
    }
  }*/

  return result;
}


psy::lex::codepoint
psy::ucn::decoder::get_codepoint(
  ) const
{
  lex::codepoint result;

  return result;
}


std::vector<psy::utf8::encoded_byte>
psy::ucn::decoder::get_encoded_bytes(
  ) const
{
  std::vector<utf8::encoded_byte> result;
  return result;
}
