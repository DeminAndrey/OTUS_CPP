#include "auxiliary.h"

#include <stdexcept>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

std::vector<std::string> aux::split(const std::string& str,
                               char separator) noexcept {
  std::vector<std::string> results;
  boost::split(results, str, boost::is_any_of(std::string{separator}),
               boost::token_compress_on);
  return results;
}

ip_t aux::splitted_to_ip(const std::vector<std::string>& splitted) {
  if (splitted.size() != 4) {
    throw std::invalid_argument("IP must consist of 4 parts");
  }

  int _0 = std::stoi(splitted[0]);
  int _1 = std::stoi(splitted[1]);
  int _2 = std::stoi(splitted[2]);
  int _3 = std::stoi(splitted[3]);

  if (_0 < 0 || _0 > 255 ||
      _1 < 0 || _1 > 255 ||
      _2 < 0 || _2 > 255 ||
      _3 < 0 || _3 > 255) {

    throw std::invalid_argument("IP parts must be from 0 to 255");
  }
  return ip_t {
    static_cast<std::uint8_t>(_0),
    static_cast<std::uint8_t>(_1),
    static_cast<std::uint8_t>(_2),
    static_cast<std::uint8_t>(_3)
  };
}

std::vector<ip_t> aux::get_ips_from_string(const std::string& input) {
  std::vector<ip_t> ip_pool;
  std::istringstream sstream(input);
  for (std::string line; std::getline(sstream, line);) {
    auto splitted = split(line, '\t');
    ip_pool.push_back(splitted_to_ip(split(splitted.at(0), '.')));
  }
  return ip_pool;
}
