#include "BasePool.hpp"


namespace cef{
	namespace helper{
		BasePool::BasePool(std::size_t element_size, std::size_t chunk_size = 8192)
			: element_size_(element_size), chunk_size_(chunk_size), capacity_(0) {}

		std::size_t BasePool::size() const{
			return size_;
		}
		std::size_t BasePool::capacity() const{
			return capacity_;
		}
		std::size_t BasePool::chunks() const{
			return blocks_.size();
		}

		void BasePool::reserve(std::size_t n){
			while (capacity_ < n){
				char * chunk = new char[element_size_ * chunk_size_];
				blocks_.push_back(chunk);
				capacity_ += chunk_size_;
			}
		}
		void BasePool::expand(std::size_t n){
			if (n >= size_){
				if (n >= capacity_){ 
					expand(n); 
				}
				size_ = n;
			}
		}
		void * BasePool::get(std::size_t n){
			assert(n < size_);
			return blocks_[n / chunk_size_] + (n % chunk_size_) * element_size_;
		}
		const void * BasePool::get(std::size_t n) const{
			assert(n < size_);
			return blocks_[n / chunk_size_] + (n % chunk_size_) * element_size_;
		}


		BasePool::~BasePool() {
			for (char *ptr : blocks_) {
				delete[] ptr;
			}
		}
	}
}