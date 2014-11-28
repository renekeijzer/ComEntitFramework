#include "EventManager.hpp"
typedef Simple::Signal<void(const BaseEvent*)> EventSignal;
typedef std::shared_ptr<EventSignal> EventSignalPtr;
typedef std::weak_ptr<EventSignal> EventSignalWeakPtr;

cef::manager::EventManager::EventManager()
{
}


cef::manager::EventManager::~EventManager()
{
}

template<typename e, typename Receiver>
void cef::manager::EventManager::subscribe(Receiver & receiver){
	void(Receiver::*receive)(const e &) = &Receiver::receive;
	auto signal = signalFor(e::family());
	auto wrapper = EventCallbackWrapper<E>(std::bind(receive, &receiver, std::placeholders::_1));
	auto connection = signal->connect(wrapper);
	
}


template<typename e, typename ... Args>
void cef::manager::EventManager::emit(Args &&...args){
	e event = e(std::forward<Args>(args)...);
	auto signal = signalFor(std::size_t(e::family()));
	BaseEvent * base = &event;
	signal->emit(base);
}


std::size_t cef::manager::EventManager::connectedReceivers() const{
	std::size_t size = 0;
	for (EventSignalPtr handler : handlers_){
		if (handler){
			size += handler->size();
		}
	}
	return size;
}

EventSignalPtr & cef::manager::EventManager::signalFor(std::size_t id){
	if (id >= handlers_.size()){
		handlers_.resize(handlers_.size() + 1);
	}
	if (!handlers_[id]){
		handlers_[id] = std::make_shared<EventSignal>();
	}
	return handlers_[id];

}

