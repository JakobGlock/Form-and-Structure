////////////////////////////////////////
// PFA Advanced - Astronomical Study //
// By Jakob Glock                    //
///////////////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /* Initial setup */
    ofBackground(0);
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    /* Allocating space for my fbo */
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(0, 0, 0, 255); // Clear any junk out
    fbo.end();

    /* Setting up my GUI */
    gui.setup();
    gui.add(numPointsSlider.setup("numPoints", 180, 1, 360));
    gui.add(startSizeX.setup("startSizeX", 200, 10, 600));
    gui.add(startSizeY.setup("startSizeY", 200, 10, 600));
    gui.add(startFreq1.setup("startFreq1", 1, 1, 128));
    gui.add(startFreq2.setup("startFreq2", 1, 1, 128));
    gui.add(attractAmt1.setup("attractAmt1", 1.5, -2, 2));
    gui.add(attractAmt2.setup("attractAmt2", 0.2, -2, 2));
    gui.add(attractAmt3.setup("attractAmt3", 0.2, -2, 2));
    gui.add(attractAmt4.setup("attractAmt4", 0.25, -2, 2));
    gui.add(attractAmt5.setup("attractAmt5", 0.25, -2, 2));
    gui.add(attractAmt6.setup("attractAmt6", -0.125, -2, 2));

    /* Initialize variables */
    numPoints = 180;
    angle = TWO_PI / numPoints;
    centerX = ofGetWidth()/2;
    centerY = ofGetHeight()/2;

    /* Initialize saveScreen to false */
    saveScreen = false;

    /* Draw some points to the screen on setup */
    for(int i=0; i<numPoints; i++){
        ofVec3f p;
        p.set(cos(angle*i) * 200 + centerX, sin(angle*i) * 200 + centerY, 0);
        myParticles.push_back(Particle(p, i, angle, centerX, centerY));
        myParticles[i].setColor(ofColor(255, 255, 255, 2));
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i=0; i<myParticles.size(); i++){
            myParticles[i].update(); // Call the update function
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    /* Begin my fbo */
    fbo.begin();

    /* Draw my points to the fbo */
    for(int i=0; i<myParticles.size(); i++){
        for(int j=0; j<myParticles.size(); j++){
            myParticles[i].drawLine(myParticles[j].pos); // This draws lines between the points
        }
    }

    /* If saveScreen is true save the frame and use the frame number to name it */
    if(saveScreen){
        fbo.readToPixels(pix);
        ofSaveImage(pix, ofToDataPath(ofToString(ofGetFrameNum())+".png"));
        saveScreen = false; //set savescreen back to false
    }

    /* End my fbo */
    fbo.end();

    /* Draw my fbo */
    fbo.draw(0, 0);

    /* Draw my GUI */
    gui.draw();

    ofDrawBitmapString("-- Press 'a' to reset with new starting variables ---- Press 's' to save the current image --", 45, ofGetHeight() - 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'a')
    {
        /* Clear the fbo and then reallocate space and clear any junk out */
        fbo.clear();
        fbo.allocate(ofGetWidth(), ofGetHeight());
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();

        /* Clear my particles vector */
        myParticles.clear();

        /* Set new variables */
        numPoints = numPointsSlider; // Here I am getting the value from a slider in my gui
        angle = TWO_PI / numPoints;
        centerX = ofGetWidth()/2;
        centerY = ofGetHeight()/2;

        /* Create some points */
        for(int i=0; i<numPoints; i++){
            ofVec3f p;
            p.set(cos(angle*i*startFreq1) * startSizeX + centerX, sin(angle*i*startFreq2) * startSizeY + centerY, 0);
            myParticles.push_back(Particle(p, i, angle, centerX, centerY));

            /* Set varibles based on my slider values */
            myParticles[i].setColor(ofColor(255, 255, 255, 2));
            myParticles[i].attractAmt1 = attractAmt1;
            myParticles[i].attractAmt2 = attractAmt2;
            myParticles[i].attractAmt3 = attractAmt3;
            myParticles[i].attractAmt4 = attractAmt4;
            myParticles[i].attractAmt5 = attractAmt5;
            myParticles[i].attractAmt6 = attractAmt6;
        }
    }

    if(key == 's'){

        saveScreen = true; // If 's' is pressed set saveScreen to true

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
