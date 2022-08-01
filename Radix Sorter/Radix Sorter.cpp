#include <iostream>
#include "RadixSorter.h"

//my data type of 80 bits!!
struct mynewdatatype {
	int64_t low64bits;
	int16_t high16bits;

	mynewdatatype operator+(mynewdatatype& other) {
		mynewdatatype retval;
		retval.low64bits = low64bits + other.low64bits;
		retval.high16bits = high16bits + other.high16bits;
		return retval;
	}

	mynewdatatype operator-(mynewdatatype& other) {
		mynewdatatype retval;
		retval.low64bits = low64bits - other.low64bits;
		retval.high16bits = high16bits - other.high16bits;
		return retval;
	}

	mynewdatatype operator=(int val) {
		mynewdatatype retval;
		retval.high16bits = 0;
		retval.low64bits = val;
		return retval;
	}

	operator size_t() {
		return (size_t)low64bits;
	}

	mynewdatatype operator &(uint8_t val) {
		mynewdatatype retval;
		retval.high16bits = 0;
		retval.low64bits = low64bits & val;
		return retval;
	}

	mynewdatatype operator<<(uint64_t val) {
		mynewdatatype retval = *this;
		for (uint64_t i = 0; i < val / 8; i++) {
			retval.high16bits = retval.high16bits << 8;

			uint64_t temp = retval.low64bits;
			temp >>= 56;
			retval.high16bits |= (uint16_t)temp;

			retval.low64bits = retval.low64bits << 8;
		}

		uint8_t remain_shift = val % 8;

		retval.high16bits = retval.high16bits << remain_shift;

		uint64_t temp = retval.low64bits;
		temp >>= (uint8_t)64 - remain_shift;
		retval.high16bits |= (uint16_t)temp;

		retval.low64bits = retval.low64bits << remain_shift;

		return retval;
	}

	mynewdatatype operator>>(uint64_t val) {
		mynewdatatype retval = *this;
		for (uint64_t i = 0; i < val / 8; i++) {
			retval.low64bits = (uint64_t)retval.low64bits >> 8;

			uint64_t temp = retval.high16bits & 0xFF;
			temp <<= 56;
			retval.low64bits |= temp;

			retval.high16bits = (uint16_t)retval.high16bits >> 8;
		}

		uint8_t remain_shift = val % 8;

		retval.low64bits = (uint64_t)retval.low64bits >> remain_shift;

		uint8_t maskValue = -1;
		maskValue >>= (uint8_t)8 - remain_shift;

		uint64_t temp = retval.high16bits & maskValue;
		temp <<= (uint8_t)64 - remain_shift;
		retval.low64bits |= temp;

		retval.high16bits = (uint16_t)retval.high16bits >> remain_shift;

		return retval;
	}

};


std::ostream& operator<<(std::ostream& cout, const mynewdatatype& mytype) {
	std::cout << mytype.high16bits << mytype.low64bits;
	return cout;
}

int main(int argc, char** argv) {

	constexpr size_t arr_size = 500;

	mynewdatatype arr[arr_size];

	for (int i = 0; i < arr_size; i++) {
		arr[i].high16bits = -32768 + rand() % 65536;
		arr[i].low64bits = rand();
	}

	radix_sortSigned(arr, arr_size, 10);

	//check if sorted
	unsigned int i;
	for (i = 1; i < arr_size; i++)
	{
		if (arr[i - 1].high16bits > arr[i].high16bits)
			break;
		else if (arr[i - 1].high16bits == arr[i].high16bits)
			if (arr[i - 1].low64bits > arr[i].low64bits)
				break;
	}
	if (i == arr_size)
		std::cout << "array is sorted\n";
	else
		std::cout << "array is not sorted\n";

	std::cin.get();

	return 0;
}