#include "TFileWalker/RegexRule.h"
#include "TFileWalker/HistoTarget.h"

namespace TFileWalker {
  RegexRule::RegexRule(
      const boost::regex& pattern,
      const std::string& target,
      bool useFName) :
    m_pattern(pattern),
    m_targetFmt(target),
    m_useFName(useFName)
  {}

  RegexRule::RegexRule(
      const std::string& pattern,
      const std::string& target,
      bool useFName) :
    RegexRule(boost::regex(pattern), target, useFName)
  {}

  RegexRule::~RegexRule() {}

  bool RegexRule::useFile(const std::string& fileName) const
  {
    return !m_useFName || boost::regex_match(
        fileName, m_pattern, boost::match_default | boost::match_partial);
  }

  bool RegexRule::useDir(const Path& path) const 
  {
    // Use a partial match which tells us if the start of the pattern is matched
    return boost::regex_match(
        (m_useFName ? path : path.internalPath()).fullName(),
        m_pattern, boost::match_default | boost::match_partial);
  }

  Rule::FoundObject RegexRule::read(TKey& key, const Path& path) const
  {
    Path usedPath = m_useFName ? path : path.internalPath();
    boost::smatch results;
    if (boost::regex_match(usedPath.fullName(), results, m_pattern) )
      return {
        key.ReadObj(),
        path,
        m_targetFmt.empty() ? usedPath : Path(results.format(m_targetFmt))};
    else
      return {};
  }

  std::unique_ptr<RegexRule> RegexRule::parse(
      const std::string& line, bool useFName)
  {
    // The pattern for configuration strings
    // Matches an input pattern (consisting of any character but whitespace)
    // followed optionally by an arrow -> and then an output format.
    // Any capture groups in the input pattern can be referenced in the output
    // format (e.g. with $1 for the first group)
    const static boost::regex pattern(R"(\s*([^\s]+)(?:\s*->\s*([^\s]+))?\s*)");
    boost::smatch results;
    if (boost::regex_match(line, results, pattern) )
      return std::make_unique<RegexRule>(results.str(1), results.str(2), useFName);
    else
      return nullptr;
  }

  std::unique_ptr<Target> RegexRule::create(
      const FoundObject& found, FileHandler& output) const
  {
    const TH1* h = dynamic_cast<TH1*>(found.object);
    if (h)
      return std::make_unique<HistoTarget>(found.outputPath, output.getMkDir(found.outputPath), h);
    else
      throw std::invalid_argument(
          found.inputPath.fullName() + " is of unhandled class " + found.object->ClassName() );
    return nullptr;
  }
} //> end namespace TFileWalker
