#include "EntityManager.hpp"

namespace cef{
	namespace entity{
		EntityManager::EntityManager()
		{
		}


		EntityManager::~EntityManager()
		{
		}

		bool EntityManager::valid(Entity::Id id){
			return id.index() < entity_version_.size() && entity_version_[id.index] == id.version();
		}

		size_t EntityManager::size() const{
			return entity_component_mask_.size() - free_list_.size();
		}

		size_t EntityManager::capacity() const{
			return entity_component_mask_.size();
		}

		Entity EntityManager::create(){
			uint32_t index, version;
			if (free_list_.empty()){
				index = index_counter_++;
				accomodate_entity(index);
				version = entity_version_[index] = 1;
			}
			else
			{
				index = free_list_.front();
				free_list_.pop_front();
				version = entity_version_[index];
			}

			Entity entity(this, Entity::Id(index, version));
			event_manager_.emit<EntityCreatedEvent>(entity);
			return entity;
		}


		void EntityManager::destroy(Entity::Id entity){
			assert_valid(entity);
			uint32_t index = entity.index();
			auto mask = entity_component_mask_[entity.index()];

			event_manager_.emit<EntityDestroyedEvent>(Entity(this, entity));
			for (size_t i = 0; i < component_pools_.size(); i++){
				cef::helper::BasePool * pool = component_pools_[i];
				if (pool && mask.test(i)){
					pool->destroy(index);
				}
			}
			entity_component_mask_[index].reset();
			entity_version_[index]++;
			free_list_.push_back(index);
		}


		Entity EntityManager::get(Entity::Id id){
			assert_valid(id);
			return Entity(this, id);
		}

		Entity::Id EntityManager::create_id(size_t index) const{
			return Entity::Id(index, entity_version_[index]);
		}


		template<typename C, typename ...Args>
		ComponentHandle<C> EntityManager::assign(Entity::Id id, Args && ... args){
			assert_valid(id);
			const BaseComponent::Family family = C::family();
			assert(!entity_component_mask_[id.index()].test(family));

			Pool<C> * pool = accomodate_component<C>();
			new(pool->get(id.index())) C(std::forward<Args>(args) ...);
			entity_component_mask_[id.index()].set(family);

			ComponentHandle<C> component(this, id);
			event_manager_.emit<ComponentAddedEvent<C>>(Entity(this, id), component);
			return component;
		}

		template<typename C>
		void EntityManager::remove(Entity::Id id){
			assert_valid(id);
			const BaseComponent::Family family = C::family();
			BasePool * pool = component_pools_[id.index()].reset(family);
			entity_component_mask_[id.index()].reset(family);
			pool->destroy(id.index());
		}

		template<typename C>
		void EntityManager::has_component(Entity::Id id){
			assert_valid(id);
			size_t family = C::family();
			if (family >= component_pools_.size()){
				return false;
			}
			BasePool * pool = component_pools_[family];
			if (!pool || !entity_component_mask_[id.index()][family]){
				return false;
			}
			return true;
		}


		template<typename C>
		ComponentHandle<C> EntityManager::component(Entity::Id id){
			assert_valid(id);
			size_t family = C::family();
			if (family >= component_pools_.size())
			{
				return ComponentHandle<C>();
			}

			BasePool* pool = component_pools_[family];
			if (!pool || !entity_component_mask_[id.index][family]){
				return ComponentHandle<C>();
			}
			return ComponentHandle<C>(this, id);
		}

		template<typename C>
		const ComponentHandle<C> EntityManager::component(Entity::Id id) const {
			assert_valid(id);
			size_t family = C::family();
			if (family >= component_pools_.size())
			{
				return ComponentHandle<C>();
			}

			BasePool* pool = component_pools_[family];
			if (!pool || !entity_component_mask_[id.index][family]){
				return ComponentHandle<C>();
			}
			return ComponentHandle<C>(this, id);
		}



		template<typename ... Components>
		std::tuple<ComponentHandle<Components> ...> EntityManager::components(Entity::Id id){
			return std::make_tuple(component<Components>(id)...);
		}

		template<typename ... Components>
		std::tuple<ComponentHandle<const Components> ...> EntityManager::components(Entity::Id id)const {
			return std::make_tuple(component<const Components>(id)...);
		}

		template<typename ... Components>
		View EntityManager::entities_with_components(){
			auto mask = ComponentMask<Components ...>();
			return View(this, mask);
		}

		template<typename ... Components>
		UnpackingView<Components...> EntityManager::entities_with_components(ComponentHandle<Components> & ... components){
			auto mask = component_mask<Components...>();
			return UnpackingView<Components...>(this, mask, components...);
		}


	}
}