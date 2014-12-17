#pragma once
#include "NonCopyable.hpp"
#include "Entity.hpp"
#include "EventManager.hpp"
#include "BasePool.hpp"
#include "Pool.hpp"
#include <new>
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

			Entity get(Entity::Id id);
			Entity::Id create_id(uint32_t index)const;
			
			template<typename C, typename ...Args>
			ComponentHandle<C> assign(Entity::Id id, Args && ... args);

			template<typename C>
			void remove(Entity::Id id);
			
			template<typename C>
			void has_component(Entity::Id id);

			template<typename C>
			ComponentHandle<C> component(Entity::Id id);

			template<typename C>
			const ComponentHandle<C> component(Entity::Id id) const;

			template<typename ... Components>
			std::tuple<ComponentHandle<Components> ...> components(Entity::Id id);

			template<typename ... Components>
			std::tuple<ComponentHandle<const Components> ...> components(Entity::Id id)const;

			template<typename ... Components>
			View entities_with_components();

			template<typename ... Components>
			UnpackingView<Components...> entities_with_components(ComponentHandle<Components> & ... components);



		private:
			uint32_t index_counter_ = 0;
			std::vector<cef::helper::BasePool *> component_pools_;
			std::vector<uint32_t> entity_version_;
			std::list<uint32_t> free_list_;
			std::vector<ComponentMask> entity_component_mask_;
		};
	}
}

