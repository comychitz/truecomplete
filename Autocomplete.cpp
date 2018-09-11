#include "Autocomplete.hpp"
#include "PrefixTree.hpp"
#include <iostream>
#include <fstream>

namespace autocomplete {

  static bool readDict(const std::string &file,
                       PrefixTree &words) {
    std::ifstream f(file.c_str());
    if(!f.good()) {
      return false;
    }
    std::string line;
    while(std::getline(f, line)) {
      words.add(line);
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

  Completer::Completer() {
    const std::string &dictFile = "./dict/words.txt";
    if(!readDict(dictFile, dict_)) {
      std::cout << "ERR> Failed to read dictionary file: " 
                << dictFile << std::endl;
    }
  }

  Completer::~Completer() { }

  std::set<std::string> Completer::complete(const std::string &prefix) { 

    // get raw listing of possibilities
    std::set<std::string> ret;
    const Node *node = dict_.getPrefix(prefix); 
    if(node) {
      complete_(prefix, node, ret);
    }
    return ret;
  }

}

