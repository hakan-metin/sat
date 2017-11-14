
#include <gtest/gtest.h>

#include "core/StreamBuffer.h"


namespace sat {
namespace io {

TEST(StreamBuffer, file_not_exists) {
    StreamBuffer stream("file_not_exists");

    ASSERT_FALSE(stream.isValid());
    ASSERT_EQ(stream.error(), CANNOT_OPEN_FILE);
}

TEST(StreamBuffer, open_file) {
    StreamBuffer stream("tests/resources/one.cnf");

    ASSERT_TRUE(stream.isValid());
    ASSERT_EQ(stream.error(), SUCCESS);
}

TEST(StreamBuffer, operator_star) {
    StreamBuffer stream("tests/resources/one.cnf");

    ASSERT_TRUE(stream.isValid());
    ASSERT_EQ(stream.error(), SUCCESS);

    ASSERT_EQ(*stream, 'p');
}

TEST(StreamBuffer, operator_plusplus) {
    StreamBuffer stream("tests/resources/one.cnf");

    ASSERT_TRUE(stream.isValid());
    ASSERT_EQ(stream.error(), SUCCESS);

    ASSERT_EQ(*stream, 'p'); ++stream;
    ASSERT_EQ(*stream, ' '); ++stream;
    ASSERT_EQ(*stream, 'c'); ++stream;
    ASSERT_EQ(*stream, 'n'); ++stream;
    ASSERT_EQ(*stream, 'f'); ++stream;
    // ASSERT_EQ(*stream, '\n'); ++stream;

}


}  // namespace io
}  // namespace core
