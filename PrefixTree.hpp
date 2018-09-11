#ifndef _PREFIX_TREE_H_
#define _PREFIX_TREE_H_

#include <map>
#include <string>

class Node {

  public:
    Node(char c) : val(c), word(false) { }

    ~Node() { }

    typedef std::map<char,Node*>  NodeMap;

    char val;
    bool word;
    NodeMap children;
};

class PrefixTree {

  public:
    PrefixTree() : root(' ') { }

    ~PrefixTree() { }

    void add(const std::string &word) {
      Node *cur = &root;
      for(long i = 0; i < word.size(); i++) {
        Node::NodeMap::iterator child = cur->children.find(word[i]);
        if(child != cur->children.end()) {
          cur = child->second;
        } else {
          Node *newNode = new Node(word[i]); 
          cur->children[word[i]] = newNode;
          cur = newNode;
        } 
      }
      cur->word = true;
    }

    const Node *getPrefix(const std::string &prefix) const {

      const Node *cur = &root;
      for(long i = 0; i < prefix.size(); i++) {
        Node::NodeMap::const_iterator child = cur->children.find(prefix[i]);
        if(child != cur->children.end()) {
          cur = child->second;
        } else {
          return NULL;
        } 
      }
      return cur;
    }

    Node root;
};

#endif
