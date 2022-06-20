#include "extract_fullcontext.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " dic-dir user-dic input-str" << std::endl;
    }

    OpenJTalk::ExtractFullcontext extractor(argv[1], argv[2]);
    if (extractor.ready()) {
        for (auto const& s : extractor(argv[3])) {
            std::cout << s << std::endl;
        }
    }

    return 0;
}
