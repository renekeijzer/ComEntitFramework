#pragma once
#include "EventManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
namespace cef{
	class Bootstrap
	{
	public:
		Bootstrap() : entities(events), systems(entities, events){}

		event::EventManager events;
		entity::EntityManager entities;
		systems::SystemManager systems;
	};
}

