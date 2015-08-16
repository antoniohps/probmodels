#ifndef DIST_BINARY_HPP
#define DIST_BINARY_HPP

#include <array>
#include <tuple>
#include <vector>
#include <cassert>

#include "base/variable.hpp"
#include "base/factor.hpp"

namespace probmodels {
namespace dist {

//The binary_variable type
template <typename Descriptor>
struct binary_variable : public base::variable<Descriptor, bool>
{
    typedef base::variable<Descriptor, bool> base_type;
    typedef typename base_type::descriptor descriptor;

    //A variable must have a non-empty descritor
    binary_variable() = delete;

    //Copy/move Constructors
    binary_variable(const binary_variable& v) = default;
    binary_variable(binary_variable&& v) = default;

    //Initializing from varible descriptor
    binary_variable(const descriptor& descript) : base_type(descript) { }
    binary_variable(descriptor&& descript) : base_type(std::move(descript)) { }

};

template <typename VarDescriptor>
class binary_factor : base::factor<binary_variable<VarDescriptor> > {

    //require Variables as tuple of variables
    //require Conditions as tuple of variables

    typedef VarDescriptor variable_descriptor;
    typedef base::factor<binary_variable<VarDescriptor> > base_type;

public:

    //Default/copy/mpve Constructors
    binary_factor() : _values(1, 0.5) { }
    binary_factor(const binary_factor& other) = default;
    binary_factor(binary_factor&& other) = default;

    //Reserve space for future variables
    binary_factor(std::size_t size) : base_type(size), _values(1, 0.5) {
        _values.reserve(1 << size);
    }

    //Add variable to the factor
    void add_variable(const variable_descriptor& var) {
        base_type::add_variable(binary_variable<variable_descriptor>(var));
        this->_accomodate_new();
    }

    void add_variable(variable_descriptor&& var) {
        base_type::add_variable(binary_variable<variable_descriptor>(std::move(var)));
        this->_accomodate_new();
    }

    template<typename... BooleanConvertible>
    void set_value(double value, const BooleanConvertible&... vars) {
        assert(this->variable_count() == sizeof...(vars));
        _values[find_var_index(vars...)] = value;
    }

    template<typename... BooleanConvertible>
    double get_value(const BooleanConvertible&... vars) const {
        assert(this->variable_count() == sizeof...(vars));
        return _values[find_var_index(vars...)];
    }

private:
    std::vector<double> _values;

    //Create index in Little Endian style
    //required for allowing factor resize without index changes
    template<typename... BooleanConvertible>
    static std::size_t find_var_index(const BooleanConvertible&... bits) {
        static_assert((sizeof...(bits)>>3) <= (sizeof(std::size_t)),
                      "The number of boolean parameters must fit the default integer type");

        return util::tuple_reverse_sum(std::forward_as_tuple(bits...), std::size_t(0), [](std::size_t curr, bool bit){
            return (curr<<1) | bit;
        });
    }

    //Accomodate new variable in the table, replicating its values for
    //  "new_var=true"
    void _accomodate_new() {
        std::size_t old_size = _values.size();
        _values.reserve(old_size << 1);
        for(std::size_t i=0; i < old_size; ++i) {
            _values.push_back(_values[i]);
        }
    }
};


/// Represents the probability of an event given th
template <typename VarDescriptor>
class conditional_multivar_binary_distribution
        : public binary_factor<VarDescriptor>
{

    //require Variables as tuple of variables
    //require Conditions as tuple of variables

    typedef binary_factor<VarDescriptor> base_type;

public:

    typedef VarDescriptor variable_descriptor;

    //The variable under evaluation is mandatory
    template <typename... Conditions>
    conditional_multivar_binary_distribution( variable_descriptor&& desc, Conditions&&... cond) :
        base_type(1 + sizeof...(Conditions))
    {
        this->base_type::add_variable(std::forward<variable_descriptor>(desc));

        util::tuple_for_each(std::forward_as_tuple(cond...),
                             [this](variable_descriptor&& desc2){
            this->base_type::add_variable(std::forward<variable_descriptor>(desc2));
        });
    }

    //Adding a new condition
    void add_variable() = delete;

    void add_condition(variable_descriptor&& desc) {
        this->base_type::add_variable(
                    std::forward<variable_descriptor>(desc));
    }

    //Set probability value given conditions
    template<typename... BooleanConvertible>
    void set_probability(double value, BooleanConvertible... conditions) {
        assert(value>= 0.0 && value <= 1.0);
        this->set_value(value, true, conditions...);
        this->set_value(1.0 - value, false, conditions...);
    }

    //Get probability value given conditions
    template<typename... BooleanConvertible>
    double get_probability(BooleanConvertible... conditions) {
        return this->get_value(true, conditions...);
    }
};


}
}

#endif
