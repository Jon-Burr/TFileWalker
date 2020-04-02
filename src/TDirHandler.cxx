#include "TFileWalker/TDirHandler.h"
#include <stdexcept>

namespace TFileWalker {
  TDirHandler::TDirHandler(
      const Path& path,
      TDirectory& dir,
      std::shared_ptr<const TDirHandler> parent) :
    m_path(path),
    m_dir(&dir),
    m_parent(parent)
  {}

  TDirHandler::~TDirHandler()
  {
    directory()->Close();
  }

  std::shared_ptr<const TDirHandler> TDirHandler::getSubDir(
      const std::string& name,
      bool allowMissing) const
  {
    if (name.empty() )
      return shared_from_this();
    std::size_t pos = name.find("/");
    TDirectory* subdir = m_dir->GetDirectory(name.substr(0, pos).c_str() );
    if (!subdir) {
      if (allowMissing)
        return nullptr;
      else
        throw std::out_of_range(
            "No subdirectory '" + name + "' in " + path().fullName());
    }
    auto tdir = std::make_shared<TDirHandler>(
        path().getPath(name.substr(0, pos) ), *subdir, shared_from_this() );
    if (pos == std::string::npos)
      // There was no / to further split the directory
      return tdir;
    else
      return tdir->getSubDir(name.substr(pos+1), allowMissing);
  }

  std::shared_ptr<TDirHandler> TDirHandler::getSubDir(
      const std::string& name,
      bool allowMissing)
  {
    auto constSubDir = (const_cast<TDirHandler*>(this))->getSubDir(
        name, allowMissing);
    return std::const_pointer_cast<TDirHandler>(constSubDir);
  }

  std::shared_ptr<TDirHandler> TDirHandler::getMkDir(const std::string& name)
  {
    if (name.empty() )
      return shared_from_this();
    std::size_t pos = name.find('/');
    std::string dirName = name.substr(0, pos);
    std::shared_ptr<TDirHandler> next = getSubDir(dirName, true);
    if (!next) {
      TDirectory* tdir = directory()->mkdir(dirName.c_str() );
      if (!tdir)
        throw std::runtime_error(
            "Failed to create directory " + path().getPath(dirName).fullName() );
      next = std::make_shared<TDirHandler>(
          path().getPath(dirName), *tdir, shared_from_this() );
    }
    if (pos == std::string::npos)
      // There was no / to further split the directory
      return next;
    else
      return next->getMkDir(name.substr(pos+1) );
  }

} //> end namespace TFileWalker
