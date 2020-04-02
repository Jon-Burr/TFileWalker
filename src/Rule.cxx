#include "TFileWalker/Rule.h"
#include <iostream>

namespace TFileWalker {
  void Rule::mergeTo(
      TKey& key, const Path& path, OutputHandler& output) const
  {
    FoundObject found = read(key, path);
    if (!found)
      return;
    Target* target = output.find(found.outputPath);
    if (target) {
      target->merge(found.object);
    }
    else {
      std::cout << "Create new target " << found.outputPath.fullName() << std::endl;
      output.add(
          found.outputPath, std::move(create(found, output.fileHandler() ) ) );
    }
  }
} //> end namespace TFileWalker
