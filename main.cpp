#include "Autocomplete.cpp"
#include <iostream>

int main( int argc, const char *argv[] )
{

  autocomplete::Completer completer;

  while(true) {

    std::string prefix;
    std::cout << "Enter a prefix: ";
    std::cin >> prefix;

    std::set<std::string> possibilities = completer.complete(prefix);
    int i = 0;
    for(std::set<std::string>::iterator poss = possibilities.begin(); 
        poss != possibilities.end() && i < 10; ++poss) {
      std::cout << *poss << std::endl;
      i++;
    }
    std::cout << std::endl;
  }
  
  return 0;
}
