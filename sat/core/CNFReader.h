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


#ifndef SAT_CORE_CNFREADER_H_
#define SAT_CORE_CNFREADER_H_

#include <vector>
#include <string>

#include "core/CNFModel.h"
#include "core/Literal.h"
#include "core/StreamBuffer.h"
#include "util/logging.h"

namespace sat {
namespace io {

class CNFReader {
 public:
    CNFReader();
    ~CNFReader();

    bool load(const std::string &filename, sat::core::CNFModel *model);

 private:
    DISALLOW_COPY_AND_ASSIGN(CNFReader);
};
}  // namespace io
}  // namespace sat

#endif  // SAT_CORE_CNFREADER_H_
