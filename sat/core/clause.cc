# include "core/clause.h"

namespace sat {
namespace core {

// static
Clause* Clause::create(const std::vector<Literal>& literals,
                       bool is_redundant) {
    CHECK_GE(literals.size(), 2);

    Clause * clause = reinterpret_cast<Clause*>(
        ::operator new(sizeof(Clause) + literals.size() * sizeof(Literal)));

    clause->_size  = literals.size();
    for (unsigned int i = 0; i < literals.size(); i++) {
        clause->_literals[i] = literals[i];
    }

    clause->$_is_redundant = is_redundant;

    return clause;
}

}  // namespace core
}  // namespace sat
