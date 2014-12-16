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
			uint32_t = entity.index();

		
		}




	}
}