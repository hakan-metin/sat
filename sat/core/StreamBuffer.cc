#include "core/StreamBuffer.h"
#include "util/logging.h"

namespace sat {
namespace io {

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
    if (c == '-') {
        negative = true;
        ++(*this);
    } else if (c == '+') {
        negative = false;
        ++(*this);
    }

    while ((c = read()) != '\0' &&  c >= '0' && c <= '9') {
        value = (value * 10) + (_buffer[_index] - '0');
        ++(*this);
    }

    if (!std::isspace(c) && c != '\0') {
        _error = ERROR_PARSE_INT;
        return 0;
    }

    return negative ? -value : value;
}

void StreamBuffer::skipWhiteSpaces() {
    unsigned char c;

    while ((c = read()) != '\0' && std::isspace(c)) {
        _index++;
    }
}

void StreamBuffer::skipLine() {
    unsigned char c;

    while ((c = read()) != '\0' && c != '\n') {
        _index++;
    }
    ++(*this);
}


int StreamBuffer::operator*() {
    return static_cast<int>(read());
}

void StreamBuffer::operator++() {
    _index++;
    read();
}

unsigned char StreamBuffer::read() {
    if (_index >= _size) {
        _size = gzread(_in, _buffer, sizeof(_buffer));
        _index = 0;
    }
    return (_index >= _size) ? '\0' : _buffer[_index];
}


bool StreamBuffer::isValid() const {
    return _error == SUCCESS;
}

StreamBufferError StreamBuffer::error() const {
    return _error;

    // switch(_error) {
    // case SUCCESS: return std::string("Success");
    // case CANNOT_OPEN_FILE: return std::string("Cannot open file ");
    // case NUM_VARS_MISMATCH: return std::string("Header num vars mismatch");
    // case NUM_CLAUSES_MISMATCH: return std::string("Header num clause mismatch");
    // case MALFORMED_CLAUSE: return std::string("Malformed clause");
    // }
    // return std::string("Unknown error");
}

}  // namespace io
}  // namespace sat
