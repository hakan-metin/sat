#include "core/CNFModel.h"

namespace sat {
namespace core {

CNFModel::CNFModel() {
}

CNFModel::~CNFModel() {
}

void CNFModel::addClause(std::vector<Literal>* literals) {
    CHECK_GT(literals->size(), static_cast<unsigned int>(0));

    /* Remove duplicate literals in clause */
    std::sort(literals->begin(), literals->end());
    auto last_element_it = std::unique(literals->begin(), literals->end());
    literals->erase(last_element_it, literals->end());

    std::unique_ptr<Clause> clause
        (Clause::create(*literals, /* is_redundant= */ false));

    switch (clause->size()) {
    case 1:  _unary_clauses.emplace_back(clause.release());   break;
    case 2:  _binary_clauses.emplace_back(clause.release());  break;
    case 3:  _ternary_clauses.emplace_back(clause.release()); break;
    default: _clauses.emplace_back(clause.release());         break;
    }
}

}  // namespace core
}  // namespace sat
