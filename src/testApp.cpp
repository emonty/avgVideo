#include "testApp.h"

#include <iostream>

bool showMovie= false;
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
    blues+= pixels[loop+1];
    greens+= pixels[loop+2];
  }
  avg_red= int(reds/color_pixels);
  avg_blue= int(blues/color_pixels);
  avg_green= int(greens/color_pixels);

}

//--------------------------------------------------------------
void testApp::draw(){


  ofBackground(avg_red, avg_blue, avg_green);

  ofSetColor(255-avg_red, 255-avg_blue, 255-avg_green);
  ofDrawBitmapString("RED: dmx: " +
                     ofToString(avg_red) +
                     " percent: " +
                     ofToString(avg_red * 100 / 255), 20, 40);
  ofDrawBitmapString("BLUE: dmx: " +
                     ofToString(avg_blue) +
                     " percent: " +
                     ofToString(avg_blue * 100 / 255), 20, 60);
  ofDrawBitmapString("GREEN: dmx: " +
                     ofToString(avg_green) +
                     " percent: " +
                     ofToString(avg_green * 100 / 255), 20, 80);

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

