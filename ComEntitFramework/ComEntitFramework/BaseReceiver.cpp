#include "BaseReceiver.hpp"



cef::event::BaseReceiver::~BaseReceiver()
{
	for (auto connection : connections_){
		auto &ptr = connection.first;
		if (!ptr.expired()){
			ptr.lock()->disconnect(connection.second);
		}
	}
}

std::size_t cef::event::BaseReceiver::connectedSignals() const{
	std::size_t size = 0;
	for (auto connection : connections_){
		if (!connection.first.expired()){
			size++;
		}
	}
}
