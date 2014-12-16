#pragma once
#include "NonCopyable.hpp"
#include "Entity.hpp"
#include "EventManager.hpp"
namespace cef{
	namespace entity{
		class EntityManager : cef::helper::NonCopyable
		{
		public:
			explicit EntityManager(cef::event::EventManager & event_manager);
			virtual	~EntityManager();
			size_t capacity() const;
			size_t size() const;
			bool valid(Entity::Id id);
			
			Entity create();
			void destroy(Entity::Id entity);

		private:
			uint32_t index_counter_ = 0;
			std::vector<BasePool *> component_pools_;
			std::vector<uint32_t> entity_version_;
			std::list<uint32_t> free_list_;
			std::vector<ComponentMask> entity_component_mask_;
		};
	}
}

