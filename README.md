# extract_fullcontext

## download

* http://downloads.sourceforge.net/open-jtalk/open_jtalk-1.11.tar.gz
* http://downloads.sourceforge.net/open-jtalk/open_jtalk_dic_shift_jis-1.11.tar.gz

## mecab-dict-index.exe

```sh
cd open_jtalk-1.11\mecab
nmake -f Makefile.mak
```

```sh
open_jtalk-1.11\mecab\src\mecab-dict-index.exe -d open_jtalk_dic_shift_jis-1.11 -u user.dic -f utf-8 -t shift-jis user.csv
```

## run

```sh
x64\Release\extract_fullcontext.exe open_jtalk_dic_shift_jis-1.11 user.dic ずんだもん
```
