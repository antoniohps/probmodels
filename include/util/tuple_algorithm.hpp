#ifndef TUPLE_ALGORITHM_HPP
#define TUPLE_ALGORITHM_HPP

#include <tuple>
#include <functional>

namespace probmodels {
namespace util {

namespace _detail {

template<std::size_t Pos, typename... Types>
struct tuple_algo_impl {
    ///Tuple foreach
    template <typename UnaryFunctor>
    static UnaryFunctor for_each(std::tuple<Types...>& tuple, UnaryFunctor&& func)
    {
        func(std::get<sizeof...(Types) - Pos>(tuple));
        return tuple_algo_impl<Pos-1,Types...>::for_each(tuple, func);
    }

    template <typename UnaryFunctor>
    static UnaryFunctor for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
    {
        func(std::get<sizeof...(Types) - Pos>(tuple));
        return tuple_algo_impl<Pos-1,Types...>::for_each(tuple, func);
    }

    ///Tuple sum
    template <typename ElementType,  typename BinaryFunctor>
    static ElementType sum(const std::tuple<Types...>& tuple, BinaryFunctor&& func, const ElementType& current_value)
    {
        return tuple_algo_impl<Pos-1,Types...>::sum
                (tuple, func, func(current_value, std::get<sizeof...(Types) - Pos>(tuple)));
    }
};

//Specialization for Pos = 0
template<typename... Types>
struct tuple_algo_impl<0, Types...> {

    ///Tuple foreach
    template <typename UnaryFunctor>
    static UnaryFunctor for_each(std::tuple<Types...>& tuple, UnaryFunctor&& func)
    {
        return func;
    }

    template <typename UnaryFunctor>
    static UnaryFunctor for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
    {
        return func;
    }

    ///Tuplesum
    template <typename ElementType,  typename BinaryFunctor>
    static ElementType sum(const std::tuple<Types...>& tuple, BinaryFunctor&& func, const ElementType& current_value)
    {
        return current_value;
    }
};

}

//Algorithm invocation

/// tuple_for_each
template <typename UnaryFunctor, typename... Types>
UnaryFunctor tuple_for_each(std::tuple<Types...>& tuple, UnaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::for_each(tuple,func);
}

template <typename UnaryFunctor, typename... Types>
UnaryFunctor tuple_for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::for_each(tuple,func);
}

/// tuple_sum
template <typename ElementType,  typename BinaryFunctor, typename... Types>
ElementType tuple_sum(const std::tuple<Types...>& tuple, const ElementType& initial, BinaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::sum(tuple,func,initial);
}

template <typename ElementType, typename... Types>
ElementType tuple_sum(const std::tuple<Types...>& tuple, const ElementType& initial)
{
    return tuple_sum(tuple, initial, std::plus<ElementType>());
}


}

}

#endif // TUPLE_ALGORITHM_HPP
