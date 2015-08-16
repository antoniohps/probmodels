#ifndef BASE_VARIABLE_HPP
#define BASE_VARIABLE_HPP

#include <utility>

namespace probmodels {
namespace base {

template <typename DescriptorType, typename InstanceType>
struct variable {

    //Type definitions
    typedef DescriptorType descriptor;
    typedef InstanceType instance;

    //A variable must have a non-empty descritor
    variable() = delete;

    //Copy/move Constructors
    variable(const variable& v) = default;
    variable(variable&& v) = default;

    //Initializing from varible descriptor
    variable(const descriptor& descript) : _desc(descript) { }
    variable(descriptor&& descript) : _desc(std::move(descript)) { }

    //Conversor to descriptor type
    operator const descriptor&() const {return _desc;}

private:
    DescriptorType _desc;
};

}

}


#endif // VARIABLE_HPP
