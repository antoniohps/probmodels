#ifndef FACTOR_BASE_HPP
#define FACTOR_BASE_HPP

#include <tuple>
#include <unordered_map>

#include "base/variable.hpp"
#include "util/tuple_algorithm.hpp"

namespace probmodels {
namespace base {

template<typename... VarTypes>
struct factor {

    //requires is_same<VarTypes...::descriptor, VarDescriptor>::value == true

    template <typename VarType>
    using _var_map_type = std::unordered_map <
            VarType,
            std::size_t,
            std::hash<typename VarType::descriptor>,
            std::equal_to<typename VarType::descriptor>
    >;

    //Default/Copy/Move constructors
    factor() = default;
    factor(const factor& other) = default;
    factor(factor&& other) = default;

    //Initialize hash map buckets
    //Two pack expansions?? Yeah, we can do it! See: http://en.cppreference.com/w/cpp/language/parameter_pack
    template <typename... Sizes>
    factor(Sizes&&... sizes) : _nvars(0), _var_map(_var_map_type<VarTypes>{sizes}...){
        static_assert(sizeof...(Sizes) == sizeof...(VarTypes),
                      "The number buckets must match each variable type.");
    }

    //Get the overall variable count
    std::size_t variable_count() const {
        return _nvars;
    }

    //Add a variable of supported type
    template <typename VarType>
    void add_variable(const VarType& variable) {
        std::get< _var_map_type<VarType> >(_var_map)
                [variable] = _nvars++;
    }
    //Adding a variable (move semantics)
    template <typename VarType>
    void add_variable(VarType&& variable) {
        std::get< _var_map_type<VarType> >(_var_map)
                [std::move(variable)] = _nvars++;
    }

private:
    std::size_t _nvars;
    std::tuple < _var_map_type<VarTypes>... >_var_map;
};

}
}


#endif // FACTOR_BASE_HPP
