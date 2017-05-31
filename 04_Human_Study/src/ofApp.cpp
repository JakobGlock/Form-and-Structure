////////////////////////////////////////////////////////
// PFA Advanced - Human Study                         //
// By Jakob Glock                                     //
//                                                    //
// Inspired by http://paulbourke.net/fractals/dla/    //
////////////////////////////////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* Basic setup */
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofBackground(0);
    ofEnableAlphaBlending();

    /* Set up lighting */
    light.setParent(cam);

    /* Set drawmode to zero */
    drawMode = 0;

    /* Create a seed object in the form and place it in the center */
    myForm.push_back(Box(false));
    myForm[myForm.size()-1].pos = ofVec3f(0, 0, 0);

    /* Set max squares to 200 */
    maxSquares = 200;

    /* Create 200 paricle/cubes */
    for(int i=0; i<maxSquares; i++){
        myBox.push_back(Box(true));
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    /* Calculate everything 50 times a frame to speed the process up */
    for(int a=0; a<50; a++){

        /* Loop over the particle boxes and update them */
        for(int i=0; i<myBox.size(); i++){
            myBox[i].update();
        }

        /* Loop over the form and particles */
        for(int i=0; i<myForm.size(); i++){
            for(int j=0; j<myBox.size(); j++){

                /* Calculate the distance between the particles and form */
                float d = ofDist(myForm[i].pos.x, myForm[i].pos.y, myForm[i].pos.z, myBox[j].pos.x, myBox[j].pos.y, myBox[j].pos.z);

                /* If the distance is equal to 10/next to each other add it to the form and delete it */
                if(d == 10)
                {
                    myForm.push_back(myBox[j]);
                    myForm[myForm.size()-1].isMoving = false;
                    myBox.erase(myBox.begin()+j);
                }
            }
        }

        /* Check to see if they are out of the defined space */
        for(int i=0; i<myBox.size(); i++){
            if(myBox[i].outOfScreen())
            {
                /* delete them and add a new one if they are going too far away from the form */
                myBox.erase(myBox.begin()+i);
                myBox.push_back(Box(true));
            }
        }
    }

    /* Count how many neighbours each one has */
    for(int i=0; i<myForm.size(); i++){
        for(int j=0; j<myForm.size(); j++){

            /* If they have to many neighbours to delete the latest one and create a new object somewhere else */
            if(myForm[i].increaseNeighbours(myForm[j].pos))
            {
                myForm.erase(myForm.begin()+i);
                myBox.push_back(Box(true));
            }
        }
    }

    /* If the form is equal to 200, clear eveything and start again */
    if(myForm.size() == 200)
    {
        /* Clear vectors */
        myForm.clear();
        myBox.clear();

        /* Increase drawmode */
        drawMode++;

        /* Create a new seed form */
        myForm.push_back(Box(false));
        myForm[myForm.size()-1].pos = ofVec3f(0, 0, 0);

        /* create 200 particles */
        for(int i=0; i<maxSquares; i++){
            myBox.push_back(Box(true));
        }
    }

    /* Increase time */
    time += 0.001;

}

//--------------------------------------------------------------
void ofApp::draw(){

    /* values to rotate the camera */
    float rotX = ofSignedNoise(time) * 0.25;
    float rotY = ofSignedNoise(time+8345) * 0.25;
    float rotZ = ofSignedNoise(time+298) * 0.25;
    float rS = 10 / 1000 + 0.01;

    /* Rotate the camera */
    cam.rotateAround(0.5, ofVec3f(rotX, rotY, rotZ), ofVec3f(abs(rotY*rS), abs(rotZ*rS), abs(rotX*rS)));

    /* Always look at the center */
    cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(1, 1, 1));

    /* smoothing zoom */
    prevZoom = ofMap(myForm.size(), 0, maxSquares, 50, 200, true);
    zoom =  0.95f * zoom + 0.05f * prevZoom;

    /* set the distance of the camera */
    cam.setDistance(zoom);

    /* Begin the camera */
    cam.begin();

    /* Draw cube wireframe or solid cubes */
    if(drawMode%2 == 0)
    {
        /* Draw solid cubes with lights */
        light.enable();
        ofFill();
        for(int i=0; i<myForm.size(); i++){
            myForm[i].draw(ofColor(255));
        }
        light.disable();
    }
    else
    {
        /* draw cube wireframe, without lights */
        ofNoFill();
        ofSetLineWidth(2);
        for(int i=0; i<myForm.size(); i++){
            myForm[i].draw(ofColor(255));
        }
    }
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
