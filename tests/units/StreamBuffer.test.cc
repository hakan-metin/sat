
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
    ++stream; // ' '
    ++stream; // ' '
    ASSERT_EQ(*stream, 'c'); ++stream;
    ASSERT_EQ(*stream, 'n'); ++stream;
    ASSERT_EQ(*stream, 'f'); ++stream;
    ASSERT_EQ(*stream, ' '); ++stream;
    ASSERT_EQ(*stream, '3'); ++stream;
    ASSERT_EQ(*stream, ' '); ++stream;
    ASSERT_EQ(*stream, '1'); ++stream;
    ASSERT_EQ(*stream, '\n'); ++stream;
}

TEST(StreamBuffer, skip_whitespaces) {
    StreamBuffer stream("tests/resources/one.cnf");

    stream.skipWhiteSpaces();
    ASSERT_EQ(*stream, 'p'); ++stream;
    stream.skipWhiteSpaces();
    ASSERT_EQ(*stream, 'c');
}

TEST(StreamBuffer, skip_line) {
    StreamBuffer stream("tests/resources/one.cnf");

    ASSERT_EQ(*stream, 'p');
    stream.skipLine();
    ASSERT_EQ(*stream, '1');

    stream.skipLine();
    stream.skipLine();
    stream.skipLine();

    ASSERT_EQ(*stream, '\0');
}

TEST(StreamBuffer, read_int) {
    int value;
    StreamBuffer stream("tests/resources/one.cnf");

    stream.skipLine();
    ASSERT_EQ(stream.error(), SUCCESS);

    value = stream.readInt();
    ASSERT_EQ(stream.error(), SUCCESS);
    ASSERT_EQ(value, 1);
    ASSERT_EQ(*stream, ' '); ++stream;

    value = stream.readInt();
    ASSERT_EQ(stream.error(), SUCCESS);
    ASSERT_EQ(value, -2);
    ASSERT_EQ(*stream, ' '); ++stream;

    value = stream.readInt();
    ASSERT_EQ(stream.error(), SUCCESS);
    ASSERT_EQ(value, 3);
    ASSERT_EQ(*stream, ' '); ++stream;
}

TEST(StreamBuffer, read_int_error) {
    int value;
    StreamBuffer stream("tests/resources/one.cnf");

    value = stream.readInt();
    ASSERT_EQ(stream.error(), ERROR_PARSE_INT);
    ASSERT_EQ(value, 0);
}


}  // namespace io
}  // namespace core
