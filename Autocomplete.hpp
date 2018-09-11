#ifndef _AUTOCOMPLETE_H_
#define _AUTOCOMPLETE_H_

#include <set>
#include <string>

namespace autocomplete {

  /**
  * given a prefix string, return a set of the possible completions
  */
  std::set<std::string> complete(const std::string &prefix);

}

#endif
