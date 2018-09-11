#include "Autocomplete.hpp"
#include "PrefixTree.hpp"
#include <iostream>
#include <fstream>

static PrefixTree words_;

namespace autocomplete {

  static bool readDict(const std::string &file) {
    std::ifstream f(file.c_str());
    if(!f.good()) {
      return false;
    }
    std::string line;
    while(std::getline(f, line)) {
      words_.add(line);
    }
    return true;
  }

  static void complete_(const std::string &prefix, 
                        const Node *node, 
                        std::set<std::string> &out) {
    if(node->word) {
      out.insert(prefix);
    }
    for(Node::NodeMap::const_iterator child = node->children.begin(); 
        child != node->children.end(); ++child) {
      std::string tmp = prefix + child->second->val;
      complete_(tmp, child->second, out);
    }
  }

  std::set<std::string> complete(const std::string &prefix) {

    std::set<std::string> ret;
    if(words_.root.children.empty()) {
      const std::string &dictFile = "./dict/words.txt";
      if(!readDict(dictFile)) {
        std::cout << "ERR> Failed to read dictionary file: " 
                  << dictFile << std::endl;
        return ret;
      }
    }

    // get raw listing of possibilities
    const Node *node = words_.getPrefix(prefix); 
    complete_(prefix, node, ret);
    return ret;
  }

}

