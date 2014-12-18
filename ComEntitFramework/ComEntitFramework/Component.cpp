#include "Component.hpp"
namespace cef{
	namespace entity{

		template<typedef C>
		BaseComponent::Family Component<C>::family(){
			static Family family = family_counter_++;
			assert(family < entityx::MAX_COMPONENTS);
			return family;
		}
	}
}