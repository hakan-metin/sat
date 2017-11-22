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

#include <iostream>

#include "core/CNFReader.h"
#include "core/CNFModel.h"

int main() {
    std::cout << "Hello" << std::endl;
    std::string cnf_filename("/data/hmetin/cnfs/hole/hole005.cnf");
    sat::core::CNFModel model;
    sat::io::CNFReader reader;

    reader.load(cnf_filename, &model);


    return 0;
}
