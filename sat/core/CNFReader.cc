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
            ++in; assert(*in == ' ');

            expected_num_vars = in.readInt();
            if (!in.isValid())
                LOG(FATAL) << in.errorMessage() << std::endl;

            expected_num_clauses = in.readInt();
            if (!in.isValid())
                LOG(FATAL) << in.errorMessage() << std::endl;
        } else {
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
            literals.clear();
        }
    }

    return true;
}

}  // namespace io
}  // namespace sat
