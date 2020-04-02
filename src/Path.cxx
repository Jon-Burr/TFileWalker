#include "TFileWalker/Path.h"

namespace TFileWalker {
  Path::Path(const std::string& name)
  {
    std::string nameCopy = name;
    std::size_t colonPos = nameCopy.find(":");
    if (colonPos != std::string::npos) {
      m_fileName = name.substr(0, colonPos);
      nameCopy = nameCopy.substr(colonPos+1);
    }
    // Find the last slash
    std::size_t slashPos = nameCopy.rfind("/");
    if (slashPos == std::string::npos) {
      m_dirPath = "";
      m_name = nameCopy;
    }
    else {
      m_dirPath = nameCopy.substr(0, slashPos);
      m_name = nameCopy.substr(slashPos+1);
    }
  }

  Path::Path(
      const std::string& fileName,
      const std::string& dirPath,
      const std::string& name) :
    m_fileName(fileName),
    m_dirPath(dirPath),
    m_name(name)
  {}

  std::string Path::fullName() const
  {
    std::string result;
    if (!fileName().empty() )
      result += fileName() + ":";
    if (!dirPath().empty() )
      result += dirPath() + "/";
    result += name();
    return result;
  }

  Path Path::getPath(const std::string& name) const
  {
    std::string newDirPath = dirPath();
    if (!this->name().empty() ) {
      if (newDirPath.empty() )
        newDirPath = this->name();
      else
        newDirPath += "/" + this->name();
    }
    return Path(fileName(), newDirPath, name);
  }
} //> end namespace TFileWalker
