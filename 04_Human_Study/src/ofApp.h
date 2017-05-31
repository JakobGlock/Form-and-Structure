#pragma once

#include "ofMain.h"
#include "Box.h"

class ofApp : public ofBaseApp{

public:
    
    /* Methods */
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    
    /* camera and light */
    ofEasyCam cam;
    ofLight light;
    float time, zoom, prevZoom;
    
    /* vectors to store my objects */
    vector<Box> myBox;
    vector<Box> myForm;
    
    /* Varibales */
    int drawMode, maxSquares;
    
    /* Fbo to draw my scene in */
    ofFbo scene;
};
