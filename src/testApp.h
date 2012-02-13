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

#include <vector>
#include <ola/DmxBuffer.h>
#include <ola/StreamingClient.h>

#include "ofMain.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

class DmxProxy;

class testApp :
  public ofBaseApp
{

  const std::string _filename;
  ofVideoPlayer _movie;
  int screenW;
  int screenH;
  unsigned int number_of_pixels;
  unsigned int color_pixels;
  int avg_red;
  int avg_blue;
  int avg_green;
  ola::StreamingClient _client;
  ola::DmxBuffer _dmx;
public:
  explicit testApp(const std::string filename);
  virtual ~testApp();

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);

};
