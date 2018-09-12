#include "Autocomplete.cpp"
#include <iostream>

int main( int argc, const char *argv[] )
{

  autocomplete::Completer completer;

  while(true) {

    std::string prefix;
    std::cout << "Enter a prefix: ";
    std::cin >> prefix;

    autocomplete::WordSet possibilities = completer.complete(prefix);
    int i = 0;
    while(!possibilities.empty() && i < 10) {
      const autocomplete::Word &w = possibilities.top(); 
      std::cout << w.word << std::endl;
      possibilities.pop();
      i++;
    }
    std::cout << std::endl;
  }
  
  return 0;
}
