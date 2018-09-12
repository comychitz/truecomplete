#ifndef _AUTOCOMPLETE_H_
#define _AUTOCOMPLETE_H_

#include <set>
#include <map>
#include <string>
#include <queue>
#include "PrefixTree.hpp"

namespace autocomplete {

  class Word {
    public:
      Word() : rank(~0) { }

      Word(const std::string &w) : rank(~0), word(w) { }

      Word(const std::string &w, int r) : rank(r), word(w) { }

      ~Word() { }

      bool operator<(const Word &b) const {
        return word < b.word;
      }

      unsigned rank;
      std::string word;
  };
  class WordCompare {
    public:
      bool operator()(Word &a, Word&b) {
        return a.rank > b.rank;
      }
  };
  typedef std::priority_queue<Word, std::vector<Word>, WordCompare> WordSet;

  class Completer {

    public:
      Completer();

      ~Completer();

      /**
       * given a prefix string, return a set of the possible completions
       */
      WordSet complete(const std::string &prefix);

    private:
      PrefixTree dict_;
      std::map<std::string,unsigned> ranks_;
  };

}

#endif
