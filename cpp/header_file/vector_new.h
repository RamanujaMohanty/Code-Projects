#ifndef VECTOR_NEW_H
#define VECTOR_NEW_H

#include <iostream>
#include <cstdlib>

namespace omlib
{
	template<typename T>
	class vector
	{
		private:
			size_t _capacity = 0;
			size_t _size = 0;
			T* _data = nullptr;
			void _alloc()
			{
				if(!_data) {
					_data = (T*) malloc(sizeof(T));
					_capacity = 1;
				}
				else {
					_capacity *= 2;
					new_data = realloc(_data, _capacity * sizeof(T));
					free(_data);
					_data = new_data;
				}
			}
		public:
			void push_back(const T& _val)
			{
				if (_size + 1 < _capacity)
				{

				}
				else
				{
					_alloc;
					_data[_size] = _val;
					++size;
				}
			}
	};
}
#endif
