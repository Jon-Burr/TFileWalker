#include "TFileWalker/TDirHandle.h"
#include <stdexcept>

namespace TFileWalker {
  TDirHandle::TDirHandle(
      const Path& path,
      TDirectory* dir,
      std::shared_ptr<const TDirHandle> parent) :
    m_path(path),
    m_dir(dir),
    m_parent(parent)
  {
    if (!dir)
      throw std::invalid_argument(
          "Cannot initialise TDirHandle " + path.fullName() + " with nullptr");
  }

  TDirHandle::~TDirHandle()
  {
    if(directory() )
      directory()->Close();
  }

  std::shared_ptr<const TDirHandle> TDirHandle::getSubDir(
      const std::string& name,
      bool allowMissing) const
  {
    if (name.empty() )
      return shared_from_this();
    std::size_t pos = name.find("/");
    std::string dirName = name.substr(0, pos);
    auto itr = m_children.find(dirName);
    if (itr != m_children.end() )
      if (!itr->second.expired() )
        return itr->second.lock();
    TDirectory* subdir = m_dir->GetDirectory(dirName.c_str() );
    if (!subdir) {
      if (allowMissing)
        return nullptr;
      else
        throw std::out_of_range(
            "No subdirectory '" + dirName + "' in " + path().fullName());
    }
    auto tdir = std::make_shared<TDirHandle>(
        path().getPath(dirName), subdir, shared_from_this() );
    m_children[dirName] = tdir;
    if (pos == std::string::npos)
      // There was no / to further split the directory
      return tdir;
    else
      return tdir->getSubDir(name.substr(pos+1), allowMissing);
  }

  std::shared_ptr<TDirHandle> TDirHandle::getSubDir(
      const std::string& name,
      bool allowMissing)
  {
    auto constSubDir = (const_cast<const TDirHandle*>(this))->getSubDir(
        name, allowMissing);
    return std::const_pointer_cast<TDirHandle>(constSubDir);
  }

  std::shared_ptr<TDirHandle> TDirHandle::getMkDir(const std::string& name)
  {
    if (name.empty() )
      return shared_from_this();
    std::size_t pos = name.find('/');
    std::string dirName = name.substr(0, pos);
    std::shared_ptr<TDirHandle> next = getSubDir(dirName, true);
    if (!next) {
      TDirectory* tdir = directory()->mkdir(dirName.c_str() );
      if (!tdir)
        throw std::runtime_error(
            "Failed to create directory " + path().getPath(dirName).fullName() );
      next = std::make_shared<TDirHandle>(
          path().getPath(dirName), tdir, shared_from_this() );
      m_children[dirName] = next;
    }
    if (pos == std::string::npos)
      // There was no / to further split the directory
      return next;
    else
      return next->getMkDir(name.substr(pos+1) );
  }

} //> end namespace TFileWalker
