#pragma once
#include "BaseComponent.hpp"
namespace cef{
	namespace entity{


		template<typename C>
		class ComponentHandle;


		template <typename Derived>
		class Component :
			public BaseComponent
		{
		public:
			typedef ComponentHandle<Derived> Handle;
			static Family family();		
			BaseComponent::Family family();
		};

	}
}