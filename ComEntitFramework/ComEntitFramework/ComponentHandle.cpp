#include "ComponentHandle.hpp"
namespace cef{
	namespace entity{
		template<typedef C>
		inline ComponentHandle<C>::operator bool() const {
			return valid();
		}

		template <typename C>
		inline bool ComponentHandle<C>::valid() const {
			return manager_ && manager_->valid(id_) && manager_->has_component<C>(id_);
		}

		template <typename C>
		inline C *ComponentHandle<C>::operator -> () {
			assert(valid());
			return manager_->get_component_ptr<C>(id_);
		}

		template <typename C>
		inline const C *ComponentHandle<C>::operator -> () const {
			assert(valid());
			return manager_->get_component_ptr<C>(id_);
		}

		template <typename C>
		inline C *ComponentHandle<C>::get() {
			assert(valid());
			return manager_->get_component_ptr<C>(id_);
		}

		template <typename C>
		inline const C *ComponentHandle<C>::get() const {
			assert(valid());
			return manager_->get_component_ptr<C>(id_);
		}

		template <typename C>
		inline void ComponentHandle<C>::remove() {
			assert(valid());
			manager_->remove<C>(id_);
		}

	
	
	}



}