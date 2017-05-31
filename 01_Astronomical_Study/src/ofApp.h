#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

public:
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

    /* Create gui panel and sliders */
    ofxPanel gui;
    ofxIntSlider numPointsSlider;
    ofxIntSlider startSizeX;
    ofxIntSlider startSizeY;
    ofxIntSlider startFreq1;
    ofxIntSlider startFreq2;
    ofxIntSlider startFreq3;
    ofxIntSlider startFreq4;
    ofxFloatSlider attractAmt1;
    ofxFloatSlider attractAmt2;
    ofxFloatSlider attractAmt3;
    ofxFloatSlider attractAmt4;
    ofxFloatSlider attractAmt5;
    ofxFloatSlider attractAmt6;

    /* Vector and varibles */
    vector<Particle> myParticles;
    int numPoints;
    float angle, centerX, centerY;

    /* Fbo */
    ofFbo fbo;
    ofPixels pix;
    bool saveScreen;

};
