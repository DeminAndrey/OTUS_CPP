#include "auxiliary.h"
#include "filter.h"
#include "ip.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

template <typename IpPool>
void print_pool(const IpPool& ip_pool) {
  for (const ip_t& ip : ip_pool) {
    std::cout << static_cast<int>(ip._0) << '.'
              << static_cast<int>(ip._1) << '.'
              << static_cast<int>(ip._2) << '.'
              << static_cast<int>(ip._3) << '\n';
  }
}

int main(int, char const*[]) {
  try {
    std::vector<ip_t> ip_pool;
    for (std::string line; std::getline(std::cin, line);) {
      if (line.empty()) { break; }
      ip_pool.push_back(aux::splitted_to_ip(aux::split(line, '.')));
    }
    aux::sort(ip_pool);

    FilteredVectorAdaptor filter1(
          ip_pool, [](const ip_t& ip) {
      return (ip._0 == 1);
    });

    FilteredVectorAdaptor filter46_70(
          ip_pool, [](const ip_t& ip) {
      return (ip._0 == 46 && ip._1 == 70);
    });

    FilteredVectorAdaptor filter46_any(
          ip_pool, [](const ip_t& ip) {
      return (ip._0 == 46 || ip._1 == 46 || ip._2 == 46 || ip._3 == 46);
    });

    print_pool(ip_pool);
    print_pool(filter1);
    print_pool(filter46_70);
    print_pool(filter46_any);
  }
  catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}
