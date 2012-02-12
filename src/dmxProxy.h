#pragma once

#include <ola/DmxBuffer.h>

namespace ola
{
  class OlaClient;
namespace network
{
  class SelectServer;
}
}


class DmxProxy
{
  void *ola_client;
  ola::OlaClient *client;
  DmxProxy& operator=(const DmxProxy&);
  DmxProxy(const DmxProxy&);

public:
  DmxProxy();
  ~DmxProxy();

  void sendDmx(const ola::DmxBuffer &dmx);
};
