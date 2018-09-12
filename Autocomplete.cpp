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

  static bool readRanks(const std::string &file,
                        std::map<std::string,unsigned> ranks) {
    std::ifstream f(file.c_str());
    if(!f.good()) {
      return false;
    }
    unsigned count = 0;
    std::string line;
    while(std::getline(f, line)) {
      ranks[line] = count++;
    }
    return true;
  }

  static void complete_(const std::string &prefix, 
                        const Node *node, 
                        const std::map<std::string,unsigned> &ranks,
                        WordSet &out) {
    if(node->word) {
      Word w(prefix);
      std::map<std::string,unsigned>::const_iterator r;
      if((r = ranks.find(prefix)) != ranks.end()) {
        w.rank = r->second;
      }
      out.push(w);
    }
    for(Node::NodeMap::const_iterator child = node->children.begin(); 
        child != node->children.end(); ++child) {
      std::string tmp = prefix + child->second->val;
      complete_(tmp, child->second, ranks, out);
    }
  }

  Completer::Completer() {
    const std::string &dictFile = "./dict/words.txt";
    if(!readDict(dictFile, dict_)) {
      std::cout << "ERR> Failed to read dictionary file: " 
                << dictFile << std::endl;
    }
    const std::string &ranksFile = "./dict/google-10000-english.txt";
    if(!readRanks(ranksFile, ranks_)) {
      std::cout << "ERR> Failed to read ranks file: " 
                << ranksFile << std::endl;
    }
  }

  Completer::~Completer() { }

  WordSet Completer::complete(const std::string &prefix) { 

    // get raw listing of possibilities
    WordSet ret;
    const Node *node = dict_.getPrefix(prefix); 
    if(node) {
      complete_(prefix, node, ranks_, ret);
    }
    return ret;
  }

}

