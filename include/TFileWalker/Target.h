#ifndef TFileWalker_Target_H
#define TFileWalker_Target_H

#include "TFileWalker/FileHandler.h"
#include "TFileWalker/TDirHandler.h"
#include "TFileWalker/Path.h"
#include <TDirectory.h>
#include <string>

namespace TFileWalker {
  /**
   * @brief The target for a rule in the output file
   */
  class Target {
    public:
      virtual ~Target() {}

      /// Get the path to this in the output file
      const Path& path() const { return m_path; }

      /// The wrapped TObject
      virtual const TObject* wrapped() const = 0;
      virtual TObject* wrapped() = 0;

      /// Merge a new object into this one
      virtual void merge(TObject* other) = 0;

      /// Write to the provided file
      virtual void write() const;

      std::shared_ptr<TDirHandler> outputDir() const { return m_outputDir; }

    protected:
      /// Create the target with its location in the output file
      Target(const Path& outputPath, std::shared_ptr<TDirHandler> outputDir);

    private:
      Path m_path;
      std::shared_ptr<TDirHandler> m_outputDir;
  }; //> end class Target

} //> end namespace TFileWalker

#endif //> !TFileWalker_Target_H
