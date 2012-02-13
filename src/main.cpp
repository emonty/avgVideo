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

#include "ofMain.h"
#include "avgVid.h"
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
  testApp theApp(filename);
  ofRunApp(&theApp);

}
