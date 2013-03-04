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
#include "utf8_decoder.hpp"
#include "octet.hpp"
#include <stdexcept>
#include <vector>
#include <fstream>
#include <bitset>


std::uint32_t
psy::utf8::utf8_decoder::decode_utf8(
  const psy::utf8::utf8_encoded_value encoded_value
  )
{ 
  std::uint32_t result(0U);

  if(encoded_value.octet_count == 1) {
    result = decode_value<16>(encoded_value.value, psy::utf8::octet::single_octet_positions);
  }
  else if(encoded_value.octet_count == 2) {
    result = decode_value<16>(encoded_value.value, psy::utf8::octet::double_octet_positions);
  }
  else if(encoded_value.octet_count == 3) {
    result = decode_value<24>(encoded_value.value, psy::utf8::octet::triple_octet_positions);
  }
  else if(encoded_value.octet_count == 4) {
    result = decode_value<32>(encoded_value.value, psy::utf8::octet::quadruple_octet_positions);
  }
  else {
    throw std::runtime_error("could not decode utf8 value.");
  }

  return result;
}


std::vector<std::uint32_t>
psy::utf8::utf8_decoder::decode_file(
  const std::string &filename
  )
{
  std::ifstream file;
  file.open(filename, std::ios::binary|std::ios::in);

  if(file.is_open() == false) {
    throw std::runtime_error("Failed to open file " + filename);
  }

  std::vector<unsigned char> buffer(4, 0);
  std::vector<std::uint32_t> decoded_utf8_values;

  while(file.good()) {
    //
    // read character, so we can see how many octets are used to encode the unicode value.
    file.read(reinterpret_cast<char*>(buffer.data()), 1);

    if(file.good() == false) {
      //
      // we have just read the end of file,
      // notice buffer has not changed.
      break;
    }

    if((buffer.front() & 0x80) == 0x00) {
      //
      // single octet
      psy::utf8::octet octet1(buffer.front());
      psy::utf8::utf8_encoded_value encoded_utf(octet1);
      const auto decoded_value = decode_utf8(encoded_utf);
      decoded_utf8_values.emplace_back(decoded_value);
    }
    else if((buffer.front() & 0xE0) == 0xC0) {
      //
      // double octet
      file.read(reinterpret_cast<char*>(&buffer[1]), 1);
      psy::utf8::octet octet1(buffer.front());
      psy::utf8::octet octet2(buffer.at(1));
      
      psy::utf8::utf8_encoded_value encoded_utf(octet1, octet2);
      const auto decoded_value = decode_utf8(encoded_utf);
      decoded_utf8_values.emplace_back(decoded_value);
    }
    else if((buffer.front() & 0xF0) == 0xE0) {
      //
      // triple octet
      file.read(reinterpret_cast<char*>(&buffer[1]), 2);
      
      psy::utf8::octet octet1(buffer.front());
      psy::utf8::octet octet2(buffer.at(1));
      psy::utf8::octet octet3(buffer.at(2));
      
      psy::utf8::utf8_encoded_value encoded_utf(octet1, octet2, octet3);
      const auto decoded_value = decode_utf8(encoded_utf);
      decoded_utf8_values.emplace_back(decoded_value);
    }
    else {
      //
      // quadruple octet
      file.read(reinterpret_cast<char*>(&buffer[1]), 3);
      if((buffer.front() & 0xF8) != 0xF0) {
        throw std::runtime_error("ill-formated utf8");
      }

      //
      // correctly-formatted quadruple octet
      psy::utf8::octet octet1(buffer.front());
      psy::utf8::octet octet2(buffer.at(1));
      psy::utf8::octet octet3(buffer.at(2));
      psy::utf8::octet octet4(buffer.at(3));
      
      psy::utf8::utf8_encoded_value encoded_utf(octet1, octet2, octet3, octet4);
      const auto decoded_value = decode_utf8(encoded_utf);
      decoded_utf8_values.emplace_back(decoded_value);
    }
  }

  return decoded_utf8_values;
}
