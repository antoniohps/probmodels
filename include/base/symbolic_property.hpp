//Symbolic Property
#ifndef _PROBMODELS_BASE_SYMBOLIC_PROPERTY_HPP_
#define _PROBMODELS_BASE_SYMBOLIC_PROPERTY_HPP_

#include <array>

#include "boost/pending/property.hpp"

namespace probmodels {
namespace base {

//Property must be copyable, assignable and copy constructable
template <std::size_t Len, typename Property = boost::no_property>
class SymbolicProperty {

    static const std::size_t _array_len = Len+1;

public:
    SymbolicProperty() {}
    SymbolicProperty(const SymbolicProperty& prop) :
        _label(prop._label), _prop(prop._prop) {}

    inline const char* label() const { return _label; }

    SymbolicProperty& operator= (const SymbolicProperty& property) {
        std::copy(property._label, property._label+Len+1, _label);
    }

private:
    std::array<char,_array_len> _label;
    Property _prop;
};

}
}

#endif
