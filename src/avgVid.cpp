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

#include "avgVid.h"

#include <ola/Logging.h>

#include <iostream>


testApp::testApp(const std::string filename) :
  _filename(filename),
  _movie(),
  color_pixels(0),
  avg_red(0),
  avg_blue(0),
  avg_green(0),
  showMovie(false),
  multiplier(1.0),
  _client(),
  _dmx()
{}

testApp::~testApp()
{
  _dmx.Blackout();
  _client.SendDmx(0, _dmx);
  _client.Stop();
}

//--------------------------------------------------------------
void testApp::setup(){

  //ofSetFullscreen(true);

  //_movie.setUseTexture(false);
  _movie.setLoopState(OF_LOOP_NORMAL);
  _movie.loadMovie(_filename);
  _movie.play();
  color_pixels = _movie.width * _movie.height / 3;

  _movie.firstFrame();

  ola::InitLogging(ola::OLA_LOG_WARN, ola::OLA_LOG_STDERR);

  _dmx.Blackout();

  if (not _client.Setup())
  {
    std::cout << "OLA Client setup failed" << std::endl;
    exit();
  }
}

//--------------------------------------------------------------
void testApp::update(){

  _movie.idleMovie();
  const ofPixelsRef pixels= _movie.getPixelsRef();
  long double reds= 0.0;
  long double blues= 0.0;
  long double greens= 0.0;

  for (int x= 0; x < _movie.width; ++x)
  {
    for (int y= 0; y < _movie.height; ++y)
    {
      reds += pixels.getColor(x, y).r;
      greens += pixels.getColor(x, y).g;
      blues += pixels.getColor(x, y).b;
    }
  }

  // Divide by 10 because ofColor rgb values are in units of 0-1000.
  //
  // Then we multiply by 2.55 to get us on DMX scale and not percentage
  avg_red= int(reds/color_pixels*multiplier)/10*2.55;
  avg_green= int(greens/color_pixels*multiplier)/10*2.55;
  avg_blue= int(blues/color_pixels*multiplier)/10*2.55;

  _dmx.SetChannel(0, avg_red);
  _dmx.SetChannel(1, avg_green);
  _dmx.SetChannel(2, avg_blue);
}

//--------------------------------------------------------------
void testApp::draw(){


  ofBackground(avg_red, avg_green, avg_blue);

  ofSetColor(255-avg_red, 255-avg_green, 255-avg_blue);
  _client.SendDmx(0, _dmx);

  ofDrawBitmapString("RED: dmx: " +
                     ofToString(avg_red) +
                     " percent: " +
                     ofToString(avg_red * 100 / 255), 20, 40);
  ofDrawBitmapString("GREEN: dmx: " +
                     ofToString(avg_green) +
                     " percent: " +
                     ofToString(avg_green * 100 / 255), 20, 60);
  ofDrawBitmapString("BLUE: dmx: " +
                     ofToString(avg_blue) +
                     " percent: " +
                     ofToString(avg_blue * 100 / 255), 20, 80);
  ofDrawBitmapString("PERCENT: " +
                     ofToString(int(multiplier * 100)), 20, 110);

  if (showMovie)
  {
    _movie.draw(60,100);
  }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  switch(key) {
    case 'v':
      showMovie = showMovie ? false : true;
      break;
    case '+':
      if (multiplier < 1)
        multiplier += 0.01;
      break;
    case '-':
      if (multiplier > 0)
        multiplier -= 0.01;
      break;
    case 'f':
      multiplier = 1;
      break;
    case '0':
      multiplier = 0;
      break;
  }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
  (void)key;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
  (void)x;
  (void)y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  (void)x; (void)y; (void)button;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  (void)x; (void)y; (void)button;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
  (void)x; (void)y; (void)button;

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
  (void)w; (void)h;

}

