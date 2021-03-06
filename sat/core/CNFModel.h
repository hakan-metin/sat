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


#ifndef SAT_CORE_CNFMODEL_H_
#define SAT_CORE_CNFMODEL_H_

#include <algorithm>
#include <memory>
#include <vector>

#include "core/Clause.h"
#include "core/Literal.h"
#include "util/logging.h"

namespace sat {
namespace core {

class CNFModel {
 public:
    CNFModel();
    ~CNFModel();

    void addClause(std::vector<Literal>* literals);

    int64 numberOfVariables() const;
    int64 numberOfClauses() const;

    int64 numberOfUnaryClauses()   const { return _unary_clauses.size();   }
    int64 numberOfBinaryClauses()  const { return _binary_clauses.size();  }
    int64 numberOfTernaryClauses() const { return _ternary_clauses.size(); }
    int64 numberOfOtherClauses()   const { return _clauses.size();         }
    int64 totalNumberOfClauses()   const {
        return _unary_clauses.size() + _binary_clauses.size() +
            _ternary_clauses.size() + _clauses.size();
    }

 private:
    int64 _num_variables;
    std::vector<std::unique_ptr<Clause>> _unary_clauses;
    std::vector<std::unique_ptr<Clause>> _binary_clauses;
    std::vector<std::unique_ptr<Clause>> _ternary_clauses;
    std::vector<std::unique_ptr<Clause>> _clauses;

    DISALLOW_COPY_AND_ASSIGN(CNFModel);
};
}  // namespace core
}  // namespace sat

#endif  // SAT_CORE_CNFMODEL_H_
