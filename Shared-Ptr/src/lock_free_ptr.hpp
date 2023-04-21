//
// Created by believe on 2023/4/20.
//

#ifndef DATA_STRUCTURE_SHARED_PTR_SRC_LOCK_FREE_PTR_HPP_
#define DATA_STRUCTURE_SHARED_PTR_SRC_LOCK_FREE_PTR_HPP_

#include <atomic>
#include <memory>
#include <cstddef>
#include <thread>

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
            ref_count_->fetch_add(1, std::memory_order_relaxed);
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
        while (ptr && ref_count->load(std::memory_order_relaxed)) {
            auto expected = ref_count->load(std::memory_order_relaxed);
            if (ref_count->compare_exchange_weak(expected, expected + 1, std::memory_order_relaxed, std::memory_order_relaxed)) {
                return std::shared_ptr<T>(ptr, [ref_count](T* p) {
                    if (ref_count->fetch_sub(1, std::memory_order_release) == 1) {
                        std::atomic_thread_fence(std::memory_order_acquire);
                        delete p;
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

template <typename T>
class LockFreeSharedPtr {
public:
    LockFreeSharedPtr() {
        count_.store(new CountedPtr(0, new T()));
    }

    explicit LockFreeSharedPtr(T* ptr) {
        count_.store(new CountedPtr(1, ptr));
    }

    LockFreeSharedPtr(const LockFreeSharedPtr& other) {
        count_.store(other.count_);
        AddRef();
    }

    LockFreeSharedPtr& operator=(const LockFreeSharedPtr& other) {
        CountedPtr* old_cp = count_.exchange(other.count_);
        RemoveRef(old_cp);
        AddRef();
        return *this;
    }

    ~LockFreeSharedPtr() {
        RemoveRef(count_);
    }

    T* Get() const {
        return count_.load()->ptr;
    }

    T& operator*() const {
        return *(count_.load()->ptr);
    }

    T* operator->() const {
        return count_.load()->ptr;
    }

    operator bool() const {
        return (count_.load()->ptr != nullptr);
    }

private:
    struct CountedPtr {
        int count;
        T* ptr;

        CountedPtr(int count, T* ptr) : count(count), ptr(ptr) {}
    };

    std::atomic<CountedPtr*> count_;

    void AddRef() {
        CountedPtr* old_cp = count_.load();
        do {
            ++old_cp->count;
        } while (!count_.compare_exchange_strong(old_cp, old_cp));
    }

    void RemoveRef(CountedPtr* old_cp) {
        if (--old_cp->count == 0) {
            delete old_cp->ptr;
            delete old_cp;
        }
    }
};

#endif // DATA_STRUCTURE_SHARED_PTR_SRC_LOCK_FREE_PTR_HPP_
