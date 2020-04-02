#include "TFileWalker/Target.h"
#include <stdexcept>
#include <sstream>

namespace TFileWalker {
  void Target::write()  const
  {
    outputDir()->directory()->WriteTObject(wrapped(), m_path.name().c_str() );
  }

  Target::Target(const Path& outputPath, std::shared_ptr<TDirHandler> outputDir) :
    m_path(outputPath), m_outputDir(outputDir)
  {
  }
} //> end namespace TFileWalker
