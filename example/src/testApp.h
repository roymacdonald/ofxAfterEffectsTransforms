#pragma once


#include "ofMain.h"
#include "ofxAEOverlay.h"


class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
 	void keyReleased(int key);

    void reset();
    void loadOverlays();
	
	int frame;
	float fps;
	string ss;
	
	ofVideoPlayer mov;
	
    vector<ofxAEOverlay> overlays;

    ofImage imgMask;
        
};
