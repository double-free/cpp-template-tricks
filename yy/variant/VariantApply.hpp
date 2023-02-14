#pragma once

#include <variant>
#include <cstddef>

namespace yy
{
    template <size_t I, typename FuncT, typename VariantT>
    bool try_apply_to_type_idx(FuncT f,  VariantT &v)
    {
        using ExpectedType = std::variant_alternative_t<I, VariantT>;
        auto *p = std::get_if<ExpectedType>(&v);
        if (p == nullptr)
        {
            return false;
        }
        f(*p);
        return true;
    }

    template <typename FuncT, typename VariantT, size_t... Is>
    bool apply_helper(FuncT f,  VariantT &v, std::index_sequence<Is...>)
    {
        bool success = (... || try_apply_to_type_idx<Is>(f, v));
        return success;
    }

    // apply function to std::variant
    template <typename FuncT, typename... Types>
    bool try_apply(FuncT f,  std::variant<Types...> &v)
    {
        return apply_helper(f, v, std::index_sequence_for<Types...>{});
    }
} // namespace yy
