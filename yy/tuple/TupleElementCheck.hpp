#pragma once

#include <cstddef>
#include <tuple>

namespace yy {
template <typename T1, typename T2> constexpr bool are_irrelevant_types() {
  if constexpr (std::is_same_v<T1, T2>) {
    return false;
  }
  if constexpr (std::is_base_of_v<T1, T2> || std::is_base_of_v<T2, T1>) {
    return false;
  }
  return true;
}

// loop through element type at 0 to Idx-1 and compare it with Idx
template <typename Tuple, size_t Idx, size_t... OtherIdx>
constexpr bool tuple_element_check_against(std::index_sequence<OtherIdx...>) {
  return (... && are_irrelevant_types<std::tuple_element_t<Idx, Tuple>,
                                      std::tuple_element_t<OtherIdx, Tuple>>());
}

template <typename Tuple, size_t Index>
std::enable_if_t<Index == 0, bool> constexpr tuple_element_check_until() {
  return true;
}

template <typename Tuple, size_t Index>
std::enable_if_t<(Index > 0), bool> constexpr tuple_element_check_until() {

  bool ok = tuple_element_check_against<Tuple, Index>(
      std::make_index_sequence<Index>{});
  // if success, continue to check the one before
  return ok && tuple_element_check_until<Tuple, Index - 1>();
}

// check if element types in a tuple are relevant
template <typename Tuple>
std::enable_if_t<(std::tuple_size_v<Tuple> <= 1),
                 bool> constexpr irrelevant_element_types() {
  return true;
}
template <typename Tuple>
std::enable_if_t<(std::tuple_size_v<Tuple> > 1),
                 bool> constexpr irrelevant_element_types() {
  return tuple_element_check_until<Tuple, std::tuple_size_v<Tuple> - 1>();
}
} // namespace yy
