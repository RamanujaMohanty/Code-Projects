// Include Guard
#ifndef OM_VECTOR_H  // If OM_VECTOR_H isn't defined:
#define OM_VECTOR_H  // Defines the macro OM_VECTOR_H.

#include <iostream>
#include <vector>

// Ensures that the public functions belong to "omlib" rather than the global scope.
namespace omlib
{
	template<typename T>   // Ensures that OmVector and its methods work universally.
	class OmVector
	{
		// Private makes sure that declared statements 
		// cannot be accessed outside of OmVector
		private:
			std::vector<T> data_vec;
		public:
			// Forwards to std::vector's internal push_back function.
			// If enough mem: adds value directly. Else: allocates, copies
			// and then adds value.
			void push_back(const T& value)
			{
				data_vec.push_back(value);
			}
			// Prints the contents of data_vec. Adds commas up to n-2, then
			// ends with n-1 and ']'.
			void print() const
			{
				std::cout << "[";
				for (std::size_t ii = 0; ii < data_vec.size() - 1; ++ii)
				{
					std::cout << data_vec[ii] << ", ";
				}
				std::cout << data_vec[data_vec.size() - 1] << "]" << std::endl;
			}
			// Returns "True" if empty and "False" if data_vec 
			// has a non-zero number of entries.
			// const ensures that data_vec remains read-only.
			void empty() const
			{
				if (!(data_vec.empty()))
				{
					std::cout << "False." << std::endl;
				}
				else
				{
					std::cout << "True." << std::endl;
				}
			}
			// Returns size_t containing data_vec's size.
			// size_t chosen because guaranteed to be non-negative.
			// Range of size_t will change with each device.
			std::size_t size() const
			{
				return data_vec.size();
			}
	};      // End of class OmVector.
}

#endif               // Ends conditional started by #ifndef.
