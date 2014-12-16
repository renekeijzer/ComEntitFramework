#include "BaseView.hpp"
namespace cef{
	namespace entity{

		template<bool all>
		BaseView::BaseView(EntityManager *manager) : manager_(manager)
		{
			mask_.set();
		}


		template<bool all>
		Iterator BaseView::begin()
		{ 
			return Iterator(manager_, mask_, 0); 
		}
		

		template<bool all>
		Iterator BaseView::end() { 
			return Iterator(manager_, mask_, uint32_t(manager_->capacity())); 
		}


		template<bool all>
		const Iterator BaseView::begin() const { 
			return Iterator(manager_, mask_, 0); 
		}


		template<bool all>
		const Iterator BaseView::end() const {
			return Iterator(manager_, mask_, manager_->capacity()); 
		}
	}
}