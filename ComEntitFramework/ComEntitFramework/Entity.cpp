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

		std::bitset<MAX_COMPONENTS> Entity::component_mask() const {
			return manager_->component_mask(id_);
		}

		template <typename C, typename ... Args>
		ComponentHandle<C> Entity::assign(Args && ... args) {
			assert(valid());
			return manager_->assign<C>(id_, std::forward<Args>(args) ...);
		}

		template <typename C>
		ComponentHandle<C> Entity::assign_from_copy(const C &component) {
			assert(valid());
			return manager_->assign<C>(id_, std::forward<const C &>(component));
		}

		template <typename C>
		void Entity::remove() {
			assert(valid() && has_component<C>());
			manager_->remove<C>(id_);
		}

		template <typename C>
		ComponentHandle<C> Entity::component() {
			assert(valid());
			return manager_->component<C>(id_);
		}

		template <typename C>
		const ComponentHandle<const C> Entity::component() const {
			assert(valid());
			return manager_->component<const C>(id_);
		}

		template <typename ... Components>
		std::tuple<ComponentHandle<Components>...> Entity::components() {
			assert(valid());
			return manager_->components<Components...>(id_);
		}

		template <typename ... Components>
		std::tuple<ComponentHandle<const Components>...> Entity::components() const {
			assert(valid());
			return manager_->components<const Components...>(id_);
		}


		template <typename C>
		bool Entity::has_component() const {
			assert(valid());
			return manager_->has_component<C>(id_);
		}

		template <typename A, typename ... Args>
		void Entity::unpack(ComponentHandle<A> &a, ComponentHandle<Args> & ... args) {
			assert(valid());
			manager_->unpack(id_, a, args ...);
		}

		bool Entity::valid() const {
			return manager_ && manager_->valid(id_);
		}

	}
}