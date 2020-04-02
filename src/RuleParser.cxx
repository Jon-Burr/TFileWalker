#include "TFileWalker/RuleParser.h"
#include "TFileWalker/RegexRule.h"
#include <regex>
#include <stdexcept>
#include <fstream>

namespace TFileWalker {
  std::unique_ptr<Rule> RuleParser::parseLine(
      const std::string& line, bool ruleUseFName)
  {
    // Matches empty lines or ones that begin with a # character
    static std::regex commentPattern(R"(\s*(#.*)?)");
    if (std::regex_match(line, commentPattern) )
      return nullptr;
    std::unique_ptr<Rule> rule;
    rule = RegexRule::parse(line, ruleUseFName);
    if (!rule)
      throw std::invalid_argument(
          "Failed to parse " + line + " as a rule!");
    return rule;
  }

  std::vector<std::unique_ptr<Rule>> RuleParser::parse(
      std::istream& is, bool ruleUseFName)
  {
    std::vector<std::unique_ptr<Rule>> rules;
    std::string line;
    while (std::getline(is, line) ) {
      std::unique_ptr<Rule> rule = parseLine(line, ruleUseFName);
      if (rule)
        rules.push_back(std::move(rule) );
    }
    return std::move(rules);
  }

  std::vector<std::unique_ptr<Rule>> RuleParser::parseFile(
      const std::string& fileName, bool ruleUseFName)
  {
    std::ifstream fin(fileName);
    if (!fin.is_open() )
      throw std::runtime_error(
          "Could not open input rules file " + fileName);
    return parse(fin, ruleUseFName);
  }

} //> end namespace TFileWalker
