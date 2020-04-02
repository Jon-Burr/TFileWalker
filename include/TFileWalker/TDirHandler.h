#ifndef TFileWalker_TDirHandler_H
#define TFileWalker_TDirHandler_H

#include <TDirectory.h>
#include "TFileWalker/Path.h"
#include <memory>

namespace TFileWalker {
  class TDirHandler : public std::enable_shared_from_this<TDirHandler> {
    public:
      /**
       * @brief Create the handler from its path and the contained directory
       * @param path The path from the start position of the parent FileHandler
       * @param dir The TDirectory
       * @param parent The parent FileHandler
       */
      TDirHandler(
          const Path& path,
          TDirectory& dir,
          std::shared_ptr<const TDirHandler> parent);

      TDirHandler(const TDirHandler& other) = delete;

      /// Destructor, closes the directory
      ~TDirHandler();

      /// The path from the start position of the parent fileHandler
      const Path& path() const { return m_path; }

      /// The directory
      const TDirectory* directory() const { return m_dir; }

      TDirectory* directory() { return m_dir; }

      std::shared_ptr<const TDirHandler> parent() const { return m_parent; }

      /**
       * @brief Get a TDirHandler for a subdirectory
       * @param name The name of the subdirectory
       * @param bool allowMissing If true, throw an error if the directory
       * doesn't exist
       *
       * If the directory doesn't exist, a null handler will be returned
       */
      std::shared_ptr<const TDirHandler> getSubDir(
          const std::string& name, bool allowMissing=false) const;

      /**
       * @brief Get a TDirHandler for a subdirectory
       * @param name The name of the subdirectory
       * @param bool allowMissing If true, throw an error if the directory
       * doesn't exist
       *
       * If the directory doesn't exist, a null handler will be returned
       */
      std::shared_ptr<TDirHandler> getSubDir(
          const std::string& name, bool allowMissing=false);

      /**
       * @brief Get a subdirectory, making it if it doesn't exist
       * @param name The subdirectory to retrieve
       *
       * If name is empty, a reference to this is returned
       */
      std::shared_ptr<TDirHandler> getMkDir(const std::string& name);
      std::shared_ptr<TDirHandler> getMkDir(const Path& path) {
        return getMkDir(path.dirPath() );
      }
    private:
      Path m_path;
      TDirectory* m_dir;
      std::shared_ptr<const TDirHandler> m_parent;
  }; //> end class TDirHandler
}; //> end namespace TFileWalker

#endif //> !TFileWalker_TDirHandler_H
