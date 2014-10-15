//
//  alphaMasker.h
//  ofxEdsdkExample
//
//  Created by Roy Macdonald on 10/1/14.
//
//

#pragma once

#include "ofMain.h"

class alphaMasker{
public:
    
    
    ofShader    shader;
    
    void setup(){
        
        if(ofGetGLProgrammableRenderer()){
            string vertex = "#version 150\n\
            \n\
            uniform mat4 projectionMatrix;\n\
            uniform mat4 modelViewMatrix;\n\
            uniform mat4 modelViewProjectionMatrix;\n\
            \n\
            \n\
            in vec4  position;\n\
            in vec2  texcoord;\n\
            \n\
            out vec2 texCoordVarying;\n\
            \n\
            void main()\n\
            {\n\
	        texCoordVarying = texcoord;\
    		gl_Position = modelViewProjectionMatrix * position;\n\
            }";
            string fragment = "#version 150\n\
            \n\
            uniform sampler2DRect tex0;\
            uniform sampler2DRect maskTex;\
            in vec2 texCoordVarying;\n\
            \
            out vec4 fragColor;\n\
            void main (void){\
            vec2 pos = texCoordVarying;\
            \
            vec3 src = texture(tex0, pos).rgb;\
            float mask = texture(maskTex, pos).a;\
            \
            fragColor = vec4( src , mask);\
            }";
            shader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
            shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
            shader.bindDefaults();
            shader.linkProgram();
        }else{
            string shaderProgram = "#version 120\n \
            #extension GL_ARB_texture_rectangle : enable\n \
            \
            uniform sampler2DRect tex0;\
            uniform sampler2DRect maskTex;\
            \
            void main (void){\
            vec2 pos = gl_TexCoord[0].st;\
            \
            vec3 src = texture2DRect(tex0, pos).rgb;\
            float mask = texture2DRect(maskTex, pos).a;\
            \
            gl_FragColor = vec4( src , mask);\
            }";
            shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
            shader.linkProgram();
        }
        
     
        
    }
    
    //--------------------------------------------------------------
    void doMask(ofImage & srcImg, ofRectangle srcRect, ofImage & mask, ofImage & destImg){
        ofFbo       fboSrc;
        fboSrc.allocate(mask.width, mask.height);
        ofEnableAlphaBlending();
        fboSrc.begin();
        ofClear(0, 0, 0, 0);
        srcImg.draw(srcRect);
        fboSrc.end();
        ofFbo       fbo;
        fbo.allocate(mask.width, mask.height);
        ofEnableAlphaBlending();
        fbo.begin();
        ofClear(0, 0, 0, 0);
        
        
        
        shader.begin();
        shader.setUniformTexture("maskTex", mask.getTextureReference(), 1 );
        
        fboSrc.draw(0,0);
        
        shader.end();
        fbo.end();
        ofDisableAlphaBlending();

        fbo.readToPixels(destImg.getPixelsRef());
        
    }
    
  
};
