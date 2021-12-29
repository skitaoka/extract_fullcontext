#include "extract_fullcontext.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " dic-path input-str" << std::endl;
    }

    OpenJTalk::ExtractFullcontext extractor(argv[1]);
    for (auto const& s : extractor(argv[2])) {
        std::cout << s << std::endl;
    }

    return 0;
}
