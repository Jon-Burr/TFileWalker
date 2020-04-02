#include "TFileWalker/Rule.h"

namespace TFileWalker {
  void Rule::mergeTo(
      TKey& key, const Path& path, OutputHandler& output) const
  {
    FoundObject found = read(key, path);
    if (!found)
      return;
    Target* target = output.find(found.outputPath);
    if (target)
      target->merge(found.object);
    else
      output.add(
          found.outputPath, std::move(create(found, output.fileHandler() ) ) );
  }
} //> end namespace TFileWalker
