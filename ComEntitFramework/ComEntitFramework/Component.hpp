#pragma once
#include "ComponentHandle.hpp"
#include "BaseComponent.hpp"
namespace cef{
	namespace entity{
		template <typename Derived>
		class Component :
			public BaseComponent
		{
		public:
			typedef ComponentHandle<Derived> Handle;
			static Family family();
		};

	}
}