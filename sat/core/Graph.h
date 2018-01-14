// Copyright 2017 Hakan Metin
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SAT_CORE_GRAPH_H_
#define SAT_CORE_GRAPH_H_

#include <limits>
#include <vector>

#include "util/int_type.h"
#include "util/logging.h"

namespace sat {
namespace core {

DEFINE_INT_TYPE(NodeIndex, int);

DEFINE_INT_TYPE(ArcIndex, int);

static const ArcIndex  kNilArc(std::numeric_limits<int>::max());
static const NodeIndex kNilNode(std::numeric_limits<int>::max());

class BaseGraph {
 public:
    BaseGraph() :
        _num_nodes(0),
        _num_arcs(0) {}
    virtual ~BaseGraph() {}


 protected:
    unsigned int _num_nodes;
    unsigned int _num_arcs;

};

class ListGraph : public BaseGraph {
 public:
    ListGraph();
    ~ListGraph();

    void addNode(NodeIndex node);
    ArcIndex addArc(NodeIndex from, NodeIndex to);

    NodeIndex head(ArcIndex arc);
    NodeIndex tail(ArcIndex arc);

 private:
    std::vector<ArcIndex> _start;
    std::vector<ArcIndex> _next;
    std::vector<NodeIndex> _head;
    std::vector<NodeIndex> _tail;
    DISALLOW_COPY_AND_ASSIGN(ListGraph);
};

}  // namespace core
}  // namespace sat

#endif  // SAT_CORE_GRAPH_H_
/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
