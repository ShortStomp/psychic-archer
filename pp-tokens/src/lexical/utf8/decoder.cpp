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


psy::utf8::decoder::decoder(
	void
	) : _bytes_required(0U)
{
}


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
	const unsigned char byte
	) const
{
	//
	// declare return value
	unsigned int result{1U};
	
	if((byte & 0x80) == 0x00) {
		//
		// single-octet (no more bytes required)
		// (result was initialized to zero)
	}
	else if((byte & 0xE0) == 0xC0) {
		//
		// double-octet (one more byte required)
		result = 2U;
	}
	else if((byte & 0xF0) == 0xE0) {
		//
		// triple-octet (two more bytes required)
		result = 3U;
	}
	else {
		//
		// quadruple-octet (three more bytes required)
		result = 4U;
	}

	return result;	
}


std::uint32_t
psy::utf8::decoder::decode_internal_buffer(
	void
	)
{
	std::uint32_t result;

	if(_internal_buffer.size() == 1) {
  	//
    // single octet
    const psy::utf8::octet octet1(_internal_buffer.front());
    const psy::utf8::encoded_value encoded_utf(octet1);
    result = decode_utf8(encoded_utf);
  }
	else if(_internal_buffer.size() == 2) {
		//
		// double-octet		
    psy::utf8::octet octet1(_internal_buffer.front());
    psy::utf8::octet octet2(_internal_buffer.at(1));
      
		const psy::utf8::encoded_value encoded_utf(octet1, octet2);
    result = decode_utf8(encoded_utf);
  }
	else if(_internal_buffer.size() == 3) {
    //
    // triple octet
    const psy::utf8::octet octet1(_internal_buffer.front());
    const psy::utf8::octet octet2(_internal_buffer.at(1));
    const psy::utf8::octet octet3(_internal_buffer.at(2));
      
    const psy::utf8::encoded_value encoded_utf(octet1, octet2, octet3);
    result = decode_utf8(encoded_utf);
  }
  else {
    //
    // quadruple octet
    const psy::utf8::octet octet1(_internal_buffer.front());
    const psy::utf8::octet octet2(_internal_buffer.at(1));
    const psy::utf8::octet octet3(_internal_buffer.at(2));
    const psy::utf8::octet octet4(_internal_buffer.at(3));
      
    const psy::utf8::encoded_value encoded_utf(octet1, octet2, octet3, octet4);
    result = decode_utf8(encoded_utf);
  }

	//
	// reset the internal buffer
	_internal_buffer.clear();

  return result;
}


std::vector<std::uint32_t>
psy::utf8::decoder::decode(
	const unsigned char byte
	)
{
	std::vector<std::uint32_t> result;

	if(_internal_buffer.size() == 0U) {
		//
		// if the internal buffer is zero, we need to calculate how many more bytes are required
		_bytes_required = bytes_required(byte);
	}

	//
	// add 'byte' to the internal buffer for later use
	_internal_buffer.emplace_back(byte);

	//
	// update number of bytes required
	_bytes_required = (_bytes_required > 0U) ? (_bytes_required - 1U) : 0U;

	if(_bytes_required == 0U) {
		//
		// internal buffer has correct number bytes
		const auto buffer_decoded = decode_internal_buffer();
		result.emplace_back(buffer_decoded);
	}

	return result;
}
