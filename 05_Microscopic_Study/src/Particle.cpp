#include "Particle.h"

/* Here i call the spring constructor */
//--------------------------------------------------------------
Particle::Particle(ofVec2f _p, ofVec2f _v) : mySpring(ofVec2f(_p.x, _p.y), ofVec2f(_p.x, _p.y)){
    pos.set(_p.x, _p.y);
    vel.set(_v.x, _v.y);
    frc.set(0, 0);
    radius = 40;
    friction = 0.04f;
}

//--------------------------------------------------------------
void Particle::update(){

    /* Calculate the spring force and add it to the particle force */
    ofVec2f springForce = mySpring.update(pos);
    frc += springForce;

    /* Dampen force */
    dampenForce();

    /* Calculate the physics */
    vel += frc;
    pos += vel;

}

//--------------------------------------------------------------
void Particle::draw(){
    ofSetColor(255);
    ofDrawCircle(pos.x, pos.y, radius);
    //mySpring.draw();
}

//--------------------------------------------------------------
void Particle::dampenForce(){
    /* Calculate the dampening */
    frc.x = frc.x - vel.x * friction;
    frc.y = frc.y - vel.y * friction;
}

//--------------------------------------------------------------
void Particle::addForce(ofVec2f _f){
    /* add a force */
    frc += _f;
}

//--------------------------------------------------------------
void Particle::resetForce(){
    frc.set(0, 0);
}

//--------------------------------------------------------------
ofVec2f Particle::getPosition(){
    return pos;
}
