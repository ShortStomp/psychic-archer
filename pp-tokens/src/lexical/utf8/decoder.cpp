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
#include "decoder.hpp"
#include "octet.hpp"
#include <stdexcept>
#include <vector>
#include <fstream>
#include <bitset>


std::uint32_t
psy::utf8::decoder::decode_utf8(
  const psy::utf8::encoded_value encoded_value
  ) const
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


unsigned int
psy::utf8::decoder::bytes_required(
	const std::uint32_t utf8_encoded_value
	) const
{
	//
	// assume single-octet
	unsigned int result{1U};

	if((utf8_encoded_value & 0xE0) == 0xC) {
		//
		// double-octet
		result = 2U;
	}
	else if((utf8_encoded_value & 0xF0) == 0xE0) {
		//
		// triple-octet
		result = 3U;
	}
	else {
		//
		// quadruple-octet
		result = 4U;
	}

	return result;	
}


std::uint32_t
psy::utf8::decoder::decode(
	const std::vector<unsigned char> &bytes
	) const
{
	std::uint32_t result{0U};

	if(bytes.size() == 1) {
  	//
    // single octet
    const psy::utf8::octet octet1(bytes.front());
    const psy::utf8::encoded_value encoded_utf(octet1);
    result = decode_utf8(encoded_utf);
  }
	else if(bytes.size() == 2) {
		//
		// double-octet		
    psy::utf8::octet octet1(bytes.front());
    psy::utf8::octet octet2(bytes.at(1));
      
		const psy::utf8::encoded_value encoded_utf(octet1, octet2);
    result = decode_utf8(encoded_utf);
  }
	else if(bytes.size() == 3) {
    //
    // triple octet
    const psy::utf8::octet octet1(bytes.front());
    const psy::utf8::octet octet2(bytes.at(1));
    const psy::utf8::octet octet3(bytes.at(2));
      
    const psy::utf8::encoded_value encoded_utf(octet1, octet2, octet3);
    result = decode_utf8(encoded_utf);
  }
  else {
    //
    // quadruple octet
    const psy::utf8::octet octet1(bytes.front());
    const psy::utf8::octet octet2(bytes.at(1));
    const psy::utf8::octet octet3(bytes.at(2));
    const psy::utf8::octet octet4(bytes.at(3));
      
    const psy::utf8::encoded_value encoded_utf(octet1, octet2, octet3, octet4);
    result = decode_utf8(encoded_utf);
  }

  return result;
}
