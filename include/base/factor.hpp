#ifndef FACTOR_BASE_HPP
#define FACTOR_BASE_HPP

#include <tuple>
#include <vector>

#include "base/variable.hpp"
#include "util/tuple_algorithm.hpp"

namespace probmodels {
namespace base {

template<typename... VarTypes>
struct factor {

protected:

    factor() {}
    factor(std::size_t numvars) {
        variable_reserve(std::array<std::size_t, sizeof...(VarTypes)>(numvars));
    }
    template <typename SizeSequence>
    factor(SizeSequence&& _sizes) {
        variable_reserve(_sizes);
    }

    template <typename VarType>
    std::size_t variable_count() const {
        return std::get<std::vector<VarType>>(_var_map).size();
    }

    template <typename SizeSequence>
    void variable_reserve(SizeSequence&& _sizes) {
        //require SizeSequence::value_type is convertible to std::size_t
        assert(_sizes.size() == sizeof...(VarTypes));
        auto it = _sizes.begin();
        util::tuple_for_each(_var_map, [it](auto element){ element.reserve(*it++);});
    }

private:
    std::tuple<std::vector<VarTypes...>> _var_map;
};

}
}


#endif // FACTOR_BASE_HPP
