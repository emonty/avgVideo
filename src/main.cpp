#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main(int argc, char** argv){

  if (argc < 1)
  {
    std::cout << "Please pass in filename" << std::endl;
    exit(-1);
  }
  const std::string filename(argv[1]);

  ofAppGlutWindow window;
  ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context

  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new testApp(filename));

}
