#pragma once
namespace cef{
	class Bootstrap
	{
	public:
		Bootstrap() : entities(events), systems(entities, events){}

		EventManager events;
		EntityManager entities;
		SystemManager systems;
	};
}

