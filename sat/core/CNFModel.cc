#include "core/CNFModel.h"

namespace sat {
namespace core {

CNFModel::CNFModel() {
}

CNFModel::~CNFModel() {
}

void CNFModel::addClause(const std::vector<Literal>& literals) {
    CHECK_GT(literals.size(), 0);

    std::unique_ptr<Clause> clause
        (Clause::create(literals, /* is_redundant= */ false));

    switch (literals.size()) {
    case 1:  _unary_clauses.emplace_back(clause.release());   break;
    case 2:  _binary_clauses.emplace_back(clause.release());  break;
    case 3:  _ternary_clauses.emplace_back(clause.release()); break;
    default: _clauses.emplace_back(clause.release());         break;
    }
}

}  // namespace core
}  // namespace sat
