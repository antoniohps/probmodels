#ifndef TUPLE_OPERATIONS_HPP
#define TUPLE_OPERATIONS_HPP

#include <tuple>
#include <type_traits>

namespace probmodels {
namespace util {

//Set pertinence test
template <typename U, typename Tup>
struct belongs_to;

template <typename U, typename... Tail>
struct belongs_to<U, std::tuple<U, Tail...> > : public std::true_type
{ };

template <typename U, typename T, typename... Tail>
struct belongs_to<U, std::tuple<T, Tail...> > : public belongs_to<U,std::tuple<Tail...> >
{ };

template <typename U>
struct belongs_to<U,std::tuple<> > : public std::false_type
{ };

//Conditional tuple element swallow
template <typename Tup1, typename Tup2, bool... Test>
struct tuple_swallow;
//require Tup1 and Tup2 to be tuples

template <typename... T1, typename Head, typename... Tail, bool... Test>
struct tuple_swallow <std::tuple<T1...>, std::tuple<Head, Tail...>, true, Test...>
        : public tuple_swallow <std::tuple<T1..., Head>, std::tuple<Tail...>, Test...>
{ };

template <typename... T1, typename Head, typename... Tail, bool... Test>
struct tuple_swallow <std::tuple<T1...>, std::tuple<Head, Tail...>, false, Test...>
        : public tuple_swallow <std::tuple<T1...>, std::tuple<Tail...>, Test...>
{ };

template <typename... T1>
struct tuple_swallow <std::tuple<T1...>, std::tuple<> >
{
    typedef std::tuple<T1...> type;
};

//Tuple union
template<typename T1, typename T2>
struct tuple_union;

//Partial specialization for tuples
template<typename... T1, typename... T2>
struct tuple_union<std::tuple<T1...>, std::tuple<T2...> > :
        public tuple_swallow< std::tuple<T1...>, std::tuple<T2...>,
                   (!belongs_to<T2, std::tuple<T1...> >::value)...>
{ };


}
}


#endif // TUPLE_OPERATIONS_HPP
