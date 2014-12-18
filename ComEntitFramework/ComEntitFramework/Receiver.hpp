#pragma once
#include "BaseReceiver.hpp"
namespace cef{ 
	namespace event{
		template <typename Derived>
		class Receiver : public BaseReceiver
		{
			public:
				virtual ~Receiver();
		};
	}
}
