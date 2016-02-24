#ifndef NODE_HPP
#define NODE_HPP

//!< Node in the DFA graph representing a point reached by following a
// path of gaps between pulses.

#include "find_tags_common.hpp"
#include "Tag.hpp"
#include "Set.hpp"

class Node {

  friend class Graph;
  friend class Tag_Finder;

  typedef std::map < Gap, Node * > Edges;

protected:
  Set * s;  //!< set of tag phases at this node
  Edges e;  //!< edges to other nodes
  int useCount; //!< number of nodes linking to this one
  int label; //!< unique label for this node, during run
  
  bool _seen; //!< has this node been visited during an algorithm operating on the graph?

  static int _numNodes;  //!< number of allocated nodes not yet deleted
  static int maxLabel; //!< max label value
  static Node * _empty; //!< pointer to unique node representing empty tag phase set

  void ctorCommon(); //!< common ctor code

public:

  bool is_unique(); //!< true if only a single tag ID (possibly in multiple phases) is represented here
  int stamp; //!< when running a recursive algorithm, this records the "stamp" of the current run.  Nodes receiver
  // the stamp the first time they are touched in a given run of the algorithm.  This is cheaper than keeping a bool at each
  //node, and resetting across all nodes at the start of each recursive algorithm, except when the
  // stamp value has wrapped.
  
  Gap get_max_age();  //!< maximum gap value for which there's an edge to another node

  Phase get_phase(); //!< return the phase for the (presumed unique) tag int his set
  Tag * get_tag(); //!< return the (presumed unique) tag in the set for this node

  static void init(); //!< initialize static class members

  Node();  //!< ctor
  Node(const Node *n); //!< pointer copy ctor

  void link(); //!< indicate a link into node is added
  bool unlink();//!< indicate a link into node is removed
  void drop(); //!< remove this node 
  Node * advance (Gap dt); //!< move to the next node, given a gap

  static Node * empty(); //!< return unique node for empty set
  static int numNodes(); //!< return number of nodes allocated but not deleted
  
  void dump(bool skipEdges=false);
};

#endif // NODE_HPP

