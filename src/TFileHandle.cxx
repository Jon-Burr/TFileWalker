#include "TFileWalker/TFileHandle.h"
#include <TFile.h>

namespace TFileWalker {
  TFileHandle::TFileHandle(
      const std::string& name, std::unique_ptr<TFile> file) :
    TDirHandle(Path(name, "", ""), file.get(), nullptr),
    m_file(std::move(file) )
  {}

  TFileHandle::~TFileHandle() { m_dir = nullptr; }
    
} //> end namespace TFileWalker
