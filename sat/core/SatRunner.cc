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

#include <gflags/gflags.h>

#include <iostream>

#include "core/CNFReader.h"
#include "core/CNFModel.h"
#include "util/logging.h"
#include "core/Graph.h"

DEFINE_string(input, "", "Required: input cnf file.");

DEFINE_bool(print_model, false,
            "If true and the problem is satisfiable"
            " print solution to stdout in cnf form.");


static const char kUsage[] =
    "Usage: see flags.\n"
    "This program solves a given CNF sat problem in cnf format.";

int main(int argc, char *argv[]) {
    ::google::InitGoogleLogging(argv[0]);
    gflags::SetUsageMessage(kUsage);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "Hello" << std::endl;
    sat::core::CNFModel model;
    sat::io::CNFReader reader;

    reader.load(FLAGS_input, &model);


    return 0;
}
