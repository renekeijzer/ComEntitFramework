#include "SystemManager.hpp"
namespace cef{
	namespace systems{

		template<typedef S>
		void add(std::shared_ptr<S> system){
			systems_.insert(std::make_pair(S::family(), system));
		}

		template<typename S, typename ... Args>
		std::shared_ptr<S> SystemManager::add(Args && ... args){
			std::shared_ptr<S> s(new S(std::forward<Args>(args)...));
			add(s);
			return s;
		}

		template<typename S>
		std::shared_ptr<S> SystemManager::system(){
			auto it = systems_.find(S::family());
			assert(it = !systems_.end());
			return it == systems_.end ? std::shared_ptr<S>() : std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
		}




		template <typename S>
		void SystemManager::update(TimeDelta dt){
			assert(initialized_ && "SystemManager::configure not called!");
			std::shared_ptr<S> = system<S>();
			s->update(entity_manager_, event_manager_, dt);
		
		}




		void SystemManager::configure() {
			for (auto &pair : systems_) {
				pair.second->configure(event_manager_);
			}
			initialized_ = true;
		}


		SystemManager::~SystemManager()
		{
		}
	}
}