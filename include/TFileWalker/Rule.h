#ifndef TFileWalker_Rule_H
#define TFileWalker_Rule_H

#include "TFileWalker/Target.h"
#include "TFileWalker/Path.h"
#include "TFileWalker/OutputHandler.h"
#include <TObject.h>
#include <TKey.h>
#include <TDirectory.h>
#include <memory>

namespace TFileWalker {
  /**
   * @brief A rule describes how to read object from an input file and map them
   * to a target in an output file
   */
  class Rule {
    public:
      virtual ~Rule() {}

      /// Helper struct to wrap the return of the find method
      struct FoundObject {
        /// The TObject found by the rule
        TObject* object{nullptr};
        /// The full path to the found object in the input
        Path inputPath{"", "", ""};
        /// The target path in the output
        Path outputPath{"", "", ""};

        /// Is this valid
        operator bool() { return object != nullptr; }
      }; //> end struct FoundObject

      /// does this rule use anything in the specified file
      virtual bool useFile(const std::string& fileName) const = 0;

      /// does this rule use anything in the specified file
      virtual bool useFile(const Path& path) const {
        return useFile(path.fileName() );
      }

      /// Does this rule use anything in the provided directory path
      virtual bool useDir(const Path& path) const = 0;

      /// Read the full object
      virtual FoundObject read(TKey& key, const Path& path) const = 0;

      /// Create the output object
      virtual std::unique_ptr<Target> create(
          const FoundObject& obj, FileHandler& output) const = 0;

      virtual void mergeTo(
          TKey& key, const Path& path, OutputHandler& output) const;
  }; //> end class Rule
} //> end namespace TFileWalker
#endif //> !TFileWalker_Rule_H
