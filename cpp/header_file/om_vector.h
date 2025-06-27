#ifndef OM_VECTOR_H
#define OM_VECTOR_H

#include <iostream>
#include <vector>

namespace omlib
{
	template<typename T>
	class OmVector
	{
		private:
			std::vector<T> data_vec;
		public:
			void push_back(const T& value)
			{
				data_vec.push_back(value);
			}

			void print() const
			{
				std::cout << "[";
				for (std::size_t ii = 0; ii < data_vec.size() - 1; ++ii)
				{
					std::cout << data_vec[ii] << ", ";
				}
				std::cout << data_vec[data_vec.size() - 1] << "]" << std::endl;
			}

			bool empty() const
			{
				return data_vec.empty();
			}

			std::size_t size() const
			{
				return data_vec.size();
			}
	};
}

#endif
