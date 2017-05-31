#include "ofMain.h"
#include "ofApp.h"

/* Here I am using a different version of openGL to what is standard when openframeworks starts up */

//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);     // this kicks off the running of my app
    ofRunApp(new ofApp());
}
