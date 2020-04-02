#include "TFileWalker/Walker.h"
#include "TFileWalker/Target.h"

#include <iterator>
#include <algorithm>

namespace TFileWalker {
  Walker::Walker(
      std::vector<std::unique_ptr<Rule>> rules,
      OutputHandler&& output) :
    m_rules(std::move(rules)), m_output(std::move(output) )
  {}

  void Walker::walk(FileHandler& input, const std::string& fileName)
  {
    std::vector<Rule*> rules;
    rules.reserve(m_rules.size() );
    for (std::unique_ptr<Rule>& rule : m_rules)
      if (rule->useFile(fileName) )
        rules.push_back(rule.get() );
    walk(input.getFile(fileName, false), rules);
    input.releaseFile(fileName);
  }

  void Walker::walk(
      std::shared_ptr<const TDirHandler> input,
      const std::vector<Rule*>& rules) {
    if (!input)
      throw std::runtime_error(
          "Walker received invalid handler input " + input->path().fullName() );
    for (TObject* ikey : *input->directory()->GetListOfKeys() ) {
      TKey& key = dynamic_cast<TKey&>(*ikey);
      Path keyPath = input->path().getPath(key.GetName() );
      if (strcmp(key.GetClassName(), "TDirectoryFile") == 0) {
        std::vector<Rule*> dirRules;
        dirRules.reserve(rules.size() );
        std::copy_if(rules.begin(), rules.end(), std::back_inserter(dirRules),
            [keyPath] (Rule* rule) { return rule->useDir(keyPath); });
        if (dirRules.size() > 0)
          walk(input->getSubDir(key.GetName() ), dirRules);
      }
      else {
        for (Rule* rule : rules)
          rule->mergeTo(key, keyPath, m_output);
      }
    }
  }

} //> end namespace TFileWalker
