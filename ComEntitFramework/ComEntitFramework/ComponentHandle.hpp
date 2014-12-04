#pragma once
namespace cef{
	namespace entity{
		template<typename C>
		class ComponentHandle
		{
		public:
			typedef C ComponentType;

			ComponentHandle() : manager_(nullptr){}
			bool valid() const;

			C *operator->();
			const C *operator->() const;

			C* get();
			const C* get();
			void remove();

			bool operator ==(const ComponentHandle<C> & other)const{
				return manager_ == other.manager_ && id_ == other.id_;
			}
			bool operator !=(const ComponentHandle<C> & other)const{
				return !(*this == other);
			}

		private:
			friend class EntityManager;
			ComponentHandle(EntityManager *manager, Entity::Id id) : manager_(manager), id_(id){}
			ComponentHandle(const EntityManager * manager, Entity::Id id) : manager_(const_cast<EntityManager*>(manager)), id_(id)){}

			EntityManager * manager_;
			Entity::Id id_;
		};

	}
}