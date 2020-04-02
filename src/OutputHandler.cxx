#include "TFileWalker/OutputHandler.h"

namespace TFileWalker {
  OutputHandler::OutputHandler(
      const std::string& start, const std::string& mode)
    : m_fileHandler(start, mode)
  {}

  Target* OutputHandler::find(const Path& target) {
    auto itr = m_targets.find(target);
    if (itr == m_targets.end() )
      return nullptr;
    else
      return itr->second.get();
  }

  const Target* OutputHandler::find(const Path& target) const {
    auto itr = m_targets.find(target);
    if (itr == m_targets.end() )
      return nullptr;
    else
      return itr->second.get();
  }

  void OutputHandler::add(const Path& target, std::unique_ptr<Target> value) {
    m_targets[target] = std::move(value);
  }

  void OutputHandler::write()
  {
    for (auto& p : m_targets)
      p.second->write();
  }
} //> end namespace
