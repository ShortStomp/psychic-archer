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
#include "trigraph_system.hpp"
#include "lexical_helper.hpp"
#include <string>
#include <map>

std::vector<std::uint32_t>
psychic::remove_trigraphs(
  const std::vector<std::uint32_t> &input
  )
{
  const std::uint32_t arr[9] = { '=', '/', '\'', '(', ')', '!', '<', '>', '-'};
  std::vector<char> trigraph_chars;
  trigraph_chars.assign(arr, arr + sizeof(arr) / sizeof(arr[0]));

  std::map<std::string, uint32_t> trigraph_map;
  trigraph_map.emplace("??=", '#');
  trigraph_map.emplace("??//", '\\');
  trigraph_map.emplace("??'", '^');
  trigraph_map.emplace("??(", '[');
  trigraph_map.emplace("??)", ']');
  trigraph_map.emplace("??!", '|');
  trigraph_map.emplace("??<", '{');
  trigraph_map.emplace("??>", '}');
  trigraph_map.emplace("??-", '~');

  std::vector<std::uint32_t> result;

  for(std::vector<std::uint32_t>::const_iterator it = input.cbegin(); it != input.cend(); ++it) {

    const bool enough_characters = ((it + 1) != input.cend()) && ((it + 2) != input.cend());
    if(enough_characters == false) {
      result.emplace_back(*it);
      continue;
    }

    const auto third_digit_iter = std::find(trigraph_chars.cbegin(), trigraph_chars.cend(), lex::look_ahead(it + 2, input.cend()));
    const bool third_digit_tri = third_digit_iter != trigraph_chars.cend();

    if(lex::look_ahead(it, input.cend()) == '?' && lex::look_ahead(it + 1, input.cend()) == '?' && third_digit_tri) {
      
      const auto look_ahead_zero = static_cast<char>(*it);
      const auto look_ahead_one = static_cast<char>(*(it + 1));

      std::string three_digit_string(1, look_ahead_zero);
      three_digit_string += look_ahead_one;
      three_digit_string += lex::look_ahead(it + 2, input.cend());
      it += 2;

      result.emplace_back(trigraph_map.find(three_digit_string)->second);
    }
    else {
      result.emplace_back(*it);
    }
  }

  return result;
}