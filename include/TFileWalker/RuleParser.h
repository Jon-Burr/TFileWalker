#ifndef TFileWalker_RuleParser_H
#define TFileWalker_RuleParser_H

#include <string>
#include <istream>
#include <memory>
#include <vector>
#include "TFileWalker/Rule.h"

namespace TFileWalker {
  class RuleParser {
    public:
      static std::unique_ptr<Rule> parseLine(
          const std::string& line, bool ruleUseFName=true);

      static std::vector<std::unique_ptr<Rule>> parse(
          std::istream& is, bool ruleUseFName=true);

      static std::vector<std::unique_ptr<Rule>> parseFile(
          const std::string& fileName, bool ruleUseFName=true);
  }; //> end class RuleParser
} //> end namespace TFileWalker

#endif //> !TFileWalker_RuleParser_H
