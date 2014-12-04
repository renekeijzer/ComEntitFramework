#pragma once
#include "EventManager.hpp"
namespace cef{
	class Bootstrap
	{
	public:
		Bootstrap() : entities(events), systems(entities, events){}

		cef::event::EventManager events;
		cef::entity::EntityManager entities;
		SystemManager systems;
	};
}

