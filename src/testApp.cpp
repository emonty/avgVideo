#include "testApp.h"
#include "dmxProxy.h"

#include <iostream>

bool showMovie= false;
double multiplier= 1.0;

testApp::testApp(const std::string filename) :
  _filename(filename),
  _movie(),
  screenW(0),
  screenH(0),
  number_of_pixels(0),
  color_pixels(0),
  avg_red(0),
  avg_blue(0),
  avg_green(0),
  _proxy(new DmxProxy),
  _dmx()
{}

testApp::~testApp()
{
  delete _proxy;
}

//--------------------------------------------------------------
void testApp::setup(){

  //ofSetFullscreen(true);

  //_movie.setUseTexture(false);
  _movie.setLoopState(OF_LOOP_NORMAL);
  _movie.loadMovie(_filename);
  _movie.play();
  number_of_pixels= _movie.width*_movie.height;
  color_pixels = number_of_pixels / 3;
  

  _movie.firstFrame();

}

//--------------------------------------------------------------
void testApp::update(){

  _movie.idleMovie();
  unsigned char *pixels = _movie.getPixels();
  long double reds= 0.0;
  long double blues= 0.0;
  long double greens= 0.0;
  for (unsigned int loop=0; loop <= number_of_pixels; loop+=3)
  {
    reds+= pixels[loop];
    greens+= pixels[loop+1];
    blues+= pixels[loop+2];
  }
  avg_red= int(reds/color_pixels*multiplier);
  avg_green= int(greens/color_pixels*multiplier);
  avg_blue= int(blues/color_pixels*multiplier);

  _dmx.SetChannel(0, avg_red);
  _dmx.SetChannel(1, avg_green);
  _dmx.SetChannel(2, avg_blue);
}

//--------------------------------------------------------------
void testApp::draw(){


  ofBackground(avg_red, avg_green, avg_blue);

  ofSetColor(255-avg_red, 255-avg_green, 255-avg_blue);
  _proxy->sendDmx(_dmx);

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
                     ofToString(int(multiplier * 100)), 20, 100);

  if (showMovie)
  {
    _movie.draw(60,100);
  }
  if (_movie.getCurrentFrame() < _movie.getTotalNumFrames())
  {
    _movie.nextFrame();
  }
  else
  {
    _movie.firstFrame();
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

