//////////////////////////////////////////////////////////////////////////////////
// PFA Advanced - Ecological Study                                              //
// By Jakob Glock                                                               //
//                                                                              //
// - You can use the mouse to spin and look at the object from different angles //
// - You can generate a new object by pressing the key 'd'                      //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /* Setup */
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofBackground(0);

    /* Create a tree on setup */
    int randNum = int(ofRandom(8) + 1);
    for(int i=0; i<randNum; i++){
        agents.push_back(new Agent(1, ofVec3f(0, 0, 0), 0, ofVec3f(0, 0, 0), ofVec2f(TWO_PI/5, TWO_PI/7)));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    /* Nothing here to see today */
}

//--------------------------------------------------------------
void ofApp::draw(){

    /* Draw the tree */
    cam.begin();
    for(int i=0; i<agents.size(); i++){
        agents[i]->draw();
    }
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    /* Pressing 'd' creates a new tree */
    if(key == 'd')
    {
        agents.clear();
        int randNum = int(ofRandom(8) + 1);
        for(int i=0; i<randNum; i++){
            agents.push_back(new Agent(1, ofVec3f(0, 0, 0), 0, ofVec3f(0, 0, 0),
                                       ofVec2f(ofMap(ofRandom(ofGetWidth()), 0, ofGetWidth(), 0, PI),
                                               ofMap(ofRandom(ofGetHeight()), 0, ofGetHeight(), 0, TWO_PI))));
        }
    }

}
