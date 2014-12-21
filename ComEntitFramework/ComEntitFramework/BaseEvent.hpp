#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "simplesignal.h"
#include "BaseEvent.hpp"
#include "Receiver.hpp"
namespace cef{
	namespace event{
		class BaseEvent
		{
		public:
			typedef std::size_t Family;
			BaseEvent();
			virtual ~BaseEvent();
			virtual Family myFamily() const = 0;
		protected:
			static Family family_counter_;
		}; 
	}
}

