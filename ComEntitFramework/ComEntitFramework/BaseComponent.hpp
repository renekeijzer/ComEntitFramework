#pragma once
#include <memory>

namespace cef{
	namespace entity{
		class BaseComponent
		{
		public:
			typedef size_t Family;

			void operator delete(void *p){ fail(); }
			void operator delete[](void * p){fail(); }

		protected:
			static void fail(){
#if defined(_HAS_EXCEPTIONS)|| defined(__EXCEPTIONS)
				throw std::bad_alloc();
#else
				std::abort();
#endif
			}
			static Family family_counter_;
		};
	}
}