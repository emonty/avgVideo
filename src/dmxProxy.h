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

#pragma once

#include <ola/DmxBuffer.h>

namespace ola
{
  class OlaClient;
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
