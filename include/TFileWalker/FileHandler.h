#ifndef TFileWalker_FileHandler_H
#define TFileWalker_FileHandler_H

#include "TFileWalker/Path.h"
#include "TFileWalker/TDirHandler.h"
#include <TFile.h>
#include <memory>

namespace TFileWalker {
  /**
   * @brief Class for interacting with ROOT files on disk
   */
  class FileHandler {
    public:
      /**
       * @brief Create a FileHandler
       * @param start All paths will be taken as relative to this. If it refers
       * to a ROOT file then only internal file paths can be used with this
       * handler.
       * @param mode The mode to open files with
       */
      FileHandler(const std::string& start="", const std::string& mode="READ");

      ~FileHandler();

      /**
       * @brief Get a pointer to an open file
       * @param name The name of the file
       * @param allowMissing 
       *
       * The handler keeps shared pointers to all files that it has opened. To
       * remove one from this collection, used the @see releaseFile function
       */
      std::shared_ptr<TDirHandler> getFile(
          const std::string& name, bool allowMissing=false);

      /**
       * @Get a pointer to an open file
       * @param path The path whose filename to retrieve
       *
       * Gets the file containing the provided path
       */
      std::shared_ptr<TDirHandler> getFile(
          const Path& path, bool allowMissing=false);

      /**
       * @brief Take ownership over an open file
       *
       * This method will not open a new file.
       *
       * After this, the handler knows nothing about this file anymore, so there
       * is nothing to stop it opening it a second time!
       */
      std::shared_ptr<TFile> releaseFile(const std::string& name);

      std::shared_ptr<TDirHandler> getMkDir(const Path& path);

    private:
      std::string m_start;
      std::string m_mode;
      std::map<std::string, std::shared_ptr<TFile>> m_openFiles;
  }; //> end class FileHandler
} //> end namespace TFileWalker

#endif //> !TFileWalker_FileHandler_H
