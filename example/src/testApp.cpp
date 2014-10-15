#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
    ofSetLogLevel(OF_LOG_ERROR);
    loadOverlays();
    
	if (mov.loadMovie("testAnimation.mov")) {//This must be the movie you rendered from AE.
        mov.setLoopState(OF_LOOP_NORMAL);
		mov.play();
	}
}
//--------------------------------------------------------------
void testApp::loadOverlays(){
    imgMask.loadImage("mask.png");//This must be the image you used as mask/placeholder in the AfterEffects animation.
    ofDirectory dir;
    dir.listDir("overlays");// this must be the folder you selected when running the AfterEffects script.
    
    for (int i =0; i < dir.size(); i++) {
        if(dir.getFile(i).isDirectory()){
            ofDirectory d;
            d.allowExt("txt");
            d.listDir(dir.getPath(i));

            overlays.push_back(ofxAEOverlay());
            
            overlays.back().setImg(imgMask);
            for (int j = 0; j < d.size(); j++) {
                overlays.back().loadKeyframes(d.getPath(j));
            }
        }
    }
}
//--------------------------------------------------------------
void testApp::reset(){
	mov.firstFrame();
	mov.play();
}
//--------------------------------------------------------------
void testApp::update(){
	if (mov.isPlaying()) {
		mov.update();
     	if (mov.isFrameNew()) {
			frame = mov.getCurrentFrame();
		}
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
    ofEnableAlphaBlending();
    mov.draw(0, 0);
    for (int i = 0; i < overlays.size(); i++) {
        overlays[i].draw(frame);
    }
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch (key) {
		case ' ':
			mov.setPaused(!mov.isPaused());
            break;
        case OF_KEY_LEFT:
            mov.setFrame(frame-1);
            break;
        case OF_KEY_RIGHT:
            mov.setFrame(frame+1);
            break;
		case  'f':
            ofToggleFullscreen();
			break;
        case 'c':
            ofHideCursor();
            break;
        case 'C':
            ofShowCursor();
            break;
		default:
			break;
	}
}
