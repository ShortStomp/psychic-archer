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
#include <exception>
#include <iostream>
#include <fstream>

#include "trigraph_system.hpp"
#include "utf8-decoder.hpp"
#include "line_splicing_system.hpp"
#include "comment_system.hpp"
#include "universal_character_system.hpp"

int main(int argc, char *argv[])
{  
  try {
    psychic::utf8_decoder decoder;
    const auto decoded_file = decoder.decode_file("test.bin");

    const auto universal_character_names_removed = psychic::remove_all_universal_character_names(decoded_file);
    const auto trigraphs_removed = psychic::remove_trigraphs(universal_character_names_removed);
    auto linefeeds_removed = psychic::remove_backslashes_followed_by_linefeed(trigraphs_removed);

    //
    // If the file does not end in a linefeed add one.
    if(linefeeds_removed.back() != '\n') {
      linefeeds_removed.emplace_back('\n');
    }

    const auto b = psychic::remove_comments(linefeeds_removed);

    std::wofstream outfile;
    outfile.open("out.bin");

    for(auto wc : b) {
      if(wc < 120) {
        outfile << static_cast<wchar_t>(wc);
      }
    }
    outfile.flush();
    outfile.close();


    // Comments (/* ... */ and // ...) are replaced by a space character
    // (ie they are part of a non-empty whitespace-sequence)

    /*auto encoded = encoder.encode_utf8(0x25);
    auto decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(1024);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(734);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(8192);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(16384);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(32768);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(45868);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(65536);
    decoded = encoder.decode_utf8(encoded);

    encoded = encoder.encode_utf8(65537);
    decoded = encoder.decode_utf8(encoded);
    __debugbreak();*/
    
  }
  catch(std::exception &e) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}