
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "core/literal.h"

namespace sat {
namespace core {

TEST(LiteralTest, positive) {
    Literal literal(+1);
    ASSERT_TRUE(literal.isPositive());
    ASSERT_FALSE(literal.isNegative());
}

TEST(LiteralTest, negative) {
    Literal literal(-1);
    ASSERT_FALSE(literal.isPositive());
    ASSERT_TRUE(literal.isNegative());
}

TEST(LiteralTest, signed_value) {
    Literal negative_literal(-2);
    ASSERT_EQ(negative_literal.signedValue(), -2);

    Literal positive_literal(+1);
    ASSERT_EQ(positive_literal.signedValue(), 1);
}

TEST(LiteralTest, negate) {
    Literal negative_literal(-2);
    Literal positive_literal(+2);

    ASSERT_EQ(negative_literal.negated(), positive_literal);
    ASSERT_EQ(positive_literal.negated(), negative_literal);
}

TEST(LiteralTest, error_on_zero) {
    ASSERT_DEATH({ Literal literal(0); }, ".*");
}

}  // namespace core
}  // namespace sat
