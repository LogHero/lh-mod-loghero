#ifndef SUBMITPOLICYMOCK_H
#define SUBMITPOLICYMOCK_H

#include "LogHeroSettings.h"
#include "LogHeroSession.h"


namespace loghero {
namespace testing {

  class SubmitPolicyMock {
    public:

      std::size_t getNumberOfDumpedLogEvents() const;

    protected:
      SubmitPolicyMock(const LogHeroSettings &);

      typedef DefaultLogBuffer BufferT;

      void dumpAndSubmit(BufferT *pLogBuffer);

    private:

      std::size_t numberOfDumpedLogEvents;
  };

  inline SubmitPolicyMock::SubmitPolicyMock(const LogHeroSettings &):
    numberOfDumpedLogEvents(0) {
  }

  inline void SubmitPolicyMock::dumpAndSubmit(BufferT *pLogBuffer) {
    numberOfDumpedLogEvents += pLogBuffer->dump()->size();
  }

  inline std::size_t SubmitPolicyMock::getNumberOfDumpedLogEvents() const {
    return numberOfDumpedLogEvents;
  }

}}

#endif // SUBMITPOLICYMOCK_H
