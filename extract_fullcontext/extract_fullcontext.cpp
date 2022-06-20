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

#include <memory>

namespace OpenJTalk
{
    ExtractFullcontext::ExtractFullcontext(char const* dn_mecab, char const* user_dic)
        : ready_(true)
    {
        Mecab_initialize(&mecab_);
        if (user_dic) {
            if (this->load(dn_mecab, user_dic)) {
                ready_ = false;
            }
        }
        else {
            if (!Mecab_load(&mecab_, dn_mecab)) {
                ready_ = false;
            }
        }
        NJD_initialize(&njd_);
        JPCommon_initialize(&jpcommon_);
    }

    ExtractFullcontext::~ExtractFullcontext()
    {
        Mecab_clear(&mecab_);
        NJD_clear(&njd_);
        JPCommon_clear(&jpcommon_);
    }

    int ExtractFullcontext::load(char const* dn_mecab, char const* user_dic) const {
        Mecab_clear(&mecab_);

        std::string dicdir(dn_mecab);
        std::string userdic(user_dic);
        // char* argv[] = { "mecab", "-d", dicdir.data(), "-u", userdic.data() }; // C++17
        char* argv[] = { "mecab", "-d", &dicdir[0], "-u", &userdic[0] };
        int argc = std::size(argv);

        std::unique_ptr<MeCab::Model> model(MeCab::createModel(argc, argv));
        if (!model) {
            return 1;
        }

        std::unique_ptr<MeCab::Tagger> tagger(model->createTagger());
        if (!tagger) {
            return 2;
        }

        std::unique_ptr<MeCab::Lattice> lattice(model->createLattice());
        if (!lattice) {
            return 3;
        }

        mecab_.model = model.release();
        mecab_.tagger = tagger.release();
        mecab_.lattice = lattice.release();

        return 0;
    }

    std::vector<std::string> ExtractFullcontext::operator () (char const* text) const
    {
        std::string buff(text);

        text2mecab(&buff[0], text);
        Mecab_analysis(&mecab_, buff.c_str());
#if !defined(NDEBUG)
        Mecab_print(&mecab_);
#endif
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
