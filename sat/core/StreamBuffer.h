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

#ifndef INCLUDE_SAT_CORE_STREAMBUFFER_H_
#define INCLUDE_SAT_CORE_STREAMBUFFER_H_

#include <zlib.h>

#include <cctype>
#include <string>

static const int kBufferSize = 4096;

namespace sat {
namespace io {

enum StreamBufferError {
    SUCCESS,
    CANNOT_OPEN_FILE,
    ERROR_PARSE_INT
};

class StreamBuffer {
 public:
    explicit StreamBuffer(const std::string& filename);
    explicit StreamBuffer(const char * filename);
    ~StreamBuffer();

    int readInt();
    void skipWhiteSpaces();
    void skipLine();

    int operator*();
    void operator++();

    bool isValid() const;
    StreamBufferError error() const;
    std::string errorMessage() const;

 private:
    const std::string _filename;
    gzFile _in;
    unsigned char _buffer[kBufferSize];
    unsigned int _index;
    unsigned int _size;
    StreamBufferError _error;

    unsigned char read();
};

}  // namespace io
}  // namespace sat


#endif  // INCLUDE_SAT_CORE_STREAMBUFFER_H_
