#include "auxiliary.h"
#include "filter.h"
#include "input.h"
#include "ip.h"
#include "output.h"

#include <algorithm>
#include <tuple>

#include <gtest/gtest.h>

TEST(Filter, CheckFilter) {
  auto ip_pool = aux::get_ips_from_string(IP_LIST);
  std::sort(ip_pool.begin(), ip_pool.end(),
            [](const ip_t& lhs, const ip_t& rhs) {
    return std::tie(lhs._0, lhs._1, lhs._2, lhs._3)
        > std::tie(rhs._0, rhs._1, rhs._2, rhs._3);
  });
  ASSERT_EQ(ip_pool, FILTERED);
}

TEST(Filter, CheckFilter_1) {
  auto ip_pool = aux::get_ips_from_string(IP_LIST);
  aux::sort(ip_pool);
  FilteredVectorAdaptor filter1(
        ip_pool, [](const ip_t& ip) {
    return (ip._0 == 1);
  });
  ASSERT_TRUE(FILTERED_BY_1.size());
  auto it = FILTERED_BY_1.begin();
  for (const auto& ip : filter1) {
    ASSERT_FALSE(it == FILTERED_BY_1.end());
    ASSERT_EQ(ip, *it++);
  }
}

TEST(Filter, CheckFilter_46_70) {
  auto ip_pool = aux::get_ips_from_string(IP_LIST);
  aux::sort(ip_pool);
  FilteredVectorAdaptor filter46_70(
        ip_pool, [](const ip_t& ip) {
    return (ip._0 == 46 && ip._1 == 70);
  });
  ASSERT_TRUE(FILTERED_BY_46_70.size());
  auto it = FILTERED_BY_46_70.begin();
  for (const auto& ip : filter46_70) {
    ASSERT_FALSE(it == FILTERED_BY_46_70.end());
    ASSERT_EQ(ip, *it++);
  }
}

TEST(Filter, CheckFilter_any_46) {
  auto ip_pool = aux::get_ips_from_string(IP_LIST);
  aux::sort(ip_pool);
  FilteredVectorAdaptor filter46_any(
        ip_pool, [](const ip_t& ip) {
    return (ip._0 == 46 || ip._1 == 46 || ip._2 == 46 || ip._3 == 46);
  });
  ASSERT_TRUE(FILTERED_BY_ANY_46.size());
  auto it = FILTERED_BY_ANY_46.begin();
  for (const auto& ip : filter46_any) {
    ASSERT_FALSE(it == FILTERED_BY_ANY_46.end());
    ASSERT_EQ(ip, *it++);
  }
}
