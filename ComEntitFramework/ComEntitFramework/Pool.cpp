#include "Pool.hpp"
namespace cef{
	namespace helper{

		template<typename T, std::size_t ChunkSize = 8192>
		Pool::Pool() : BasePool(sizeof(T), ChunkSize)
		{
		}

		template<typename T, std::size_t ChunkSize = 8192>
		void Pool::destroy(std::size_t n){
			assert(n < size_);
			T* ptr = static_cast<T*>(get(n));
			ptr->~T();
		}
			
	
	}
}