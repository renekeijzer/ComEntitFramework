#pragma once
#include <cstdint>
#include <bitset>
#include <cassert>
#include "Event.hpp"
#include "Config.h"
#include "BaseView.hpp"
#include <ostream>

namespace cef{
	namespace entity{
		typedef std::bitset<MAX_COMPONENTS> ComponentMask;
		typedef std::uint32_t uint32_t;
		typedef std::uint64_t uint64_t;
		typedef BaseView<false> View;
		typedef BaseView<true> DebugView;
		class EntityManager;


		template <typename C>
		class ComponentHandle;

		class Entity
		{
		public:
			struct Id
			{
			Id(): id_(0){}
			explicit Id(uint64_t id) : id_(id){}
			Id(uint32_t index, uint32_t version) : id_(uint64_t(index) | uint64_t(version) << 32UL) {}

			uint64_t id() const { return id_; }

			bool operator == (const Id &other) const { return id_ == other.id_; }
			bool operator != (const Id &other) const { return id_ != other.id_; }
			bool operator < (const Id &other) const { return id_ < other.id_; }

			uint32_t index() const { return id_ & 0xffffffffUL; }
			uint32_t version() const { return id_ >> 32; }

			private:
				friend class EntityManager;
				uint64_t id_;
			};
			
			static const Id INVALID;
			Entity() {}
			Entity(EntityManager *manager, Entity::Id id) : manager_(manager), id_(id) {}
			Entity(const Entity &other) : manager_(other.manager_), id_(other.id_) {}

			Entity &operator = (const Entity &other) {
				manager_ = other.manager_;
				id_ = other.id_;
				return *this;
			}

			operator bool() const {
				return valid();
			}

			bool operator == (const Entity &other) const {
				return other.manager_ == manager_ && other.id_ == id_;
			}

			bool operator != (const Entity &other) const {
				return !(other == *this);
			}

			bool operator < (const Entity &other) const {
				return other.id_ < id_;
			}
			void invalidate();

			Id id() const { return id_; }

			template <typename C, typename ... Args>
			ComponentHandle<C> assign(Args && ... args);

			template <typename C>
			ComponentHandle<C> assign_from_copy(const C &component);

			template <typename C>
			void remove();

			template <typename C>
			ComponentHandle<C> component();

			template <typename C>
			const ComponentHandle<const C> component() const;

			template <typename ... Components>
			std::tuple<ComponentHandle<Components>...> components();

			template <typename ... Components>
			std::tuple<ComponentHandle<const Components>...> components() const;

			template <typename C>
			bool has_component() const;

			template <typename A, typename ... Args>
			void unpack(ComponentHandle<A> &a, ComponentHandle<Args> & ... args);

			bool valid() const;
			void destroy();

			std::bitset<MAX_COMPONENTS> component_mask() const;

			
		private:
			EntityManager *manager_ = nullptr;
			Entity::Id id_ = INVALID;


		};
	}
	/*initializing Entity events here*/
	namespace event{
		template <typename C>
		struct ComponentAddedEvent : public Event<ComponentAddedEvent<C>> {
			ComponentAddedEvent(Entity entity, ComponentHandle<C> component) :
			entity(entity), component(component) {}

			Entity entity;
			ComponentHandle<C> component;
		};

		template <typename C>
		struct ComponentRemovedEvent : public Event<ComponentRemovedEvent<C>> {
			ComponentRemovedEvent(Entity entity, ComponentHandle<C> component) :
			entity(entity), component(component) {}

			Entity entity;
			ComponentHandle<C> component;
		};

		struct EntityCreatedEvent : public Event<EntityCreatedEvent> {
			explicit EntityCreatedEvent(cef::entity::Entity entity) : entity(entity) {}
			virtual ~EntityCreatedEvent();
		private:
			cef::entity::Entity entity;
		};

		struct EntityDestroyedEvent : public Event<EntityDestroyedEvent> {
			explicit EntityDestroyedEvent(cef::entity::Entity entity) : entity(entity) {}
			virtual ~EntityDestroyedEvent();
		private:
			cef::entity::Entity entity;
		};

	
	}
}
