#ifndef TFileWalker_OutputHandler_H
#define TFileWalker_OutputHandler_H

#include "TFileWalker/Target.h"
#include "TFileWalker/Path.h"
#include "TFileWalker/FileHandler.h"
#include <memory>
#include <map>

namespace TFileWalker {

  class OutputHandler {
    public:
      OutputHandler(
          const std::string& start="", const std::string& mode="READ");
      Target* find(const Path& target);
      const Target* find(const Path& target) const;
      void add(const Path& target, std::unique_ptr<Target> value);
      FileHandler& fileHandler() { return m_fileHandler; }
      const FileHandler& fileHandler() const { return m_fileHandler; }
      void write();
    private:
      std::map<std::string, std::unique_ptr<Target>> m_targets;
      FileHandler m_fileHandler;
  }; //> end class OutputHandler

} //> end namespace TFileWalker

#endif //> !TFileWalker_OutputHandler_H
