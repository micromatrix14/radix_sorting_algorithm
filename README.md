# Radix Sorting Algorithm
Simple Radix Sorting algorithm library written in C++, coming with two generic functions

the first one for sorting unsigned numbers

`radix_sortUnsigned`

 and the second for sorting signed numbers
 
 `radix_sortSigned`

## How to use the library?
Add the header file RadixSorter.h to your project

## Some examples of using the library

### 1- to sort primitive unsigned integer values
```
#include <iostream>
#include "RadixSorter.h"

int main(int argc, char** argv) {

	constexpr size_t arr_size = 137533455;
	unsigned int* arr = new unsigned int[arr_size];
	
	for (unsigned int i = 0; i < arr_size; i++)
		arr[i] = rand();
	
	radix_sortUnsigned(arr, arr_size);

	delete[] arr;

	return 0;
}
```
And on one of machines this is the result of sorting between std::sort in C++ and this Radix sorting algorithm
![1](https://user-images.githubusercontent.com/22969054/182248248-2abebccf-63ed-4f55-8db5-c6f5f5d4db32.png)

### 2- to sort primitive signed integer values
```
#include <iostream>
#include "RadixSorter.h"

int main(int argc, char** argv) {

	constexpr size_t arr_size = 7653487;
	int* arr = new int[arr_size];

	for (unsigned int i = 0; i < arr_size; i++)
		arr[i] = -2147483648 + rand() % 429496729;

	radix_sortSigned(arr, arr_size);

	delete[] arr;

	return 0;
}
```
And on one of machines this is the result of sorting between std::sort in C++ and this Radix sorting algorithm
![2](https://user-images.githubusercontent.com/22969054/182248386-d9ade1dd-0600-4eca-bc1d-76da4aba9836.png)

### 3- to sort custom unsigned integer values of 10 bytes size
```
#include <iostream>
#include "RadixSorter.h"

//my data type of 80 bits!!
struct mynewdatatype {
	uint64_t low64bits;
	uint16_t high16bits;

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

	constexpr size_t arr_size = 1000;

	mynewdatatype arr[arr_size];

	for (int i = 0; i < arr_size; i++) {
		arr[i].high16bits = rand();
		arr[i].low64bits = rand();
	}

	radix_sortUnsigned(arr, arr_size, 10);

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
```
And on one of machines this is the result of sorting between std::sort in C++ and this Radix sorting algorithm
![3](https://user-images.githubusercontent.com/22969054/182248436-8c3f13fd-01f8-454e-a322-c5f9b3794c7c.png)

### 4- to sort custom signed integer values of 10 bytes size

```
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
```
And on one of machines this is the result of sorting between std::sort in C++ and this Radix sorting algorithm
![4](https://user-images.githubusercontent.com/22969054/182248464-d50b4a48-9e39-4bc5-9ccb-e7ee3fc471bd.png)
