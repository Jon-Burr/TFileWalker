#include "TFileWalker/HistoTarget.h"

namespace TFileWalker {
  HistoTarget::HistoTarget(
      const std::string& outputName,
      std::shared_ptr<TDirHandler> tdir,
      const TH1* histo) :
    Target(outputName, tdir)
  {
    tdir->directory()->cd();
    m_obj = dynamic_cast<TH1*>(histo->Clone() );
    if (!m_obj)
      throw std::runtime_error(outputName+" clone failed!");
  }

  HistoTarget::~HistoTarget() {}

  void HistoTarget::merge(TObject* other)
  {
    TH1* hist = dynamic_cast<TH1*>(other);
    if (!hist)
      throw std::runtime_error(path().fullName() + ": merge did not receive a histogram");
    wrapped()->Add(hist);
  }
} //> end namespace TFileWalker
