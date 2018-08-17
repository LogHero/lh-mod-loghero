#ifndef SUBMITPOLICYSYNC_H
#define SUBMITPOLICYSYNC_H

#include "APIAccess.h"
#include "LogHeroSettings.h"

#include <memory>


namespace loghero {

  template <class BufferT_, class HttpRequestT, class SerializerT>
  class SubmitPolicySync {
    public:      
      typedef BufferT_ BufferT;

      DISALLOW_COPY_AND_ASSIGN(SubmitPolicySync);
      SubmitPolicySync(const LogHeroSettings &settings);
      virtual ~SubmitPolicySync(){}

      static void dumpAndSubmit(BufferT *pLogBuffer, const LogHeroSettings &settings);

    protected:

      void dumpAndSubmit(BufferT *pLogBuffer);

      LogHeroSettings settings;
  };

  template <class BufferT_, class HttpRequestT, class SerializerT>
  SubmitPolicySync<BufferT_, HttpRequestT, SerializerT>::SubmitPolicySync(const LogHeroSettings &settings):
    settings(settings) {
  }

  template <class BufferT_, class HttpRequestT, class SerializerT>
  void SubmitPolicySync<BufferT_, HttpRequestT, SerializerT>::dumpAndSubmit(BufferT *pLogBuffer) {
    SubmitPolicySync<BufferT_, HttpRequestT, SerializerT>::dumpAndSubmit(pLogBuffer, this->settings);
  }

  template <class BufferT_, class HttpRequestT, class SerializerT>
  void SubmitPolicySync<BufferT_, HttpRequestT, SerializerT>::dumpAndSubmit(
      BufferT *pLogBuffer,
      const LogHeroSettings &settings
  ) {
    loghero::APIAccess<HttpRequestT, SerializerT> apiAccess(settings);
    std::unique_ptr<LogEvent::List> pLogEventsToSend = pLogBuffer->dump();
    apiAccess.submitLogEvents(*pLogEventsToSend);
  }

}

#endif // SUBMITPOLICYSYNC_H
