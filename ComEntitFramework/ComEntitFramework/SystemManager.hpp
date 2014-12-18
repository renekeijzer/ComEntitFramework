#pragma once
#include "NonCopyable.hpp"
namespace cef{
	namespace systems{
		class SystemManager :
			public cef::helper::NonCopyable
		{
		public:
			SystemManager();
			~SystemManager();
		};

	}
}