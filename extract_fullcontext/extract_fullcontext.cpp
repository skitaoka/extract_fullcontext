#include "extract_fullcontext.hpp"

#include "mecab2njd.h"
#include "njd_set_accent_phrase.h"
#include "njd_set_accent_type.h"
#include "njd_set_digit.h"
#include "njd_set_long_vowel.h"
#include "njd_set_pronunciation.h"
#include "njd_set_unvoiced_vowel.h"
#include "njd2jpcommon.h"
#include "text2mecab.h"


namespace OpenJTalk
{
    ExtractFullcontext::ExtractFullcontext(char const* dn_mecab)
    {
        Mecab_initialize(&mecab_);
        Mecab_load(&mecab_, dn_mecab);
        NJD_initialize(&njd_);
        JPCommon_initialize(&jpcommon_);
    }

    ExtractFullcontext::~ExtractFullcontext()
    {
        Mecab_clear(&mecab_);
        NJD_clear(&njd_);
        JPCommon_clear(&jpcommon_);
    }

    std::vector<std::string> ExtractFullcontext::operator () (char const* text) const
    {
        char buff[8192];

        text2mecab(buff, text);
        Mecab_analysis(&mecab_, buff);
        mecab2njd(&njd_, Mecab_get_feature(&mecab_), Mecab_get_size(&mecab_));
        njd_set_pronunciation(&njd_);
        njd_set_digit(&njd_);
        njd_set_accent_phrase(&njd_);
        njd_set_accent_type(&njd_);
        njd_set_unvoiced_vowel(&njd_);
        njd_set_long_vowel(&njd_);
        njd2jpcommon(&jpcommon_, &njd_);
        JPCommon_make_label(&jpcommon_);

        int const label_size = JPCommon_get_label_size(&jpcommon_);
        char** labels = JPCommon_get_label_feature(&jpcommon_);
        std::vector<std::string> fullcontext(labels, labels + label_size);

        JPCommon_refresh(&jpcommon_);
        NJD_refresh(&njd_);
        Mecab_refresh(&mecab_);

        return fullcontext;
    }
}
