#ifndef TFileWalker_Path_H
#define TFileWalker_Path_H

#include <string>

namespace TFileWalker {
  /**
   * @brief Class representing a full TFile path
   *
   * The path is split down into a file name, a directory path and an object
   * name. The full format of the string is
   * fileName:full/dir/path/objectName.
   * A path can be within a file, in which case the fileName part is blank (in
   * this case the colon can be omitted).
   */
  class Path {
    public:
      /// Create a path from a full string
      Path(const std::string& name);
      /// Create the path from the three components
      Path(
          const std::string& fileName,
          const std::string& dirPath,
          const std::string& name);

      /// The file name
      const std::string& fileName() const { return m_fileName; }

      /// The directory path
      const std::string& dirPath() const { return m_dirPath; }

      /// The object name
      const std::string& name() const { return m_name; }

      /// The full name
      std::string fullName() const;

      /// The internal path, excluding the filename
      Path internalPath() const { return Path("", dirPath(), name() ); }

      /// string conversion operator produces the full string
      operator std::string() const { return fullName(); }

      /// Get the path for a path relative to this
      Path getPath(const std::string& name) const;
    private:
      std::string m_fileName;
      std::string m_dirPath;
      std::string m_name;
  }; //> end class Path
} //> end namespace TFileWalker

#endif //> !TFileWalker_Path_H
