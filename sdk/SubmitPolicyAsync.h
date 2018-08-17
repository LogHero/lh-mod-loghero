#ifndef SUBMITPOLICYASYNC_H
#define SUBMITPOLICYASYNC_H

#include "LogHeroSettings.h"
#include "SubmitPolicySync.h"

#include <future>


namespace loghero {

  template <class BufferT_, class HttpRequestT, class SerializerT>
  class SubmitPolicyAsync {
    public:
      DISALLOW_COPY_AND_ASSIGN(SubmitPolicyAsync);
      SubmitPolicyAsync(const LogHeroSettings &settings);
      virtual ~SubmitPolicyAsync(){}

    protected:
      typedef BufferT_ BufferT;

      auto dumpAndSubmit(BufferT *pLogBuffer);

      LogHeroSettings settings;
      std::launch launchPolicy;
  };

  template <class BufferT_, class HttpRequestT, class SerializerT>
  SubmitPolicyAsync<BufferT_, HttpRequestT, SerializerT>::SubmitPolicyAsync(const LogHeroSettings &settings):
    settings(settings),
    launchPolicy(std::launch::async) {
  }

  template <class BufferT_, class HttpRequestT, class SerializerT>
  auto SubmitPolicyAsync<BufferT_, HttpRequestT, SerializerT>::dumpAndSubmit(BufferT *pLogBuffer) {
    return std::async(this->launchPolicy, [=]() {
      SubmitPolicySync<BufferT_, HttpRequestT, SerializerT>::dumpAndSubmit(pLogBuffer, this->settings);
    });
  }

}
#endif // SUBMITPOLICYASYNC_H
