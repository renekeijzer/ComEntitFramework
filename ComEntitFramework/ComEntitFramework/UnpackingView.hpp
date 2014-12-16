#pragma once
#include "ComponentHandle.hpp"
#include <utility>
#include "Entity.hpp"
namespace cef{
	namespace entity{
		template<typename ... Components>
		class UnpackingView
		{
		public:
			struct Unpacker{
				Unpacker(ComponentHandle<Components> & ...handles) : handles(std::tuple<ComponentHandle<Components> & ...>(handles));
				void unpack(Entity &ent)const {
					unpack_<0, Components...>(ent);
				}
			private:
				template<int N, typename C>
				void unpack_(Entity & ent)
				{
					std::get<N>(handles) = ent.component<C0>();
				}

				template<int N, int typename C0, typename C1, typename ... Cn>
				void unpack_(Entity & ent){
					std::get<N>(handles) = ent.components<C0>();
					unpack_<N + 1, C1, Cn...>(ent);
				}
				
				std::tuple<ComponentHandle<Components>&...>handles;


			};

			class Iterator : public ViewIterator<Iterator> {
			public:
				Iterator(EntityManager *manager, const ComponentMask mask, uint32_t index, const Unpacker &unpacker)
					: ViewIterator<Iterator>(manager, mask, index), unpacker_(unpacker) {
						ViewIterator<Iterator>::next();
					}

				void next_entity(Entity &entity) {
					unpacker_.unpack(entity);
				}

			private:
				const Unpacker &unpacker_;
			};


			Iterator begin() { return Iterator(manager_, mask_, 0, unpacker_); }
			Iterator end() { return Iterator(manager_, mask_, manager_->capacity(), unpacker_); }
			const Iterator begin() const { return Iterator(manager_, mask_, 0, unpacker_); }
			const Iterator end() const { return Iterator(manager_, mask_, manager_->capacity(), unpacker_); }


		private:
			friend class EntityManager;
			UnpackingView(EntityManager *manager, ComponentMask mask, ComponentHandle<Components> & ... handles) :
				manager_(manager), mask_(mask), unpacker_(handles...) {}

			EntityManager *manager_;
			ComponentMask mask_;
			Unpacker unpacker_;
		};

	}
}