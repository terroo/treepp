#include "tree.hpp"

Tree::Tree(){
  dirs = 0;
  files = 0;
  inner_pointers = { "\u251c\u2500\u2500 ", "\u2502   " };
  final_pointers = { "\u2514\u2500\u2500 ", "    " };
}

void Tree::walk(std::string directory, std::string prefix) {
  std::vector<fs::directory_entry> entries;

  for (const auto &entry : fs::directory_iterator(directory)) {
    if (entry.path().filename().string()[0] != '.') {
      entries.push_back(entry);
    }
  }

  sort(entries.begin(), entries.end(), [](const fs::directory_entry &left, const fs::directory_entry &right) -> bool {
    return left.path().filename() < right.path().filename();
  });


  for (size_t index = 0; index < entries.size(); index++) {
    fs::directory_entry entry = entries[index];
    std::vector<std::string> pointers = index == entries.size() - 1 ? final_pointers : inner_pointers;

    const std::string filetype = fs::path(entry.path().filename().string()).extension().string(); // .md

    std::cout << prefix << pointers[0] << unicode(filetype) << " " << entry.path().filename().string() << '\n';

    if (!entry.is_directory()) {
      files++;
    } else {
      dirs++;
      walk(entry.path(), prefix + pointers[1]);
    }
  }
}

void Tree::summary() {
  std::cout << "\n" << dirs << " directories," << " " << files << " files" << '\n';
}


