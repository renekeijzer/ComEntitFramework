#pragma once
#include "Iterator.hpp"
namespace cef{
	namespace entity{
		template<bool all>
		class BaseView
		{
		public:
			Iterator begin();
			Iterator end();
			const Iterator begin() const;
			const Iterator end() const;
		private:
			friend class EntityManager;
			BaseView(EntityManager *manager) : manager_(manager);
			BaseView(EntityManager *manager, ComponentMask mask) :
				manager_(manager), mask_(mask) {}



			EntityManager * manager_;
			ComponentMask mask_;
		};

	}
}