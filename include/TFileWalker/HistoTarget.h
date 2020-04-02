#ifndef TFileWalker_HistoTarget_H
#define TFileWalker_HistoTarget_H

#include "TFileWalker/Target.h"
#include "TH1.h"

namespace TFileWalker {
  class HistoTarget : public Target {
    public:
      /**
       * @brief Create the target
       * @param outputName The full location in the output file
       * @param histo The starting histogram to clone from
       * @param tdir The output directory
       */
      HistoTarget(
          const std::string& outputName,
          std::shared_ptr<TDirHandler> tdir,
          const TH1* histo);

      ~HistoTarget() override;

      TH1* wrapped() override { return m_obj; }
      const TH1* wrapped() const override { return m_obj; }
      void merge(TObject* other) override;
    private:
      /// The wrapped object
      TH1* m_obj;
  }; //> end class HistoTarget
} //> end namespace TFileWalker

#endif //> !TFileWalker_HistoTarget_H
