#pragma once
#include "NonCopyable.hpp"
namespace cef{
	namespace systems{

		class BaseSystem :
			public cef::helper::NonCopyable
		{
		public:
			BaseSystem();
			~BaseSystem();
		};

	}
}