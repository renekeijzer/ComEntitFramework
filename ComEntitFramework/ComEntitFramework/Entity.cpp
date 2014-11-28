#include "Entity.hpp"

void cef::Entity::Entity::invalidate() {
	id_ = INVALID;
	manager_ = nullptr;
}

void cef::Entity::Entity::destroy() {
	assert(valid());
	manager_->destroy(id_);
	invalidate();
}

std::bitset<64> cef::Entity::Entity::component_mask() const {
	return manager_->component_mask(id_);
}
