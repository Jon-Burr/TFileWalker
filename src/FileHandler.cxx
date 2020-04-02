#include "TFileWalker/FileHandler.h"
#include <boost/filesystem/path.hpp>

namespace TFileWalker {
  FileHandler::FileHandler(const std::string& start, const std::string& mode) :
    m_start(start), m_mode(mode)
  {}

  FileHandler::~FileHandler() {}

  std::shared_ptr<TDirHandler> FileHandler::getFile(
      const std::string& name, bool allowMissing)
  {
    auto itr = m_openFiles.find(name);
    TFile* fp = nullptr;
    if (itr == m_openFiles.end() || !itr->second || !itr->second->IsOpen() ) {
      boost::filesystem::path bpath(name);
      if (!bpath.is_absolute() )
        bpath = boost::filesystem::path(m_start) / bpath;
      fp = TFile::Open(bpath.c_str(), m_mode.c_str() );
      if (fp)
        m_openFiles[name] = std::shared_ptr<TFile>(fp);
    }
    else
      fp = itr->second.get();
    if (!fp) {
      if (allowMissing)
        return nullptr;
      else
        throw std::out_of_range(
            "Cannot open file " + name);
    }
    return std::make_shared<TDirHandler>(
        Path(name, "", ""), *fp, nullptr);
  }

  std::shared_ptr<TDirHandler> FileHandler::getFile(
      const Path& path, bool allowMissing)
  {
    return getFile(path.fileName(), allowMissing);
  }

  std::shared_ptr<TFile> FileHandler::releaseFile(const std::string& name)
  {
    auto itr = m_openFiles.find(name);
    if (itr == m_openFiles.end() )
      return nullptr;
    std::shared_ptr<TFile> result = itr->second;
    m_openFiles.erase(itr);
    return result;
  }

  std::shared_ptr<TDirHandler> FileHandler::getMkDir(const Path& path)
  {
    std::shared_ptr<TDirHandler> file = getFile(path);
    if (!file)
      throw std::runtime_error(
          "Failed to create file " + path.fileName());
    return file->getMkDir(path);
  }
} //> end namespace TFileWalker
