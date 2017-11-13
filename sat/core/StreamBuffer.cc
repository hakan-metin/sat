#include "core/StreamBuffer.h"

namespace sat {
namespace io {

StreamBuffer::StreamBuffer() :
        _in(nullptr),
        _index(0),
        _size(0),
        _error(CANNOT_OPEN_FILE) {
}

StreamBuffer::StreamBuffer(const std::string& filename) :
    StreamBuffer(filename.c_str()) {
}

StreamBuffer::StreamBuffer(const char* filename) :
        _in(nullptr),
        _index(0),
        _size(0),
        _error(SUCCESS) {
    _in = gzopen(filename, "rb");
    if (_in == nullptr)
        _error = CANNOT_OPEN_FILE;
}

StreamBuffer::~StreamBuffer() {
    if (_in != nullptr) {
        gzclose(_in);
    }
}


int StreamBuffer::readInt() {
    bool negative = false;
    int value = 0;

    unsigned char c = read();
    if (c == '-')
        negative = true;

    while ((c = read()) != '\0' &&  c >= '0' && c <= '9')
        value = (value * 10) + (_buffer[_index] - '0');

    if (!std::isspace(c) || c != '\0')
        _error = MALFORMED_CLAUSE;

    return negative ? -value : value;
}

unsigned char StreamBuffer::read() {
    return (_index >= _size) ? '\0' : _buffer[_index];
}


bool StreamBuffer::isValid() const {
    return _error == SUCCESS;
}

std::string StreamBuffer::errorString() const {
    switch(_error) {
    case SUCCESS: return std::string("Success");
    case CANNOT_OPEN_FILE: return std::string("Cannot open file ");
    case NUM_VARS_MISMATCH: return std::string("Header num vars mismatch");
    case NUM_CLAUSES_MISMATCH: return std::string("Header num clause mismatch");
    case MALFORMED_CLAUSE: return std::string("Malformed clause");
    }
    return std::string("Unknown error");
}

}  // namespace io
}  // namespace sat
