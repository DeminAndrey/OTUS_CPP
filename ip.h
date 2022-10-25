#pragma once

#include <cstdint>
#include <tuple>

struct ip_t {
  std::uint8_t _0;
  std::uint8_t _1;
  std::uint8_t _2;
  std::uint8_t _3;
};

/**
 * @brief перегруженный оператор сравнения двух структур ip_t
 * @param lhs, rhs сравниваемые структуры
 * @return результат сравнения - равны / не равны
 */
inline bool operator==(const ip_t& lhs, const ip_t& rhs) {
  return std::tie(lhs._0, lhs._1, lhs._2, lhs._3) ==
      std::tie(rhs._0, rhs._1, rhs._2, rhs._3);
}
