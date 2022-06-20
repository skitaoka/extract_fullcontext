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
        ExtractFullcontext(char const* dn_mecab, char const* user_dic = nullptr);
        ~ExtractFullcontext();

        bool ready() const { return ready_; }

        std::vector<std::string> operator () (char const* text) const;

    private:
        int load(char const* dn_mecab, char const* user_dict) const;

    private:
        bool ready_;
        mutable Mecab mecab_;
        mutable NJD njd_;
        mutable JPCommon jpcommon_;
    };

}
