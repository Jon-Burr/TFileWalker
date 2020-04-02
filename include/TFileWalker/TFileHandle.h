#ifndef TFileWalker_TFileHandle_H
#define TFileWalker_TFileHandle_H

#include "TFileWalker/TDirHandle.h"
#include <memory>

namespace TFileWalker {
  class TFileHandle : public TDirHandle {
    public:
      /**
       * @brief Create the handle 
       * @param name the name of the file
       * @param file The file pointer, not allowed to be null
       */
      TFileHandle(const std::string& name, std::unique_ptr<TFile> file);
      ~TFileHandle();
    protected:
      std::unique_ptr<TFile> m_file;
  }; //> end class TFileHandle
} //> end namespace TFileWalker

#endif //> !TFileWalker_TFileHandle_H
