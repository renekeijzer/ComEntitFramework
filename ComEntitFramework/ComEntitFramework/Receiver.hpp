#pragma once
#include "BaseReceiver.hpp"
namespace cef{ namespace event{
class Receiver :
	public BaseReceiver
{
public:
	virtual ~Receiver();
};
}
}
