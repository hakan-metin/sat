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

#ifndef INCLUDE_SAT_CORE_CLAUSE_H_
#define INCLUDE_SAT_CORE_CLAUSE_H_

#include <string>

#include "core/literal.h"
#include "util/logging.h"

namespace sat {
namespace core {

class Clause {
 public:
    static Clause* create(const std::vector<Literal>& literals,
                          bool is_redundant);

    // Non-sized delete because this is a tail-padded class.
    void operator delete(void* p) {
        ::operator delete(p);  // non-sized delete
    }

    // Allows for range based iteration: for (Literal literal : clause) {}.
    const Literal*  begin() const { return &(_literals[0]); }
    const Literal*  end() const { return &(_literals[_size]); }
    Literal* literals() { return &(_literals[0]); }

    int  size()         const { return _size;        }
    bool is_redundant() const { return _is_redundant; }

 private:
    // Packed data, use 32 bits
    bool _is_redundant : 1;
    unsigned int _size : 31;

    // This class store the literals inline, and literals_ mark the starts of
    // the variable length portion.
    Literal _literals[0];

    DISALLOW_COPY_AND_ASSIGN(Clause);
};

}  // namespace core
}  // namespace sat

#endif  // INCLUDE_SAT_CORE_CLAUSE_H_
