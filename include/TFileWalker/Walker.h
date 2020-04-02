#ifndef TFileWalker_Walker_H
#define TFileWalker_Walker_H

#include "TFileWalker/Rule.h"
#include "TFileWalker/FileHandler.h"
#include "TFileWalker/OutputHandler.h"
#include "TFileWalker/TDirHandler.h"
#include <vector>
#include <memory>

namespace TFileWalker {
  class Walker {
    public:
      Walker(
          std::vector<std::unique_ptr<Rule>> rules,
          OutputHandler&& output);

      /// Walk through an input file
      void walk(FileHandler& input, const std::string& fileName);

      /// Walk through an input directory with the specified rules
      void walk(
          std::shared_ptr<const TDirHandler> input,
          const std::vector<Rule*>& rules);

      OutputHandler& outputHandler() { return m_output; }
      const OutputHandler& outputHandler() const { return m_output; }
    private:
      std::vector<std::unique_ptr<Rule>> m_rules;
      OutputHandler m_output;
  }; //> end class Walker
} //> end namespace TFileWalker

#endif //> !TFileWalker_Walker_H
