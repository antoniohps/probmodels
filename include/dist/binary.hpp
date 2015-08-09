#ifndef DIST_BINARY_HPP
#define DIST_BINARY_HPP

#include <array>
#include <tuple>
#include <cassert>

#include "base/variable.hpp"
#include "base/factor.hpp"

namespace probmodels {
namespace dist {

template <typename Descriptor>
struct binary_variable : public base::variable<Descriptor, bool> {};

template <typename VarDescriptor>
class binary_factor : base::factor<binary_variable<VarDescriptor> > {

    //require Variables as tuple of variables
    //require Conditions as tuple of variables

    typedef base::factor<binary_variable<VarDescriptor> > base_type;

public:

    binary_factor() : base_type() { }
    binary_factor(std::size_t size) : base_type(size), _values(1 << size) { }

    std::size_t variable_count() const { return base_type::variable_count(0); }

    template<typename... BooleanConvertible>
    void set_value(double value, BooleanConvertible... vars) {

        assert(_values.size() == sizeof...(BooleanConvertible));
/*
        std::size_t index = 0;
        std::size_t
        for(auto var : std::tie(vars)) {
            index +=
        }

        set_value(value, true, conditions);
        set_value(value, false, conditions);
        */
    }


private:
    std::vector<double> _values;

    /*
    template<std::size_t Pos, typename... BooleanConvertible>
    std::size_t find_var_index(BooleanConvertible... bits) {
        return (((std::size_t)(bool)std::get<Pos>(bits)) << Pos)
                + find_var_index<Pos-1,BooleanConvertible...>;
    }

    template<typename... BooleanConvertible>
    std::size_t find_var_index<0,BooleanConvertible...> (BooleanConvertible... bits) {
        return (((std::size_t)(bool)std::get<Pos>(bits)) << Pos);
    }*/

};


template <typename VarDescriptor>
class conditional_multivar_binary_distribution
        : public binary_factor<VarDescriptor>
{

    typedef binary_factor<VarDescriptor> base;

    //require Variables as tuple of variables
    //require Conditions as tuple of variables
/*
    template<typename... BooleanConvertible>
    void set_probability(double value, BooleanConvertible... conditions) {
        assert(value>= 0.0 && value <= 1.0);
        set_value(value, true, conditions);
        set_value(1.0 - value, false, conditions);
    }
    */
};


}
}

#endif
