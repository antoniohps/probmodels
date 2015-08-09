#ifndef BASE_VARIABLE_HPP
#define BASE_VARIABLE_HPP

namespace probmodels {
namespace base {

template <typename DescriptorType, typename InstanceType>
struct variable {

    variable() {}
    variable(const variable& v) : _desc(v._desc) {}

    typedef DescriptorType descriptor;
    typedef InstanceType instance;

private:
    DescriptorType _desc;
};

}

}


#endif // VARIABLE_HPP
