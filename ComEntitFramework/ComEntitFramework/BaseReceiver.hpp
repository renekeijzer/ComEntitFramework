#pragma once
#include "EventManager.hpp"
#include <list>
#include "Event.h"
namespace cef{
	namespace event{
		class BaseReceiver
		{
		public:

			virtual ~BaseReceiver();
			std::size_t connectedSignals() const;
		private:
			friend class EventManager;
			std::list<std::pair< cef::event::EventSignalWeakPtr, std::size_t>> connections_;
		}; 
	}
}
