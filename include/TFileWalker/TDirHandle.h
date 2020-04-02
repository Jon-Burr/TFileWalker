#ifndef TFileWalker_TDirHandle_H
#define TFileWalker_TDirHandle_H

#include <TDirectory.h>
#include "TFileWalker/Path.h"
#include <memory>

namespace TFileWalker {
  class TDirHandle : public std::enable_shared_from_this<TDirHandle> {
    public:
      /**
       * @brief Create the handler from its path and the contained directory
       * @param path The path from the start position of the parent FileHandler
       * @param dir The TDirectory
       * @param parent The parent FileHandler
       */
      TDirHandle(
          const Path& path,
          TDirectory* dir,
          std::shared_ptr<const TDirHandle> parent);

      TDirHandle(const TDirHandle& other) = delete;

      /// Destructor, closes the directory
      ~TDirHandle();

      /// The path from the start position of the parent fileHandler
      const Path& path() const { return m_path; }

      /// The directory
      const TDirectory* directory() const { return m_dir; }

      TDirectory* directory() { return m_dir; }

      std::shared_ptr<const TDirHandle> parent() const { return m_parent; }

      /**
       * @brief Get a TDirHandle for a subdirectory
       * @param name The name of the subdirectory
       * @param bool allowMissing If true, throw an error if the directory
       * doesn't exist
       *
       * If the directory doesn't exist, a null handler will be returned
       */
      std::shared_ptr<const TDirHandle> getSubDir(
          const std::string& name, bool allowMissing=false) const;

      /**
       * @brief Get a TDirHandle for a subdirectory
       * @param name The name of the subdirectory
       * @param bool allowMissing If true, throw an error if the directory
       * doesn't exist
       *
       * If the directory doesn't exist, a null handler will be returned
       */
      std::shared_ptr<TDirHandle> getSubDir(
          const std::string& name, bool allowMissing=false);

      /**
       * @brief Get a subdirectory, making it if it doesn't exist
       * @param name The subdirectory to retrieve
       *
       * If name is empty, a reference to this is returned
       */
      std::shared_ptr<TDirHandle> getMkDir(const std::string& name);
      std::shared_ptr<TDirHandle> getMkDir(const Path& path) {
        return getMkDir(path.dirPath() );
      }
    protected:
      Path m_path;
      TDirectory* m_dir;
      std::shared_ptr<const TDirHandle> m_parent;
      /// Keep all already created children
      mutable std::map<std::string, std::weak_ptr<TDirHandle>> m_children;
  }; //> end class TDirHandle
}; //> end namespace TFileWalker

#endif //> !TFileWalker_TDirHandle_H
