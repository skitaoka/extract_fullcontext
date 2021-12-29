#pragma once

#include <cstdio> // for FILE in jpcommon.h

#include "jpcommon.h"
#include "mecab.h"
#include "njd.h"

#include <vector>
#include <string>

namespace OpenJTalk
{
    class ExtractFullcontext
    {
    public:
        ExtractFullcontext(char const* dn_mecab);
        ~ExtractFullcontext();

        std::vector<std::string> operator () (char const* text) const;

    private:
        mutable Mecab mecab_;
        mutable NJD njd_;
        mutable JPCommon jpcommon_;
    };

}
