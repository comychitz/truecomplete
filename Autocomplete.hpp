#ifndef _AUTOCOMPLETE_H_
#define _AUTOCOMPLETE_H_

#include <set>
#include <string>
#include "PrefixTree.hpp"

namespace autocomplete {

  class Completer {

    public:
      Completer();

      ~Completer();

      /**
       * given a prefix string, return a set of the possible completions
       */
      std::set<std::string> complete(const std::string &prefix);

    private:
      PrefixTree dict_;
  };

}

#endif
