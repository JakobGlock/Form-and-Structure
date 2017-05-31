///////////////////////////////////////////////////////////////////////////////////
// PFA Advanced - Planetary Study                                                //
//                                                                               //
// This study is based around the idea of waves travelling across long distances //
//                                                                               //
// By Jakob Glock                                                                //
///////////////////////////////////////////////////////////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /* Need this for 3D */
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofSetFrameRate(60);

    /* Setup GUI */
    gui.setup();
    gui.add(xFreq.setup("xFreq", 10., 0.0, 128.0));
    gui.add(yFreq.setup("yFreq", 8., 0.0, 128.0));
    gui.add(zFreq.setup("zFreq", 7., 0.0, 128.0));
    gui.add(xDepth.setup("xDepth", 0.15, 0.0, 2.0));
    gui.add(yDepth.setup("yDepth", 0.12, 0.0, 2.0));
    gui.add(zDepth.setup("zDepth", 0.18, 0.0, 2.0));
    gui.add(blurAmt.setup("Blur Amt", 0.24, 0.0, 16.0));
    gui.add(speed.setup("Speed", 0.03, 0.0, 2.0));

    /* Set cam distance */
    cam.setDistance(-1000);

    /* Set window shape */
    ofSetWindowShape(841, 594);
    ofBackground(0);
    ofSetSphereResolution(360);
    time = 0;

    /* Allocate FBO space and clear them of junk */
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();

    /* Allocate FBO space for the first pass of the blur */
    blurPassOne.allocate(ofGetWidth(), ofGetHeight());
    blurPassOne.begin();
    ofClear(0, 0, 0, 255);
    blurPassOne.end();

    /* Allocate FBO space for the second pass of the blur */
    blurPassTwo.allocate(ofGetWidth(), ofGetHeight());
    blurPassTwo.begin();
    ofClear(0, 0, 0, 255);
    blurPassTwo.end();

    /* Load the shaders */
    shader.load("vertShader.vert", "fragShader.frag");
    blurX.load("blurvertx.vert", "blurfragx.frag");
    blurY.load("blurverty.vert", "blurfragy.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
    /* Time forever */
    time+=speed;

    /* ofEnableDepthTest() is needed for 3D */
    ofEnableDepthTest();
    fbo.begin(); // Begin FBO
    shader.begin(); // Begin Shader
    cam.begin(); // Begin cam

    /* Clear before drawing */
    ofClear(0, 0, 0, 255);

    /* Sending values into shader */
    shader.setUniform1f("time", time);
    shader.setUniform3f("freq", xFreq, yFreq, zFreq);
    shader.setUniform3f("depth", xDepth, yDepth, zDepth);

    /* Draw something here */
    ofDrawSphere(0, 0, 200);

    cam.end(); // End cam
    shader.end(); // End shader
    fbo.end(); // End FBO

    ofDisableDepthTest(); // Disbale depth test otherwise it messes with the gui panel

    /* Gaussian blur */
    /* Blur Pass One */
    blurPassOne.begin();
    blurX.begin();
    blurX.setUniform1f("blurAmnt", blurAmt);
    fbo.draw(0, 0);
    blurX.end();
    blurPassOne.end();

    /* Blur Pass Two */
    blurPassTwo.begin();
    blurY.begin();
    blurY.setUniform1f("blurAmnt", blurAmt);
    blurPassOne.draw(0, 0);
    blurY.end();
    blurPassTwo.end();

    /* If saveScreen is true save the frame and use the frame number to name it */
    if(saveScreen){
        blurPassTwo.readToPixels(pix);
        ofSaveImage(pix, ofToDataPath(ofToString(ofGetFrameNum())+".png"));
        saveScreen = false; //set savescreen back to false
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    /* Draw the scene */
    blurPassTwo.draw(0, 0);

    /* Draw the GUI panel */
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    /* Press the 's' key to save a screenshot */

    if(key == 's')
    {
        saveScreen = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    /* Reload the shaders */
    shader.load("vertShader.vert", "fragShader.frag");
    blurX.load("blurvertx.vert", "blurfragx.frag");
    blurY.load("blurverty.vert", "blurfragy.frag");
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
