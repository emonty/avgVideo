#include <ola/Callback.h>
#include <ola/DmxBuffer.h>
#include <ola/OlaClient.h>
#include <ola/OlaClientWrapper.h>

#include "dmxProxy.h"

#include <cstdio>
#include <cerrno>

DmxProxy::DmxProxy() :
  ola_client(new ola::SimpleClient),
  client(NULL)
{
  ola::SimpleClient *simple_client=
    static_cast<ola::SimpleClient *>(ola_client);

  if (not simple_client->Setup()) {
    printf("error: %s", strerror(errno));
    exit(1);
  }
  client= simple_client->GetClient();
}

DmxProxy::~DmxProxy()
{
  delete static_cast<ola::SimpleClient *>(ola_client);
}

void DmxProxy::sendDmx(const ola::DmxBuffer &dmx)
{
  client->SendDmx(0, dmx);
}
