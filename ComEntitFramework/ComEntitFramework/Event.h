#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "simplesignal.h"
#include "BaseEvent.hpp"
namespace cef{
	namespace event{
		typedef Simple::Signal<void(const BaseEvent*)> EventSignal;
		typedef std::shared_ptr<EventSignal> EventSignalPtr;
		typedef std::weak_ptr<EventSignal> EventSignalWeakPtr;

		template <typename Derived>
		class Event : public BaseEvent
		{
		public:
			static Family family = family_counter_++;
			virtual Family myFamily() const override { return Derived::family(); }
			 
		};
	}
}