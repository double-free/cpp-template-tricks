#pragma once

namespace yy {
      template <size_t Index, typename T, typename Tuple>
      constexpr typename std::enable_if_t<Index == std::tuple_size_v<Tuple>, size_t>
      tuple_element_index_helper()
      {
          return Index;
      }
      template <size_t Index, typename T, typename Tuple>
      constexpr typename std::enable_if_t<(Index < std::tuple_size_v<Tuple>), size_t>
      tuple_element_index_helper()
      {
          if constexpr (std::is_same_v<T, std::tuple_element_t<Index, Tuple>>)
          {
              // found
              return Index;
          }

          return tuple_element_index_helper<Index + 1, T, Tuple>();
      }

      // return the index of the type in a tuple
      // the index == tuple_size if not found
      template <typename T, typename Tuple>
      constexpr size_t element_index()
      {
          return tuple_element_index_helper<0, T, Tuple>();
      }
} // namespace yy
