#pragma once
#include "NonCopyable.hpp"
#include "EventManager.hpp"
class EntityManager : cef::helper::NonCopyable
{
public:
	explicit EntityManager(cef::event::EventManager & event_manager);
	virtual	~EntityManager();
};

