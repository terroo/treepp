#include "tree.hpp"

int main(int argc, char **argv) {
  Tree tree;
  std::string directory = argc == 1 ? "." : argv[1];

  if(!fs::exists(directory) || !fs::is_directory(directory)){
    std::cerr << "Directory not exists or is not a.\n";
    return EXIT_FAILURE;
  }

  std::cout << "\ufc6e " << directory << '\n';
  tree.walk(directory, "");
  tree.summary();

  return 0;
}
