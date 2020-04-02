#ifndef TFileWalker_RegexRule_H
#define TFileWalker_RegexRule_H

#include "TFileWalker/Rule.h"
#include <boost/regex.hpp>
#include <memory>

namespace TFileWalker {
  class RegexRule : public Rule {
    public:
      RegexRule(
          const std::string& pattern,
          const std::string& target="",
          bool useFName=true);

      static std::unique_ptr<RegexRule> parse(
          const std::string& line, bool useFName=true);

      ~RegexRule() override;

      bool useFile(const std::string& fileName) const override;

      bool useDir(const Path& path) const override;

      FoundObject read(TKey& key, const Path& path) const override;

      std::unique_ptr<Target> create(
          const FoundObject& obj, FileHandler& output) const override;

    private:
      std::string m_patternStr;
      boost::regex m_pattern;
      std::string m_targetFmt;
      bool m_useFName;

  }; //> end class RegexRule
} //> end namespace TFileWalker

#endif //> !TFileWalker_RegexRule_H
