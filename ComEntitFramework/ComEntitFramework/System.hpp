#pragma once
#include "BaseSystem.hpp"
namespace cef{
	namespace systems{

		template <typename Derived>
		class System : public BaseSystem {
		public:
			virtual ~System() {}
			virtual void update(entity::EntityManager &entities, event::EventManager &events, TimeDelta dt) = 0 override;
		private:
			friend class SystemManager;

			static Family family() {
				static Family family = family_counter_++;
				return family;
			}
		};


	}
}