#ifndef _TEST_APP
#define _TEST_APP

#include <vector>
#include <ola/DmxBuffer.h>

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
  DmxProxy *_proxy;
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

#endif
