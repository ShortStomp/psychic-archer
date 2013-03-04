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
#include <utility>
#include <vector>
#include <unordered_set>

#include "trigraph_system.hpp"
#include "line_splicing_system.hpp"
#include "comment_system.hpp"
#include "universal_character_system.hpp"
#include "../utf8/utf8_decoder.hpp"
#include "token_type.hpp"

//
// See C++ Standard 2.11 Identifiers and Appendix/Annex E.1
const std::vector<std::pair<int, int>> annex_e1_allowed_ranges =
{
	{0xA8,0xA8},
	{0xAA,0xAA},
	{0xAD,0xAD},
	{0xAF,0xAF},
	{0xB2,0xB5},
	{0xB7,0xBA},
	{0xBC,0xBE},
	{0xC0,0xD6},
	{0xD8,0xF6},
	{0xF8,0xFF},
	{0x100,0x167F},
	{0x1681,0x180D},
	{0x180F,0x1FFF},
	{0x200B,0x200D},
	{0x202A,0x202E},
	{0x203F,0x2040},
	{0x2054,0x2054},
	{0x2060,0x206F},
	{0x2070,0x218F},
	{0x2460,0x24FF},
	{0x2776,0x2793},
	{0x2C00,0x2DFF},
	{0x2E80,0x2FFF},
	{0x3004,0x3007},
	{0x3021,0x302F},
	{0x3031,0x303F},
	{0x3040,0xD7FF},
	{0xF900,0xFD3D},
	{0xFD40,0xFDCF},
	{0xFDF0,0xFE44},
	{0xFE47,0xFFFD},
	{0x10000,0x1FFFD},
	{0x20000,0x2FFFD},
	{0x30000,0x3FFFD},
	{0x40000,0x4FFFD},
	{0x50000,0x5FFFD},
	{0x60000,0x6FFFD},
	{0x70000,0x7FFFD},
	{0x80000,0x8FFFD},
	{0x90000,0x9FFFD},
	{0xA0000,0xAFFFD},
	{0xB0000,0xBFFFD},
	{0xC0000,0xCFFFD},
	{0xD0000,0xDFFFD},
	{0xE0000,0xEFFFD}
};

//
// See C++ standard 2.11 Identifiers and Appendix/Annex E.2
const std::vector<std::pair<int, int>> annex_e2_disallowed_initially =
{
	{0x300,0x36F},
	{0x1DC0,0x1DFF},
	{0x20D0,0x20FF},
	{0xFE20,0xFE2F}
};

//
// See C++ standard 2.13 Operators and punctuators
const std::unordered_set<std::string> digraph_identifier_like_operators =
{
	"new", "delete", "and", "and_eq", "bitand",
	"bitor", "compl", "not", "not_eq", "or",
	"or_eq", "xor", "xor_eq"
};

//
// See `simple-escape-sequence` grammar
const std::unordered_set<int> simple_escape_sequence_code_points =
{
	'\'', '"', '?', '\\', 'a', 'b', 'f', 'n', 'r', 't', 'v'
};


void
psy::lex::analyze(
	const std::string &input_file,
	const std::string &output_file
	)
{
  psy::utf8::utf8_decoder decoder;
  const auto decoded_file = decoder.decode_file(input_file);

  const auto ucnr = psy::lex::remove_all_ucn(decoded_file);
  const auto trigraphs_rm = psy::lex::remove_trigraphs(ucnr);
  auto linefeeds_rm = psy::lex::remove_backslashes_followed_by_linefeed(trigraphs_rm);

  //
  // if the file does not end in a linefeed add one.
  if(linefeeds_rm.back() != '\n') {
    linefeeds_rm.emplace_back('\n');
  }

  const auto comments_removed = psy::lex::remove_comments(linefeeds_rm);

  std::wofstream outfile;
  outfile.open(output_file);

  for(auto wc : comments_removed) {
    if(wc < 120) {
      outfile << static_cast<wchar_t>(wc);
    }   
  }   
  outfile.flush();
  outfile.close();
}
