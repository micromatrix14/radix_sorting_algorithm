////////////////////////////////////////////////////////////////////////////////////////////
/*                             Radix Sorting Algorithm                                    */
/*                           Developed By Ahmed Elbadawy                                  */
/*         it supports sorting any size of data, including negative numbers               */
/*       for very well explained details about how this algorithm does work watch         */
/*                           WhatsaCreel video about it                                   */
/*                          https://youtu.be/_KhZ7F-jOlI                                  */
////////////////////////////////////////////////////////////////////////////////////////////


#ifndef RadixSorterH
#define RadixSorterH
#include <iostream>


/*to use this function with any data types like a structure with size of 448 bits for example, you need to overload the following
_Type operator >>(uint64_t val)	//bitwise right shift operation!
_Type operator &(uint8_t val)	//bitwise and logic operation!
operator size_t()	//conversion function at least to return the lowest 8 bits which will be used
as an index to the prefix sum array in this code!!
*/
template <typename unsorted_t>
void radix_sortUnsigned(unsorted_t* unsigned_arr, uint64_t NumberOfElements, uint64_t ElementSizeInBytes = sizeof(unsorted_t)) {

	//getting number of iterations = ElementSizeInBytes/sizeof(int8_t) which is /1
	uint64_t number_of_iterations = ElementSizeInBytes;

	//allocating array to store each new iteration
	unsorted_t* temp_array = new unsorted_t[NumberOfElements];

	//iterate every 8 bits
	for (uint64_t iteration_num = 0; iteration_num < number_of_iterations; ++iteration_num) {

		//creating prefix sum array of 8 bits = 256 number
		uint64_t prefix_summ_arr[256] = {};

		//creating our counting array
		uint64_t shifting_num = iteration_num * 8;

		for (uint64_t i = 0; i < NumberOfElements; ++i)
			prefix_summ_arr[unsigned_arr[i] >> shifting_num & (uint8_t)0xFF]++;

		//creating our prefix sum array
		for (size_t i = 1; i < 256; i++) {
			prefix_summ_arr[i] += prefix_summ_arr[i - 1];
		}

		//filling temp_array
		for (int64_t i = NumberOfElements - 1; i >= 0; --i)
			temp_array[--prefix_summ_arr[unsigned_arr[i] >> shifting_num & (uint8_t)0xFF]] = unsigned_arr[i];

		//swapping pointers
		unsorted_t* temp = unsigned_arr;
		unsigned_arr = temp_array;
		temp_array = temp;
	}

	if (number_of_iterations & 1)
	{
		unsorted_t* temp = unsigned_arr;
		unsigned_arr = temp_array;
		temp_array = temp;

		//here we move the sorted array to the main one 
		for (uint64_t i = 0; i < NumberOfElements; ++i)
			unsigned_arr[i] = temp_array[i];

		//or
		//memcpy_s(unsorted_arr, unsorted_arr_size * sizeof(unsorted_t), temp_array, unsorted_arr_size * sizeof(unsorted_t));
		//but this way isn't efficient as on specs with rsize_t less than the actual array size
		//elements larger than the rsize_t and less than uint64_t will be cut

	}

	delete[] temp_array;
}


/*to use this function with any data types like a structure with size of 448 bits for example, you need to overload the following
_Type operator +(_Type& other)
_Type operator -(_Type& other)
_Type operator =(int val)	//make sure to do it correctly, by putting all zeros and "at least" to put 1 in the lowest bit!
_Type operator <<(uint64_t val)	//bitwise left shift operation!
_Type operator >>(uint64_t val)	//bitwise right shift operation!
_Type operator &(uint8_t val)	//bitwise and logic operation!
operator size_t()	//conversion function at least to return the lowest 8 bits which will be used
as an index to the prefix sum array in this code!!
*/
template <typename unsorted_s_t>
void radix_sortSigned(unsorted_s_t* signed_arr, uint64_t NumberOfElements, uint64_t ElementSizeInBytes = sizeof(unsorted_s_t)) {

	//let's say we have 8 bits signed number of type char, it is known that the value is from
	//-128 to 127! so all we do is that we are going to treat all these numbers as unsigned
	//by adding 128 to shift them, so the range will become from 0 to 255 then after applying the sorting
	//algorithm we subtract 128 back again!!
	//to keep on our generic form of the function we can do the following
	/*
	unsorted_s_t AdditiveVal = 1;
	AdditiveVal = AdditiveVal << sizeof(unsorted_s_t) - 1;
	so in our last example we can get 128 unsigned in case of unsorted_s_t as char
	the problem is if the unsorted_s_t is of type struct, because of "structure padding"
	we can't say if this is the actual number of bytes our struct can hold using sizeof()!!
	so we need to receive the actual number of bytes of the struct from the library user!
	*/

	unsorted_s_t AdditiveVal;
	AdditiveVal = 1;
	AdditiveVal = AdditiveVal << (uint64_t)(ElementSizeInBytes * 8 - 1);

	for (uint64_t i = 0; i < NumberOfElements; ++i)
		signed_arr[i] = signed_arr[i] + AdditiveVal;

	radix_sortUnsigned(signed_arr, NumberOfElements, ElementSizeInBytes);

	for (uint64_t i = 0; i < NumberOfElements; ++i)
		signed_arr[i] = signed_arr[i] - AdditiveVal;

}

#endif