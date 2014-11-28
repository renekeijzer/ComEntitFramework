#pragma once
#include "NonCopyable.hpp"
#include <memory>
#include <vector>
#include <utility>
#include "simplesignal.h"

namespace cef{
	namespace manager{
		class EventManager :
			public cef::helper::NonCopyable
		{
		public:
			EventManager();
			virtual ~EventManager();

			template<typename e, typename Receiver>
			void subscribe(Receiver & receiver);
			void emit(const BaseEvent & event);

			template<typename e, typename ... Args>
			void emit(Args &&...args);

			std::size_t connectedReceivers() const;
		private:
			typedef Simple::Signal<void(const BaseEvent*)> EventSignal;
			typedef std::shared_ptr<EventSignal> EventSignalPtr;
			typedef std::weak_ptr<EventSignal> EventSignalWeakPtr;


			EventSignalPtr & signalFor(std::size_t id);
			std::vector<EventSignalPtr> handlers_;
			
			template<typename E>
			struct EventCallbackWrapper{
				EventCallbackWrapper(std::function<void(const E&)>) : callback(callback){}
				void operator()(const BaseEvent* event) { callback(*(static_cast<const E*>(event))); }
				std::function<void(const E &)> callback;
			};

		};
	}
}

