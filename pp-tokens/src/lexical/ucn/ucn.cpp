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
#include "../utf8/octet.hpp"
#include "../utf8/encoded_value.hpp"
#include "ucn.hpp"

const unsigned int slash_u_length = 2;

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
	return (_ucn_buffer.size() < 2) || (isxdigit(code_point) == true);
}


bool
psy::lex::ucn::decoder::is_shortname(
	const std::uint32_t code_point
	) const
{
	return (_ucn_buffer.size() > 1) && (_ucn_buffer.at(1) == 'u');
}


std::vector<std::uint32_t>
psy::lex::ucn::decoder::parse_ucn(
	const std::uint32_t code_point
	)
{
	std::vector<std::uint32_t> result;

	if(!check_first_digit(code_point) || !check_second_digit(code_point) || !check_third_plus_digit(code_point)) { 
		//
		// invalid character detected
		result = _ucn_buffer;
		_ucn_buffer.clear();
	}

	//
	// copy the character into our internal buffer
	_ucn_buffer.emplace_back(code_point);


	if(_ucn_buffer.size() == (slash_u_length + 4) && is_shortname(code_point)) {
		//
		// unicode short-character name
		_ucn_buffer.clear();
		const auto converted = convert_ucn(_ucn_buffer);
		result.emplace_back(converted);
	}
	else if(_ucn_buffer.size() == (slash_u_length + 8) && (is_shortname(code_point) == false)) {
		//
		// unicode long-character name
		_ucn_buffer.clear();
		const auto converted = convert_ucn(_ucn_buffer);
		result.emplace_back(converted);
	}	

	return result;
}

/*
std::vector<std::uint32_t>
psy::lex::remove_all_ucn(
  const std::vector<std::uint32_t> &input
  )
{
  std::vector<std::uint32_t> result;

  for(std::vector<std::uint32_t>::const_iterator it = input.cbegin(); it != input.cend(); ++it) {

    const auto upcoming_unc = is_ucn(it, input.cend());
    if(*it == '\\' && upcoming_unc.empty() == false) {
      const psy::utf8::octet octet1(upcoming_unc.front());
      const psy::utf8::octet octet2(upcoming_unc.at(1));
      const psy::utf8::octet octet3(upcoming_unc.at(2));
      const psy::utf8::octet octet4(upcoming_unc.at(3));

      it += 4;

      psy::utf8::encoded_value value(octet1, octet2, octet3, octet4);
      result.emplace_back(value.value);
    }
    else {
      result.emplace_back(*it);
    }
  }

  return result;
}


std::vector<std::uint32_t>
psy::lex::is_ucn(
  std::vector<std::uint32_t>::const_iterator it,
  const std::vector<std::uint32_t>::const_iterator end
  )
{
  std::vector<std::uint32_t> result;

  if(it == end || (it + 1) == end) {
    return result;
  }

  const auto iter_to_next = ++it;
  if(*iter_to_next == 'u') {
    //
    // read four digits
    return parse_ucn(4, it, end);
  }

  else if(*iter_to_next == 'U') {
    return parse_ucn(8, it, end);
  }

  return result;
}
*/

std::uint32_t
psy::lex::ucn::decoder::convert_ucn(
	const std::vector<uint32_t> &ucn_digits
  ) const
{
	//1const auto count = (ucn_digits.size() == slash_u_length + 4 ? 4 : 8);
  std::vector<std::uint32_t> result;
 
	for(const auto ucn : ucn_digits) {
		if(isxdigit(ucn) == true) {
			//result   (psy::conv::hex_to_decimal(ucn));
		}
	} 

	return 0;
//  return result;
}
