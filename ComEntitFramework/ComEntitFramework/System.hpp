#pragma once
#include "BaseSystem.hpp"
namespace cef{
	namespace systems{

		template <typename Derived>
		class System : public BaseSystem {
		public:
			virtual ~System() {}

		private:
			friend class SystemManager;

			static Family family() {
				static Family family = family_counter_++;
				return family;
			}
		};


	}
}