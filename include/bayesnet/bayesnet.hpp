//bayesnet.hpp
//explanation
//discalaimer

#ifndef _PROBMODELS_BAYESNET_BAYESNET_HPP_
#define _PROBMODELS_BAYESNET_BAYESNET_HPP_

#include "base/symbolic_property.hpp"
#include "graph/graph.hpp"

namespace probmodels {
namespace bayesnet {

namespace detail {
//TODO: define BNProperty concept
template <typename BNProperty>
class bayesnet_base {


private:
    graph::directed_graph<BNProperty> _net;
};

//TODO: define Multi-variate probability distribution concept
template <typename MultiVarProbDist>
struct simple_bn_property {
    typedef MultiVarProbDist distribution_type;
};

template <typename MultiVarProbDist, std::size_t SymbolLen = 7>
struct symbolic_bn_property : base::SymbolicProperty<SymbolLen, MultiVarProbDist> {
    typedef MultiVarProbDist distribution_type;
};

}

template <typename MultiVarProbDist>
using bayesnet = detail::bayesnet_base<detail::simple_bn_property<MultiVarProbDist> >;

template <typename MultiVarProbDist>
using symbolic_bayesnet = detail::bayesnet_base<detail::symbolic_bn_property<MultiVarProbDist> >;

}
}

#endif
