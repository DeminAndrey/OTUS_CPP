#pragma once

#include "ip.h"

#include <functional>
#include <vector>
#include <utility>

/**
 * @brief класс адаптор для вектора структур ip_t
 */
class FilteredVectorAdaptor {
public:
  FilteredVectorAdaptor(const std::vector<ip_t>& pool,
                        std::function<bool(const ip_t&)> predicate)
    : m_pool(pool)
    , m_predicate(std::move(predicate)) {
  }

  class Iterator {
private:
  friend class FilteredVectorAdaptor;

  Iterator(typename std::vector<ip_t>::const_iterator it,
           const FilteredVectorAdaptor* filter)
    : m_it(it)
    , m_filter(filter) {
    while (m_it != m_filter->m_pool.cend()
           && !m_filter->m_predicate(*m_it)) {
      ++m_it;
    }
  }

  public:
    Iterator& operator++() {
      ++m_it;
      while (m_it != m_filter->m_pool.cend()
             && !m_filter->m_predicate(*m_it)) {
        ++m_it;
      }
      return *this;
    }

    const ip_t& operator*() const {
      return *m_it;
    }

    bool operator!=(const Iterator& other) {
      return m_it != other.m_it;
    }

  private:
    typename std::vector<ip_t>::const_iterator m_it;
    const FilteredVectorAdaptor* m_filter;
  };

  Iterator begin() const {
    return Iterator{ m_pool.cbegin(), this };
  }

  Iterator end() const {
    return Iterator{ m_pool.cend(), this };
  }

private:
  const std::vector<ip_t>& m_pool;
  std::function<bool(const ip_t&)> m_predicate;
};
