//////////////////////////////////////////////////////////
// Microscopic Study                                    //
// By Jakob Glock                                       //
//                                                      //
// -This program uses the addon ofxVoro                 //
// -Click and move the mouse to change the pattern      //
//////////////////////////////////////////////////////////

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /* Basic setup */
    ofBackground(0);
    ofSetVerticalSync(true);

    /* Set mousedown to false and time to zero */
    mouseDown = false;
    time = 0;

    /* Setup variables for drawing the grid */
    float gridSize = 40;
    float xStep = ofGetWidth() / gridSize;
    float yStep = ofGetHeight() / gridSize;
    float xOffset = xStep / 2;
    float yOffset = yStep / 2;

    /* Create particles and position in a grid */
    for(int i=0; i<gridSize; i++){
        for(int j=0; j<gridSize; j++){
            ofVec2f p;
            p.set(xStep * i + xOffset, yStep * j + yOffset);
            myParticles.push_back(new Particle(p, ofVec2f(0, 0)));
        }
    }

    /* Save screen set to false */
    saveScreen = false;

    /* Allocate space for my fbo and clear it of junk */
    scene.allocate(ofGetWidth(), ofGetHeight());
    scene.begin();
    ofClear(0, 0, 0, 255);
    scene.end();

}

//--------------------------------------------------------------
void ofApp::update(){

    /* Increase time */
    time += 0.01;

    /* vector to store my force */
    ofVec2f f;

    /* Loop over myParticles */
    for(int i=0; i<myParticles.size(); i++){

        /* Reset the force */
        myParticles[i]->resetForce();

        /* If the mouse is pressed apply the force */
        if(mouseDown)
        {
            /* Calculate the force based on mouse position */
            float amt = 0.25;
            float xF = ofMap(mouseX, 0, ofGetWidth(), 0, TWO_PI);
            float yF = ofMap(mouseY, 0, ofGetHeight(), 0, TWO_PI);
            f.set(sin(xF * (i*0.0625) + time) * amt, cos(yF * (i*0.0625) + time) * amt);

            /* Add the force to the particle */
            myParticles[i]->addForce(f);
        }

        /* Update the particles */
        myParticles[i]->update();
    }

    /* Clear the voronoi cell frames vector */
    cellMeshWireframes.clear();

    /* Create a container for my voronoi pattern */
    voro::container con(0, ofGetWidth(), 0, ofGetHeight(), 0, 1, 32, 32, 1, true, true, true, 8);

    /* Add a circular wall */
    voro::wall_sphere sph(ofGetWidth()/2, ofGetHeight()/2, 0, 250);
    con.add_wall(sph);

    /* Get the current position of the particles and add them to the voronoi pattern to be calculated */
    for(int i=0; i<myParticles.size(); i++){
        ofVec2f particlePos = myParticles[i]->getPosition();

        ofPoint newCell = ofPoint(particlePos.x, particlePos.y, 0);
        addCellSeed(con, newCell, i, true);

    }

    /* Get the cells from the container, each cell is a ofVboMesh */
    cellMeshWireframes = getCellsFromContainer(con,0,true);

    /* Start my fbo */
    scene.begin();

    /* Clear it every frame */
    ofClear(0, 0, 0, 255);

    /* Enable smoothing */
    ofEnableSmoothing();

    /* Loop over the cellmeshwireframes vector and draw each cell */
    for(int i = 0; i < cellMeshWireframes.size(); i++){
        ofSetLineWidth(1);
        ofSetColor(255);
        cellMeshWireframes[i].draw();
    }

    /* Disable smoothing */
    ofDisableSmoothing();

    /* End the Fbo */
    scene.end();
}

//--------------------------------------------------------------
void ofApp::draw(){

    /* Draw my scene fbo */
    scene.draw(0, 0);

    /* Save the fbo contents to an image file */
    if(saveScreen == true)
    {
        ofPixels pix;
        scene.readToPixels(pix);
        ofSaveImage(pix, ofToDataPath(ofToString(ofGetFrameNum())+".png"));
        saveScreen = false;
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    saveScreen = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouseDown = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouseDown = false;
}
