#pragma once

#include <tuple>
#include <cstddef>

namespace yy
{
    template <typename T1, typename T2>
    constexpr bool are_irrelevant_types()
    {
        if constexpr (std::is_same_v<T1, T2>)
        {
            return false;
        }
        if constexpr (std::is_base_of_v<T1, T2> || std::is_base_of_v<T2, T1>)
        {
            return false;
        }
        return true;
    }
    template <typename Tuple, size_t Idx, size_t... OtherIdx>
    constexpr bool tuple_element_check_helper(std::index_sequence<OtherIdx...>)
    {
        return (... && are_irrelevant_types<std::tuple_element_t<Idx, Tuple>,
                                            std::tuple_element_t<OtherIdx, Tuple>>());
    }

    // As a rule any form of partial template specialisation is not allowed for functions.
    // We have to wrap it in a class
    template <typename Tuple, size_t UntilIdx>
    struct TupleElementChecker
    {
        static constexpr bool check()
        {
            // Idx >= 2
            bool ok = tuple_element_check_helper<Tuple, UntilIdx - 1>(
                std::make_index_sequence<UntilIdx - 1>{});

            return ok && TupleElementChecker<Tuple, UntilIdx - 1>::check();
        }
    };
    template <typename Tuple>
    struct TupleElementChecker<Tuple, 0>
    {
        static constexpr bool check()
        {
            return true;
        }
    };
    template <typename Tuple>
    struct TupleElementChecker<Tuple, 1>
    {
        static constexpr bool check()
        {
            return true;
        }
    };

    // This function check in COMPILE time if all elements in a tuple are irrelevant types
    // "irrelevant types" mean type A is neither the same with B nor derived from B.
    template <typename Tuple>
    constexpr bool irrelevant_element_types()
    {
        return TupleElementChecker<Tuple, std::tuple_size_v<Tuple>>::check();
    }
} // namespace yy
