//
//  ofxAEOverlay.cpp
//
//  Created by Roy Macdonald on 9/30/14.
//
//

#include "ofxAEOverlay.h"

//--------------------------------------------------------------
void ofxAEOverlay::setGuiParams(string name){
    parameters.setName(name);
    parameters.add(traslateAdj.set("TranslateAdj", ofVec3f(0), ofVec3f(-600), ofVec3f(600)));
    parameters.add(scaleAdj.set("ScaleAdj", ofVec3f(1), ofVec3f(0), ofVec3f(10)));
    parameters.add(rotationAdj.set("RotationAdj", 0, -180, 180));
    traslateAdj.addListener(this, &ofxAEOverlay::onTranslateAdjustChange);
    scaleAdj.addListener(this, &ofxAEOverlay::onScaleAdjustChange);
    rotationAdj.addListener(this, &ofxAEOverlay::onRotationAdjustChange);
}
//--------------------------------------------------------------
void ofxAEOverlay:: onTranslateAdjustChange(ofVec3f & t){
    for (int i = 0; i < transforms.size(); i++) {
        transforms[i].translateAdjust.set(t);
    }
}
//--------------------------------------------------------------
void ofxAEOverlay:: onScaleAdjustChange(ofVec3f & t){
    for (int i = 0; i < transforms.size(); i++) {
        transforms[i].scaleAdjust.set(t);
    }
}
//--------------------------------------------------------------
void ofxAEOverlay:: onRotationAdjustChange(float & f){
    for (int i = 0; i < transforms.size(); i++) {
        transforms[i].rotationAdjust = f;
    }
}
//--------------------------------------------------------------
void ofxAEOverlay::setImg(ofImage & i){
    img.clear();
    img.setFromPixels(i.getPixelsRef());
    img.update();
}
//--------------------------------------------------------------
void ofxAEOverlay::draw(unsigned long frame){
    if (img.isAllocated()) {
        for (int i = 0; i < transforms.size(); i++) {
            transforms[i].drawAt(frame, img);
        }
    }
}
//--------------------------------------------------------------
void ofxAEOverlay::loadKeyframes(string path){
        AEreadTransformKeyframes(path, transforms);
}