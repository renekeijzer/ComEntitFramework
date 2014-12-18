#pragma once
#include "NonCopyable.hpp"
#include "Entity.hpp"
#include "EventManager.hpp"
#include "BasePool.hpp"
#include "EventManager.hpp"
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

			DebugView entities_for_debugging();

			template<typename A, typename ... Args>
			void unpack(Entity::Id id, ComponentHandle<A> &a, ComponentHandle<Args> & ... args);

			void reset();
		private:
			friend class Enity;

			template<typename C>
			friend class ComponentHandle;

			inline void assert_valid(Entity::Id id) const {
				assert(id.index() < entity_component_mask_.size() && "Entity::Id ID outside entity vector range");
				assert(entity_version_[id.index()] == id.version() && "Attempt to access Entity via a stale Entity::Id");
			}

			template <typename C>
			C *get_component_ptr(Entity::Id id);

			template <typename C>
			const C *get_component_ptr(Entity::Id id) const;

			ComponentMask component_mask(Entity::Id id);

			template <typename C>
			ComponentMask component_mask();

			template <typename C1, typename C2, typename ... Components>
			ComponentMask component_mask();

			template <typename C>
			ComponentMask component_mask(const ComponentHandle<C> &c);

			template <typename C1, typename ... Components>
			ComponentMask component_mask(const ComponentHandle<C1> &c1, const ComponentHandle<Components> &... args);

			void accomodate_entity(uint32_t index);

			template <typename T>
			Pool<T> *accomodate_component();


			cef::event::EventManager &event_manager_;
			uint32_t index_counter_ = 0;
			std::vector<cef::helper::BasePool *> component_pools_;
			std::vector<uint32_t> entity_version_;
			std::list<uint32_t> free_list_;
			std::vector<ComponentMask> entity_component_mask_;
		};
	}
}

