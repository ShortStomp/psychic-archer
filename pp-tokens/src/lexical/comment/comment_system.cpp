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
#include "lexical_helper.hpp"
#include "comment_system.hpp"


std::vector<std::uint32_t>
psy::lex::remove_comments(
  const std::vector<std::uint32_t> &input
  )
{
  std::vector<std::uint32_t> result;

  for(std::vector<std::uint32_t>::const_iterator it = input.cbegin(); it != input.cend(); ++it) {

    const bool enough_characters = (it + 1) != input.cend();
    if(enough_characters && (*it == '/')) {

      //
      // entered state for finding a comment
      if(lex::look_ahead(it + 1, input.cend()) == '/') {
      //if(char_after_first_slash == '/') {
        //
        // read characters until we get a LF "\n"
        while(*it != '\n') {
          ++it;
          lex::check_iterator(it, input.cend());
        }
        result.emplace_back(' ');
      }
      else if(lex::look_ahead(it + 1, input.cend()) == '*') {
        //
        // move iterator to character just after initial "/"
        ++it;
        
        while(lex::look_ahead(it + 1, input.cend()) != '*' && lex::look_ahead(it + 2, input.cend()) != '\\') {
          ++it;
          lex::check_iterator(it, input.cend());
        }
        it += 2;
        result.emplace_back(' ');
      }
      else {
        result.emplace_back(*it);
      }
      continue;
    }
    
    result.emplace_back(*it);
  }

  return result;
}
