#pragma once

#include "ip.h"

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

namespace aux {

/**
 * @brief сортирует вектор в лексикографическом порядке
 * @param ip_pool вектор ip_t
 */
inline void sort(std::vector<ip_t> &ip_pool) {
  std::sort(ip_pool.begin(), ip_pool.end(),
            [](const ip_t& lhs, const ip_t& rhs) {
    return std::tie(lhs._0, lhs._1, lhs._2, lhs._3)
        > std::tie(rhs._0, rhs._1, rhs._2, rhs._3);
  });
}

/**
 * @brief разбивает строку на подстроки разделителем
 * @param str входная строка
 * @param separator разделитель который делит подстроки
 * @return вектор строк
 */
std::vector<std::string> split(const std::string& str,
                               char separator) noexcept;

/**
 * @brief создает новую структуру ip_t из вектора строк
 * @param splitted вектор строк
 * @return структура ip_t
 */
ip_t splitted_to_ip(const std::vector<std::string>& splitted);

/**
 * @brief возвращает вектор структур ip_t из строки
 * @param input входная строка
 * @return вектор структур ip_t
 */
std::vector<ip_t> get_ips_from_string(const std::string& input);

} // namespace aux
