/* -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
 *  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 *
 *  avgVideo - outputs average color values of video frames as DMX
 *  Copyright (C) 2012 Monty Taylor
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dmxProxy.h"

#include <ola/Callback.h>
#include <ola/DmxBuffer.h>
#include <ola/OlaClient.h>
#include <ola/OlaClientWrapper.h>

#include <iostream>
#include <cerrno>

DmxProxy::DmxProxy() :
  ola_client(new ola::SimpleClient),
  client(NULL)
{
  ola::SimpleClient *simple_client=
    static_cast<ola::SimpleClient *>(ola_client);

  if (not simple_client->Setup()) {
    std::cout << "error: " << strerror(errno) << std::endl;
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
