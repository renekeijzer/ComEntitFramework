#pragma once
#include "NonCopyable.hpp"
#include "EventManager.hpp"
#include "EntityManager.hpp"
#include <utility>
#include <cstdint>
#include <cassert>
#include "Config.h"

namespace cef{
	namespace systems{

		class BaseSystem :
			public helper::NonCopyable
		{
		public:
			typedef size_t Family;
			virtual ~BaseSystem();
			virtual void configure(event::EventManager &events) {}
			virtual void Update(entity::EntityManager &entities, event::EventManager &events, TimeDelta dt) = 0;
			static Family family_counter_;
		};

	}
}