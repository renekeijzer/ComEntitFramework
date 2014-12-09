#include "ViewIterator.hpp"

namespace cef{
	namespace entity{

		template<class Delegate, bool all = false>
		ViewIterator::ViewIterator(EntityManager *manager, uint32_t index)
			: manager_(manager), i_(index), capacity_(manager_->capacity()) {
			if (All) {
				manager_->free_list_.sort();
				free_cursor_ = manager_->free_list_.begin();
			}
		}

		template<class Delegate, bool all = false>
		ViewIterator::ViewIterator(EntityManager *manager, const ComponentMask mask, uint32_t index)
			: manager_(manager), mask_(mask), i_(index), capacity_(manager_->capacity()) {
			if (All) {
				manager_->free_list_.sort();
				free_cursor_ = manager_->free_list_.begin();
			}
		}

		template<class Delegate, bool all = false>
		void ViewIterator::next() {
			while (i_ < capacity_ && !predicate()) {
				++i_;
			}

			if (i_ < capacity_) {
				Entity entity = manager_->get(manager_->create_id(i_));
				static_cast<Delegate*>(this)->next_entity(entity);
			}
		}
	}
}