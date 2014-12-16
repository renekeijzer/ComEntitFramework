#include "Entity.hpp"
namespace cef{
	namespace entity{
		void Entity::invalidate() {
			id_ = INVALID;
			manager_ = nullptr;
		}

		void Entity::destroy() {
			assert(valid());
			manager_->destroy(id_);
			invalidate();
		}

		std::bitset<64> Entity::component_mask() const {
			return manager_->component_mask(id_);
		}
	}
}