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
#include "lexical_analyzer.hpp"
#include <iostream>
#include <fstream>

#include "trigraph_system.hpp"
#include "line_splicing_system.hpp"
#include "comment_system.hpp"
#include "universal_character_system.hpp"
#include "../utf8/utf8_decoder.hpp"

void
psy::lex::analyze(
	const std::string &input_file,
	const std::string &output_file
	)
{
  psy::utf8::utf8_decoder decoder;
  const auto decoded_file = decoder.decode_file(input_file);

  const auto universal_character_names_removed = psy::lex::remove_all_ucn(decoded_file);
  const auto trigraphs_removed = psy::lex::remove_trigraphs(universal_character_names_removed);
  auto linefeeds_removed = psy::lex::remove_backslashes_followed_by_linefeed(trigraphs_removed);

  //
  // If the file does not end in a linefeed add one.
  if(linefeeds_removed.back() != '\n') {
    linefeeds_removed.emplace_back('\n');
  }

  const auto b = psy::lex::remove_comments(linefeeds_removed);

  std::wofstream outfile;
  outfile.open(output_file);

  for(auto wc : b) {
    if(wc < 120) {
      outfile << static_cast<wchar_t>(wc);
    }   
  }   
  outfile.flush();
  outfile.close();
}
