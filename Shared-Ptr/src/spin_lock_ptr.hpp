

//
// Created by believe on 2023/4/20.
//

#ifndef DATA_STRUCTURE_SHARED_PTR_SRC_SPIN_LOCK_PTR_HPP_
#define DATA_STRUCTURE_SHARED_PTR_SRC_SPIN_LOCK_PTR_HPP_

#include <dlfcn.h>
#include <map>
#include <mutex>
#include <type_traits>

class spin_lock {
public:
  spin_lock() = default;

  ~spin_lock() = default;

  spin_lock(const spin_lock &) = delete;

  spin_lock(spin_lock &&) = delete;

  spin_lock &operator=(const spin_lock &) = delete;

  spin_lock &operator=(spin_lock &&) = delete;

  void lock() {
    while (flag_.exchange(true, std::memory_order_acquire))
      ;
  }

  void unlock() { flag_.exchange(false, std::memory_order_release); }

private:
  std::atomic<bool> flag_{false};
};

template <class Ty, class Mutex = spin_lock> class spin_atomic_shared_ptr {
public:
  spin_atomic_shared_ptr() = default;

  explicit spin_atomic_shared_ptr(const std::shared_ptr<Ty> &ptr) : ptr_(ptr) {}

  spin_atomic_shared_ptr(const spin_atomic_shared_ptr &rhs) {
    spin_atomic_shared_ptr(rhs.load());
  }

  ~spin_atomic_shared_ptr() = default;

  spin_atomic_shared_ptr &operator=(const std::shared_ptr<Ty> &ptr) {
    store(ptr);
    return *this;
  }

  std::shared_ptr<Ty> operator*() { return load(); }

  std::shared_ptr<Ty> operator->() { return load(); }

  explicit operator std::shared_ptr<Ty>() const { return load(); }

  std::shared_ptr<Ty> load() const {
    std::lock_guard<Mutex> lock(mutex_);
    return ptr_;
  }

  void store(const std::shared_ptr<Ty> &ptr) {
    std::lock_guard<Mutex> lock(mutex_);
    ptr_ = ptr;
  }

private:
  std::shared_ptr<Ty> ptr_;
  mutable Mutex mutex_;
};

#endif // DATA_STRUCTURE_SHARED_PTR_SRC_SPIN_LOCK_PTR_HPP_
