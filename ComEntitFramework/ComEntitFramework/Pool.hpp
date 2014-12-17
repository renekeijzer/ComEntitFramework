#pragma once
#include "BasePool.hpp"
namespace cef{
	namespace helper{
		template<typename T, std::size_t ChunkSize = 8192> 
		class Pool :
			public BasePool
		{
		public:
			Pool();
			virtual ~Pool();
			virtual void destroy(std::size_t n)override;
		};

	}
}