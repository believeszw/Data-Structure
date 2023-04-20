//
// Created by believe on 2023/4/20.
//

#ifndef DATA_STRUCTURE_SHARED_PTR_SRC_LOCK_FREE_PTR_HPP_
#define DATA_STRUCTURE_SHARED_PTR_SRC_LOCK_FREE_PTR_HPP_

#include <atomic>
#include <memory>

template<typename T>
class lf_atomic_shared_ptr {
public:
    lf_atomic_shared_ptr() = default;

    lf_atomic_shared_ptr(T* ptr) : ptr_(ptr) {
        if (ptr) {
            ref_count_ = new std::atomic_uint(1);
        }
    }

    lf_atomic_shared_ptr(const lf_atomic_shared_ptr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ptr_) {
            ref_count_->fetch_add(1, std::memory_order_acquire);
        }
    }

    lf_atomic_shared_ptr(lf_atomic_shared_ptr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)), ref_count_(std::exchange(other.ref_count_, nullptr)) {}

    ~lf_atomic_shared_ptr() {
        if (ptr_ && ref_count_->fetch_sub(1, std::memory_order_release) == 1) {
            std::atomic_thread_fence(std::memory_order_acquire);
            delete ptr_;
            delete ref_count_;
            ptr_ = nullptr;
            ref_count_ = nullptr;
        }
    }

    lf_atomic_shared_ptr& operator=(lf_atomic_shared_ptr other) noexcept {
        swap(other);
        return *this;
    }

    void swap(lf_atomic_shared_ptr& other) noexcept {
        std::swap(ptr_, other.ptr_);
        std::swap(ref_count_, other.ref_count_);
    }

    T* get() const {
        return ptr_;
    }

    std::shared_ptr<T> lock() const {
        std::atomic_uint* ref_count = ref_count_;
        T* ptr = ptr_;
        while (ptr && ref_count->load(std::memory_order_acquire)) {
            auto old_count = ref_count->load(std::memory_order_relaxed) + 1;
            if (ref_count->compare_exchange_weak(
                    old_count,
                    old_count + 1,
                    std::memory_order_release,
                    std::memory_order_acquire)) {
                return std::shared_ptr<T>(ptr, [ref_count](T* p) {
                    if (ref_count->fetch_sub(1, std::memory_order_release) == 1) {
                        std::atomic_thread_fence(std::memory_order_acquire);
                        delete[] p;
                        delete ref_count;
                    }
                });
            }
        }
        return std::shared_ptr<T>();
    }

private:
    T* ptr_ = nullptr;
    std::atomic_uint* ref_count_ = nullptr;
};


#endif // DATA_STRUCTURE_SHARED_PTR_SRC_LOCK_FREE_PTR_HPP_
