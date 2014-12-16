#pragma once
#include "ViewIterator.hpp"
namespace cef{
	namespace entity{
		class Iterator : public ViewIterator<Iterator, all>
		{
		public:
			Iterator(EntityManager *manager, const ComponentMask mask, uint32_t index) : ViewIterator<Iterator, all>(manager, mask, index) {
				ViewIterator<Iterator, all>::next();
			}

			void next_entity(Entity &entity) {}
		};
	}
}