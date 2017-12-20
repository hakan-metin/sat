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


#include "core/CNFReader.h"

namespace sat {
namespace io {

CNFReader::CNFReader() {
}

CNFReader::~CNFReader() {
}


bool CNFReader::load(const std::string &filename, sat::core::CNFModel *model) {
    StreamBuffer in(filename);
    unsigned int expected_num_vars = 0, expected_num_clauses = 0;
    int read_int;

    std::vector<sat::core::Literal> literals;

    if (!in.isValid())
        LOG(FATAL) << in.errorMessage() << std::endl;

    while (*in != '\0') {
        if (*in == 'c') {
            in.skipLine();
        } else if (*in == 'p') {
            ++in; assert(*in == ' ');
            ++in; assert(*in == 'c');
            ++in; assert(*in == 'n');
            ++in; assert(*in == 'f');
            ++in;

            expected_num_vars = in.readInt();
            if (!in.isValid())
                LOG(FATAL) << in.errorMessage() << std::endl;

            expected_num_clauses = in.readInt();
            if (!in.isValid())
                LOG(FATAL) << in.errorMessage() << std::endl;
            in.skipLine();
        } else {
            literals.clear();
            do {
                read_int = in.readInt();
                if (!in.isValid())
                    LOG(FATAL) << in.errorMessage() << std::endl;
                if (read_int != 0) {
                    sat::core::Literal lit(read_int);
                    literals.push_back(lit);
                }
            } while (read_int != 0);
            model->addClause(&literals);
            in.skipLine();
        }
        in.skipWhiteSpaces();
    }

    if (model->numberOfVariables() != expected_num_vars)
        LOG(FATAL) << "Expected " << expected_num_vars << " variables: found: "
                   <<  model->numberOfVariables();

    if (model->numberOfClauses() != expected_num_clauses)
        LOG(FATAL) << "Expected " << expected_num_clauses << " clauses: found: "
                   <<  model->numberOfClauses();

    return true;
}

}  // namespace io
}  // namespace sat
