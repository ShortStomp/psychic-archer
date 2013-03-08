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
#include "../../conversions/conversions.hpp"
#include "../utf8/octet.hpp"
#include "../utf8/encoded_value.hpp"
#include "ucn.hpp"

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


std::vector<std::uint32_t>
psy::lex::parse_ucn(
	const std::uint32_t count,
  std::vector<std::uint32_t>::const_iterator it,
  const std::vector<std::uint32_t>::const_iterator end
  )
{
  std::vector<std::uint32_t> result;

  for(auto i(0U); i < count; ++i) {
    ++it;
    if((it == end) || isxdigit(*it) == false) {
      result.clear();
      break;
    }
    result.emplace_back(psy::conv::hex_to_decimal(*it));
  }

  return result;
}
