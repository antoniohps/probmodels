#ifndef TUPLE_ALGORITHM_HPP
#define TUPLE_ALGORITHM_HPP

#include <tuple>
#include <utility>
#include <functional>

namespace probmodels {
namespace util {

namespace _detail {

template<std::size_t Pos, typename... Types>
struct tuple_algo_impl {
    ///Tuple foreach
    template <typename UnaryFunctor>
    static UnaryFunctor for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
    {
        func(std::get<sizeof...(Types) - Pos>(tuple));
        return tuple_algo_impl<Pos-1,Types...>::for_each(std::forward<std::tuple<Types...> >(tuple), func);
    }

    ///Tuple reverse foreach
    template <typename UnaryFunctor>
    static UnaryFunctor reverse_for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
    {
        func(std::get<Pos - 1>(tuple));
        return tuple_algo_impl<Pos-1,Types...>::reverse_for_each(std::forward<std::tuple<Types...> >(tuple), func);
    }

    ///Tuple sum
    template <typename ElementType,  typename BinaryFunctor>
    static ElementType sum(std::tuple<Types...>&& tuple, BinaryFunctor&& func, ElementType&& current_value)
    {
        return tuple_algo_impl<Pos-1,Types...>::sum (
                    std::forward<std::tuple<Types...> >(tuple),
                    func, std::forward<ElementType>(
                        func(std::forward<ElementType>(current_value), std::get<sizeof...(Types) - Pos>(tuple))
                        ));
    }

    ///Tuple reverse sum
    template <typename ElementType,  typename BinaryFunctor>
    static ElementType reverse_sum(std::tuple<Types...>&& tuple, BinaryFunctor&& func, ElementType&& current_value)
    {
        return tuple_algo_impl<Pos-1,Types...>::reverse_sum (
                    std::forward<std::tuple<Types...> >(tuple),
                    func, std::forward<ElementType>(
                        func(std::forward<ElementType>(current_value), std::get<Pos - 1>(tuple))
                        ));
    }
};

//Specialization for Pos = 0
template<typename... Types>
struct tuple_algo_impl<0, Types...> {

    ///Tuple foreach
    template <typename UnaryFunctor>
    static UnaryFunctor&& for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
    {
        return std::forward<UnaryFunctor>(func);
    }

    ///Tuple reverse_foreach
    template <typename UnaryFunctor>
    static UnaryFunctor&& reverse_for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
    {
        return std::forward<UnaryFunctor>(func);
    }

    ///Tuple sum
    template <typename ElementType,  typename BinaryFunctor>
    static ElementType&& sum(std::tuple<Types...>&& tuple, BinaryFunctor&& func, ElementType&& current_value)
    {
        return std::forward<ElementType>(current_value);
    }

    ///Tuple reverse_sum
    template <typename ElementType,  typename BinaryFunctor>
    static ElementType&& reverse_sum(std::tuple<Types...>&& tuple, BinaryFunctor&& func, ElementType&& current_value)
    {
        return std::forward<ElementType>(current_value);
    }
};

}

//Algorithm invocation

/// tuple_for_each
template <typename UnaryFunctor, typename... Types>
UnaryFunctor tuple_for_each(std::tuple<Types...>& tuple, UnaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::for_each(std::forward<std::tuple<Types...> >(tuple),func);
}

template <typename UnaryFunctor, typename... Types>
UnaryFunctor tuple_for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::for_each(std::forward<std::tuple<Types...> >(tuple),func);
}

template <typename UnaryFunctor, typename... Types>
UnaryFunctor tuple_reverse_for_each(std::tuple<Types...>& tuple, UnaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::reverse_for_each(std::forward<std::tuple<Types...> >(tuple),func);
}

template <typename UnaryFunctor, typename... Types>
UnaryFunctor tuple_reverse_for_each(std::tuple<Types...>&& tuple, UnaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::reverse_for_each(std::forward<std::tuple<Types...> >(tuple),func);
}

/// tuple_sum
template <typename ElementType,  typename BinaryFunctor, typename... Types>
ElementType tuple_sum(std::tuple<Types...>&& tuple, ElementType&& initial, BinaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::sum(std::forward<std::tuple<Types...> >(tuple),func,std::forward<ElementType>(initial));
}

template <typename ElementType, typename... Types>
ElementType tuple_sum(std::tuple<Types...>&& tuple, ElementType&& initial)
{
    return tuple_sum(std::forward<std::tuple<Types...> >(tuple), std::forward<ElementType>(initial), std::plus<ElementType>());
}

template <typename ElementType,  typename BinaryFunctor, typename... Types>
ElementType tuple_reverse_sum(std::tuple<Types...>&& tuple, ElementType&& initial, BinaryFunctor&& func)
{
    return _detail::tuple_algo_impl<sizeof...(Types),Types...>::reverse_sum(std::forward<std::tuple<Types...> >(tuple),func,std::forward<ElementType>(initial));
}


}

}

#endif // TUPLE_ALGORITHM_HPP
