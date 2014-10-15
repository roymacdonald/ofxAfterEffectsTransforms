 //
//  AETransforms.h
//
//  Created by Roy Macdonald on 9/23/14.
//
//
#pragma once
#include "ofMain.h"
template<typename paramType>
class AEBaseProperty_{
public:
    AEBaseProperty_<paramType>(string n =""):name(n){}
    map< unsigned long, paramType>values;
    string name;
    void addProp(unsigned long time, paramType p){
        values[time] = p;
    }
    void printValues(){
        cout << "Property " << name << endl;
        for (typename map<unsigned long, paramType>::iterator it=values.begin(); it!=values.end(); ++it){
            cout << it->first << " => " << it->second << endl;
        }
    }
};
typedef AEBaseProperty_<float> AEFloatProperty;
typedef AEBaseProperty_<ofVec3f>AEVec3Property;

class AETransform{
public:
    AETransform(){
        translateAdjust.set(0);
        scaleAdjust.set(1);
        rotationAdjust = 0;
    }
    
    AEFloatProperty & addFloatProp(string name){
        floatProps[name] = AEFloatProperty(name);
        return floatProps[name];
    }
    AEVec3Property& addVecProp(string name){
        vecProps[name] = AEVec3Property(name);
        return vecProps[name];
    }
    void printProps(){
        for(map<string, AEFloatProperty>::iterator it = floatProps.begin(); it != floatProps.end(); ++it){
            it->second.printValues();
        }
        for(map<string, AEVec3Property>::iterator it = vecProps.begin(); it != vecProps.end(); ++it){
            it->second.printValues();
        }
    }
    ofVec3f * getVecPropAtFrame(string prop, unsigned int fr){
        if (vecProps.count(prop)) {
            if(vecProps[prop].values.count(fr)){
                return &vecProps[prop].values[fr];
            }else {return NULL;}
        }else{
            return NULL;
        }
    }
    float * getFloatPropAtFrame(string prop, unsigned int fr){
        if (floatProps.count(prop)) {
            if(floatProps[prop].values.count(fr)){
                return &floatProps[prop].values[fr];
            }else {return NULL;}
        }else{
            return NULL;
        }
    }
    void drawAt(unsigned long frame, ofImage & im){
            ofVec3f * p = getVecPropAtFrame("Position", frame);
            if(!p){
                return;
            }else{
                ofPushMatrix();
                ofPushStyle();
                ofTranslate(*p + translateAdjust);
            }
            float * r = getFloatPropAtFrame("Rotation", frame);
            if(r){
                ofRotate(*r + rotationAdjust);
            }
            ofVec3f * s = getVecPropAtFrame("Scale", frame);
            if(s){
                ofScale(s->x * scaleAdjust.x, s->y * scaleAdjust.y, s->z * scaleAdjust.z);
            }
            ofFill();
            float * o = getFloatPropAtFrame("Opacity", frame*2.55f);
            if (o) {
                ofSetColor(255, *o);
            }else{
                ofSetColor(255);
            }
            im.draw(0,0);
            ofPopStyle();
            ofPopMatrix();
    }
    map<string, AEFloatProperty > floatProps;
    map<string, AEVec3Property> vecProps;
    ofVec3f translateAdjust;
    ofVec3f scaleAdjust;
    float rotationAdjust;
};

static void AEreadTransformKeyframes(string path, vector<AETransform> & transforms){
    ofBuffer buffer = ofBufferFromFile(path);
    
    if(buffer.size()) {
		
        // we now keep grabbing the next line
        // until we reach the end of the file
		vector<ofVec3f> temp;
		vector<string> propiedad;
		bool bFirst = true;
		bool bl = buffer.isLastLine();
        transforms.push_back(AETransform());
        AETransform & tr = transforms.back();
        bool bPropIsFloat = false;
        bool bPropIsVec = false;
        AEVec3Property * ptrVec = NULL;
        AEFloatProperty * ptrFloat = NULL;
        string prop = "";
        while(buffer.isLastLine() == false) {
            string line = buffer.getNextLine();
            //			cout << line << endl;
			
			if(line.empty() == false) {
				
				propiedad =  ofSplitString(line, "	",true,true );
				if (propiedad.size()>1) {
					//vector<string> pp = ofSplitString(propiedad[1], " ", true, true);
					if (propiedad[0] == "Transform") {
						prop = propiedad[1];
						if (prop == "Scale" || prop == "Position") {
                            ptrVec = &tr.addVecProp(prop);
                            ptrFloat = NULL;
                            bPropIsFloat = false;
                            bPropIsVec = true;
                        }else if(prop == "Opacity" || prop == "Rotation"){
                            
                            ptrFloat = &tr.addFloatProp(prop);
                            ptrVec = NULL;
                            bPropIsVec = false;
                            bPropIsFloat = true;
                        }else{
                            ptrFloat = NULL;
                            ptrVec = NULL;
                            bPropIsVec = false;
                            bPropIsFloat = false;
                        }
					}
					else if(propiedad[0] == "Units Per Second"){
					//	fps = ofToFloat(propiedad[1]);
						//cout << "fps set to: " << fps << endl;
					}else if(propiedad[0] != "Frame"){
						//*
                        if(bPropIsFloat) {
                            if (ptrFloat != NULL) {/*
                                cout << prop << "  ";
                                for (int j = 0; j < propiedad.size(); j++) {
                                    cout << propiedad[j] << "  ";
                                }
                                cout << endl;
                                //*/
                                ptrFloat->addProp(ofToInt(propiedad[0]), ofToFloat(propiedad[1]));
                                
                            }
                        }else if(bPropIsVec){
                            ofVec3f tp;
                            for (int i = 1; i < propiedad.size() && propiedad.size() <= 4; i++) {
                                tp[i-1] = ofToFloat(propiedad[i]);
                            }
                            if (prop == "Scale") {
                                tp /=100.0f;
                            }
                            if (ptrVec != NULL) {
                                ptrVec->addProp(ofToInt(propiedad[0]), tp);
                            }
                            
                        }
						//*/
					}
					
				}
				
			}
            
			
        }
       
     //   tr.setImgPointer(&img);
       // tr.printProps();
	}
}

