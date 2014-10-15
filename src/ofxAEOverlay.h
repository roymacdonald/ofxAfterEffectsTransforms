//
//  ofxAEOverlay.h
//
//  Created by Roy Macdonald on 9/30/14.
//
//
#pragma once

#include "ofMain.h"
#include "AETransform.h"


class ofxAEOverlay {
public:
    ofxAEOverlay(){}
    void setGuiParams(string name = "overlay");
    void draw(unsigned long frame);

    void loadKeyframes(string path);
    
    void setImg(ofImage & i);
    ofImage & getImg(){return img;}
    
    ofParameterGroup parameters;

    
protected:
    ofImage img;
    vector<AETransform> transforms;
    
    ofParameter<ofVec3f>traslateAdj, scaleAdj;
    ofParameter<float>rotationAdj;
private:
    void onTranslateAdjustChange(ofVec3f & t);
    void onScaleAdjustChange(ofVec3f & t);
    void onRotationAdjustChange(float & f);

};
