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

#include "core/Graph.h"

namespace sat {
namespace core {

ListGraph::ListGraph() : BaseGraph() {
}

ListGraph::~ListGraph() {
}


void ListGraph::addNode(NodeIndex node) {
    if (node < _num_nodes) return;
    _num_nodes = node.value() + 1;
    _start.resize(_num_nodes, kNilArc);
}

ArcIndex ListGraph::addArc(NodeIndex tail, NodeIndex head) {
    DCHECK_GE(tail, 0);
    DCHECK_GE(head, 0);

    addNode(tail > head ? tail : head);

    _head.push_back(head);
    _tail.push_back(tail);
    _next.push_back(_start[tail.value()]);
    _start[tail.value()] = _num_arcs;

    return ArcIndex(_num_arcs++);
}

}  // namespace core
}  // namespace sat

/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
