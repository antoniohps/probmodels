//graph.hpp

#ifndef _PROBMODELS_GRAPH_GRAPH_HPP_
#define _PROBMODELS_GRAPH_GRAPH_HPP_

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/adjacency_matrix.hpp"

namespace probmodels {
namespace graph {

//Selectors dense/sparse, bound/unbound, directed/undirected

//Graph is compatible with boost graph concepts

namespace utils {
template<std::size_t N, typename... T>
    using static_switch = typename std::tuple_element<N, std::tuple<T...> >::type;
}

using DefaultNodeType = boost::no_property;
using DefaultEdgeType = boost::no_property;

//////////////// Generic graph
template < typename NodeType = DefaultNodeType,
           typename EdgeType = DefaultEdgeType,
           bool IsDirected = false,
           bool IsDense = false >
class graph { };

//Dense graph specialization
template<typename NodeType, typename EdgeType, bool IsDirected>
class graph <NodeType, EdgeType, IsDirected, true> :
        public boost::adjacency_matrix <
        utils::static_switch<(int)IsDirected, boost::directedS, boost::undirectedS >,
        NodeType,
        EdgeType >
{ };

//Sparse graph specialization
template<typename NodeType, typename EdgeType, bool IsDirected>
class graph <NodeType, EdgeType, IsDirected, false> :
        public  boost::adjacency_list <
        boost::vecS, // OutEdgeListS: a Sequence or an AssociativeContainer
        boost::vecS, // VertexListS: a Sequence or a RandomAccessContainer
        utils::static_switch<(int)IsDirected, boost::directedS, boost::undirectedS >,
        NodeType,
        EdgeType >
{ };

//Directed graph type definition
template < typename NodeType = DefaultNodeType,
           typename EdgeType = DefaultEdgeType,
           bool IsDense = false >
using directed_graph = graph<NodeType, EdgeType, true, IsDense>;

}
}

#endif
