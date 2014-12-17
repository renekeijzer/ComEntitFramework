#pragma once
#include <cstddef>
#include <cassert>
#include <vector>
namespace cef{
	namespace helper{
		class BasePool
		{
		public:
			explicit BasePool(std::size_t element_size, std::size_t chunk_size = 8192 );
			std::size_t size() const;
			std::size_t capacity() const;
			std::size_t chunks() const;

			void reserve(std::size_t n);
			void expand(std::size_t n);
			void * get(std::size_t n);
			const void * get(std::size_t n) const;
			virtual void destroy(std::size_t n) = 0;
			
			
			virtual ~BasePool();
		protected:
			std::vector<char *> blocks_;
			std::size_t element_size_;
			std::size_t chunk_size_;
			std::size_t size_ = 0;
			std::size_t capacity_;
		};
	}
}