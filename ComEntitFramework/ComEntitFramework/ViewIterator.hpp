#pragma once
#include "Entity.hpp"
#include <iterator>
namespace cef{
	namespace entity{
		template<class Delegate, bool all = false>
		class ViewIterator :
			public std::iterator<std::input_iterator_tag, Entity::Id>
		{
		public:
			Delegate &operator++(){
				++i_;
				next();
				return *static_cast<Delegate*>(this);
			}


			bool operator == (const Delegate& rhs) const { return i_ == rhs.i_; }
			bool operator != (const Delegate& rhs) const { return i_ != rhs.i_; }
			Entity operator * () { return Entity(manager_, manager_->create_id(i_)); }
			const Entity operator * () const { return Entity(manager_, manager_->create_id(i_)); }
		protected:
			ViewIterator(EntityManager *manager, uint32_t index);
			ViewIterator(EntityManager *manager, const ComponentMask mask, uint32_t index);
			void next();

			inline bool valid_entity();
			inline bool predicate();

			EntityManager *manager_;
			ComponentMask mask_;
			uint32_t i_;
			size_t capacity_;
			std::list<uint32_t>::iterator free_cursor_;

		};
	}
}

