#include "Iterator.hpp"

namespace cef{
	namespace entity{
		Iterator::Iterator(EntityManager *manager, const ComponentMask mask, uint32_t index) : ViewIterator<Iterator, all>(manager, mask, index)
		{
			ViewIterator<Iterator, all>::next();
		}
	}
}