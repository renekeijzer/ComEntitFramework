#pragma once
#include <unordered_map>
#include "NonCopyable.hpp"
#include "EntityManager.hpp"
#include "BaseSystem.hpp"
#include "System.hpp"
#include "EventManager.hpp"
namespace cef{
	namespace systems{
		class BaseSystem;
		class SystemManager :
			public cef::helper::NonCopyable
		{
		public:
			SystemManager(cef::entity::EntityManager &entity_manager,
				cef::event::EventManager &event_manager) :
				entity_manager_(entity_manager),
				event_manager_(event_manager) {}

			template<typename S>
			void add(std::shared_ptr<S> system);

			template<typename S, typename ...Args>
			std::shared_ptr<S> add(Args && ... args);

			template<typename S>
			std::shared_ptr<S> system();

			template<typename S>
			void update(TimeDelta dt);

			void configure();

		private:
			bool initialized_ = false;
			cef::entity::EntityManager entity_manager_;
			cef::event::EventManager event_manager_;
			std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> systems_;
		};
	}
}