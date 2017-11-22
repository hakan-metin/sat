
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "core/Literal.h"
#include "core/Clause.h"

namespace sat {
namespace core {

TEST(ClauseTest, create) {
    std::vector<Literal> literals = { +1, +2, -3 };

    std::unique_ptr<Clause> clause(Clause::create(literals, false));

    ASSERT_EQ(clause->size(), 3);
    ASSERT_FALSE(clause->is_redundant());
}

TEST(ClauseTest, size) {
    std::vector<Literal> literals = { +1, +2, -3, -6 };

    std::unique_ptr<Clause> clause(Clause::create(literals, false));
    ASSERT_EQ(clause->size(), 4);
}

TEST(ClauseTest, is_redundant) {
    std::vector<Literal> literals = { +1, +2, -3, -6 };

    std::unique_ptr<Clause> clause_one(Clause::create(literals, false));
    ASSERT_FALSE(clause_one->is_redundant());

    std::unique_ptr<Clause> clause_two(Clause::create(literals, true));
    ASSERT_TRUE(clause_two->is_redundant());
}

TEST(ClauseTest, error_on_unary) {
    std::vector<Literal> literals = { +1 };
    ASSERT_DEATH(
        std::unique_ptr<Clause> clause(Clause::create(literals, false)), ".*");
}

}  // namespace core
}  // namespace sat
