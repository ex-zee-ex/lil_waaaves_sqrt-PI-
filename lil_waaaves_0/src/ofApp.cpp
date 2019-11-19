/*
 re the midi biz
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */






/*thanks to ed tannenbaum for help in fixing up the framebuffer code!*/










//so what is going to be added in here
//try out the new hsb controls for the framebuffers and also test with the other channels
//how many shader runs can we do?  curious if it will be feasible to do seperate shader runs for all of the vertex displacements but i think that it would be a good goal to have in terms of making a universial function for that to reuse as much as possible!  plus a goal is to test how many shader passes i can run before noticing slowdown!





#include "ofApp.h"


#include <iostream>

ofPolyline tetrahedron;
ofPolyline pnt_line;

float aa=0.0;
float ss=0.0;
float dd=0.0;
float ff=0.0;
float xw=1.01;
float yw=1.01;
float jj=1;
float kk=1;
float ll=.05;

float qq=0;
float ee=0;

float oo=1.0;
int ii=1;

float gg=0;
float hh=0;

float theta=0;

float movex=0;

float frequency=0;


float amp=0;




float scale1=1;
float scale2=1;

//vidmixer variables
float scale=.5;

float tt=0;

//framebuffer buffer variables  fbob-->framebufferobjectbuffer

//int framecount=0;
//const int fbob=15;


//int compScale=2;


int framedelayoffset=0;  // this is used as an index to the circular framebuffers eeettt
unsigned int framecount=0; // framecounter used to calc offset eeettt


//i got this up to 240 frames with steady on my computer, is a bit skewed extreme for real time video
//executions tho
const int fbob=60; // number of "framedelay" buffers eeettt
//int dd=fbob;
//this buffers the framebuffers from the final screen draws

//this buffers the framebuffers from the final screen draws
ofFbo pastFrames[fbob];

ofFbo pastFrames_comp[fbob];
//ofFbo is the openframeworks framebuffer object
//this line is declaring an array of framebuffer objects
//many c++ afficionados prefer a c++ vector object instead of arrays every time
//because c++ vectors are like arrays but with some handier ways to access and add and delete contents
//but on the other hand vectors can have dynamic lengths and one can really end up in some
//trouble with dynamically working with framebuffers bc its generally best pratice to allocate
//memory on the gpu for all of yr framebuffers before yr code runs, trying to mess with that on
//the fly could have some interesting appeal to a glitch art style but is not going to please
//others

void incIndex()  // call this every frame to calc the offset eeettt
{
    
    framecount++;
    framedelayoffset=framecount % fbob;
}

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetFrameRate(30);
   // ofDisableAlphaBlending();
    //ofSetVerticalSync(FALSE);
    
    //syphon input
    
    //mClient.set("","Black Syphon");
    mClient.setup();
    //mClient.set("","Syphoner");
 //  mClient.set("","Black Syphon");
    
    mClient.set("","Syphoner");

    
    
    //syphonoutput
    mainOutputSyphonServer.setName("LIL_WAAAVES");
    
    
    
    
   
    
	ofSetVerticalSync(true);
	ofBackground(0);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    

    
    
    /**shaderobiz***/
  //  ofSetDataPathRoot("../Resources/data/");
#ifdef TARGET_OPENGLES

#else
    if(ofIsGLProgrammableRenderer()){
    
    }else{
   
        shader_mixer.load("shadersGL2/shader_mixer");
        shader_blur.load("shadersGL2/shader_blur");
        shader_sharpen.load("shadersGL2/shader_sharpen");
        
        //shader_displace.load("shadersGL2/shader_displace");
    }
#endif
    
   
    
 
    fbo_draw.allocate(ofGetWidth(), ofGetHeight());
    fbo_feedback.allocate(ofGetWidth(), ofGetHeight());
    syphonTexture.allocate(ofGetWidth(), ofGetHeight());
    fbo_blur.allocate(ofGetWidth(), ofGetHeight());
  
    /*
    fbo_draw.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo_feedback.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    syphonTexture.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo_blur.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    */
    fbo_feedback.begin();

    ofClear(0,0,0,255);
 
       fbo_feedback.end();
    
    fbo_draw.begin();
    ofClear(0,0,0,255);
    fbo_draw.end();
    
    fbo_blur.begin();
    ofClear(0,0,0,255);
    fbo_blur.end();
    
  
    
    
    //allocate and clear the variable delay final draw buffers
    //full resolution version
    
    for(int i=0;i<fbob;i++){
        
        pastFrames[i].allocate(ofGetWidth(), ofGetHeight());
        
     //   pastFrames[i].allocate(ofGetScreenWidth(), ofGetScreenHeight());
        pastFrames[i].begin();
        ofClear(0,0,0,255);
        pastFrames[i].end();
        
    
    }//endifor
    
    
    
    
    
    
    
    
    
    
   
    
    //compressed by reducing the pixels by 1/4
    /*
    for(int i=0;i<fbob;i++){
        
        pastFrames_comp[i].allocate(ofGetWidth()/2, ofGetHeight()/2);
        pastFrames_comp[i].begin();
        ofClear(0,0,0,255);
        pastFrames_comp[i].end();
        
        
    }//endifor
    */
    
    
    //camerabiz
    //if u are having low framerates u can try lower resolution grabs
    //or if its all going smooth and u want to try higher resolutions here is where to fuck with that
    
    //add some optional UI interactivity with these
    //like a incrementer that cycles thru integers mod the lenght of the device list for selecting inputs cameras
    cam1.listDevices();
    cam1.setVerbose(true);
    cam1.setDeviceID(0);
     //cam1.initGrabber(1280, 960);
   cam1.initGrabber(640, 480);
   // cam1.initGrabber(320, 240);
    
  
    
    

    //setting up a tetrahedron
    
    ofVec3f tri1;
    ofVec3f tri2;
    ofVec3f tri3;
    ofVec3f tri4;
    tri1.set(1,1,1);
    tri2.set(-1,-1,1);
    tri3.set(-1,1,-1);
    tri4.set(1,-1,-1);
    float shapeScale=ofGetWidth()/8;
    
    tri1=tri1*shapeScale;
    tri2=tri2*shapeScale;
    tri3=tri3*shapeScale;
    tri4=tri4*shapeScale;
    
    
    tetrahedron.lineTo(tri1);
    tetrahedron.lineTo(tri2);
    tetrahedron.lineTo(tri4);
    tetrahedron.lineTo(tri1);
    tetrahedron.lineTo(tri3);
    tetrahedron.lineTo(tri2);
    tetrahedron.lineTo(tri3);
    tetrahedron.lineTo(tri4);
    //tetrahedron.lineTo(tri4);
    
    
    
    
   

    
}


//--------------------------------------------------------------
void ofApp::update() {
    
    //only update if active set a test for that too
    
    
    
    
    cam1.update();
 
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    

   
 
    
    /***shaderbix**/
    
    
    //first draw the syphon input to a framebuffer to have it available as a texture to send to the mixer
    syphonTexture.begin();
    //fix some auto scaling stuffs in general
  //  int syphonscale=mClient.getWidth()/cam1.getWidth();
    
    mClient.draw(0,0,(gui->syphon_scale)*mClient.getWidth(),(gui->syphon_scale)*mClient.getHeight());
    
    syphonTexture.end();
    
 
   
    
    
    
    
    
    
    
    ///draw to the buffers
    
    
   
    
    
    
    
    fbo_draw.begin();
    
    
    //try putting graphics up here instead and see if then we can key into opaqueness
    
    
    
    
    
    
    shader_mixer.begin();
    
    
    
    
    
   
    
    shader_mixer.setUniform1f("width", ofGetWidth());
    
    shader_mixer.setUniform1f("height", ofGetHeight());

    shader_mixer.setUniform1f("cam1_scale", gui->cam1_scale);
   
   
    
  
    
   
    
    
    //fb0
    ofVec3f hsb_x;
    hsb_x.set(gui->fb0_hue/10,gui->fb0_saturation/10,gui->fb0_bright/10);
   // hsb_x.set(1,1,1);
    shader_mixer.setUniform3f("fb0_hsb_x",hsb_x);
    
    ofVec3f hue_x;
    hue_x.set(gui->fb0_huex_mod/10,gui->fb0_huex_offset/10,gui->fb0_huex_lfo/10);
    shader_mixer.setUniform3f("fb0_hue_x",hue_x);
    
    ofVec3f fb_rescale;
    fb_rescale.set(gui->fb0_x_displace,gui->fb0_y_displace,gui->fb0_z_displace/100);
    shader_mixer.setUniform3f("fb0_rescale",fb_rescale);
    
    ofVec3f fb_modswitch;
    fb_modswitch.set(gui->fb0_hue_invert,gui->fb0_saturation_invert,gui->fb0_bright_invert);
    
    //fb_modswitch.set(1.0,1.0,1.0);
    shader_mixer.setUniform3f("fb0_modswitch",fb_modswitch);
    
    shader_mixer.setUniform1f("fb0_rotate",(gui->fb0_rotate)/100);
    
  //fb1
    hsb_x.set(gui->fb1_hue/10,gui->fb1_saturation/10,gui->fb1_bright/10);
    // hsb_x.set(1,1,1);
    shader_mixer.setUniform3f("fb1_hsb_x",hsb_x);
    
    
    hue_x.set(gui->fb1_huex_mod/10,gui->fb1_huex_offset/10,gui->fb1_huex_lfo/10);
    shader_mixer.setUniform3f("fb1_hue_x",hue_x);
    

    fb_rescale.set(gui->fb1_x_displace,gui->fb1_y_displace,gui->fb1_z_displace/100);
    shader_mixer.setUniform3f("fb1_rescale",fb_rescale);
    
    
    
   // ofVec3f fb_modswitch;
    fb_modswitch.set(gui->fb1_hue_invert,gui->fb1_saturation_invert,gui->fb1_bright_invert);
    
    //fb_modswitch.set(1.0,1.0,1.0);
    shader_mixer.setUniform3f("fb1_modswitch",fb_modswitch);
    shader_mixer.setUniform1f("fb1_rotate",(gui->fb1_rotate)/100);
    
    
    
   
    
   
    
    shader_mixer.setUniform1f("ee",ee);
    
    
    //here is where controls from the gui get shunted
    
    //for now channel 1 and 2 can only b cam1 or cam2 input
    shader_mixer.setUniform1i("channel1", gui->channel1);
  
   
    
    
    
    
    
    
    
    
    
    
    //h and v flip controls
   
  
    
    //channel1 controls from the gui
    //vector these up
    ///asuming these will all stay
    
    shader_mixer.setUniform1f("channel1bright_x", gui->channel1bright);
    shader_mixer.setUniform1f("channel1hue_x", gui->channel1hue);
    shader_mixer.setUniform1f("channel1saturation_x", gui->channel1saturation);
    
    
    
    shader_mixer.setUniform1i("channel1satwrap", gui->channel1satwrap);
    shader_mixer.setUniform1i("channel1brightwrap", gui->channel1brightwrap);
    
    
    shader_mixer.setUniform1i("ch1hue_powmaptoggle", gui->ch1hue_powmaptoggle);
    shader_mixer.setUniform1i("ch1sat_powmaptoggle", gui->ch1sat_powmaptoggle);
    shader_mixer.setUniform1i("ch1bright_powmaptoggle", gui->ch1bright_powmaptoggle);
    
 
    
    
    shader_mixer.setUniform1f("channel1bright_powmap", gui->channel1brightpowmap);
    shader_mixer.setUniform1f("channel1hue_powmap", gui->channel1huepowmap);
    shader_mixer.setUniform1f("channel1sat_powmap", gui->channel1saturationpowmap);
    
  
   
    
    
    
    
    
    
  
    
    
    
    
    
    
   
    
    shader_mixer.setUniform2f("cam1dimensions",ofVec2f(cam1.getWidth(),cam1.getHeight()));
    
    
    
    
    
    
    shader_mixer.setUniform1f("fb0blend", gui->fb0blend);
    shader_mixer.setUniform1f("fb0lumakeyvalue", gui->fb0lumakeyvalue);
    shader_mixer.setUniform1f("fb0lumakeythresh", gui->fb0lumakeythresh);
    shader_mixer.setUniform1i("fb0mix", gui->FBmix);
    
    shader_mixer.setUniform1f("fb1blend", gui->fb1blend);
    shader_mixer.setUniform1f("fb1lumakeyvalue", gui->fb1lumakeyvalue);
    shader_mixer.setUniform1f("fb1lumakeythresh", gui->fb1lumakeythresh);
    shader_mixer.setUniform1i("fb1mix", gui->FB1mix);
    
    
   
    
    
   //h and v flips
    shader_mixer.setUniform1i("cam1_hflip_switch", gui->cam1_hflip_switch);
    shader_mixer.setUniform1i("cam1_vflip_switch", gui->cam1_vflip_switch);
   
    shader_mixer.setUniform1i("fb0_hflip_switch", gui->fb0_hflip_switch);
    shader_mixer.setUniform1i("fb0_vflip_switch", gui->fb0_vflip_switch);
    shader_mixer.setUniform1i("fb1_hflip_switch", gui->fb1_hflip_switch);
    shader_mixer.setUniform1i("fb1_vflip_switch", gui->fb1_vflip_switch);
   
    
    
    
    
    //pixelations
    
    //cam1
    shader_mixer.setUniform1i("cam1_pixel_switch",gui->cam1_pixel_switch);
    shader_mixer.setUniform1i("cam1_pixel_scale",gui->cam1_pixel_scale);
    shader_mixer.setUniform1f("cam1_pixel_mix",gui->cam1_pixel_mix);
    shader_mixer.setUniform1f("cam1_pixel_brightscale",gui->cam1_pixel_brightscale);
    
   
    
    //fb0
    shader_mixer.setUniform1i("fb0_pixel_switch",gui->fb0_pixel_switch);
    shader_mixer.setUniform1i("fb0_pixel_scale",gui->fb0_pixel_scale);
    shader_mixer.setUniform1f("fb0_pixel_mix",gui->fb0_pixel_mix);
    shader_mixer.setUniform1f("fb0_pixel_brightscale",gui->fb0_pixel_brightscale);
    //fb1
    shader_mixer.setUniform1i("fb1_pixel_switch",gui->fb1_pixel_switch);
    shader_mixer.setUniform1i("fb1_pixel_scale",gui->fb1_pixel_scale);
    shader_mixer.setUniform1f("fb1_pixel_mix",gui->fb1_pixel_mix);
    shader_mixer.setUniform1f("fb1_pixel_brightscale",gui->fb1_pixel_brightscale);
    
   
    
    
    
    //--------------------------send the textures
    
    
    //this gets bound to tex0 when u do this way
    //some sort of canvas needs to be drawn to start with
    //so what i need to do is to just draw a rect i think but i should double check that that does not get drawn as a texture
    //otherwise i think the thing to do here is to replace this with the camera draw and then replace cam1 with tex0
    //in the shadercode and then that will reduce the amount of total gpu consumption bc less textures are involved
    fbo_feedback.draw(0,0);
  
    shader_mixer.setUniformTexture("syphon",syphonTexture.getTexture(),1);
    shader_mixer.setUniformTexture("cam1",cam1.getTexture(),2);
   
    
    
 
 
    
   

    
     shader_mixer.setUniformTexture("fb0",pastFrames[(abs(framedelayoffset-fbob-gui->fb0delayamnt)-1)%fbob].getTexture(),4);
    shader_mixer.setUniformTexture("fb1",pastFrames[(abs(framedelayoffset-fbob-gui->fb1delayamnt)-1)%fbob].getTexture(),5);
   
    
  
    
   
    
    
    
       
    
  
    
    
   
    
   
    shader_mixer.setUniform1f("qq",qq);
    
    shader_mixer.end();
    
	
   
    
    

    //just drawing a little rotating tetrahedron
    
    if(gui->tetrahedron_switch==1){
    
    ofSetColor(127+127*(sin(ofGetElapsedTimef())),127+127*(cos(ofGetElapsedTimef()/7)),127-127*(sin(ofGetElapsedTimef()/19)),255);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofRotateZRad(ofGetElapsedTimef()/5);
    ofRotateYRad(ofGetElapsedTimef()/13);
    ofRotateXRad(ofGetElapsedTimef()/11);
    tetrahedron.draw();
    
    
   
    ofPopMatrix();
    }
    

    
  
    
 
    
    fbo_draw.end();
    
    //----------------------------------------------------------
    
    
    
    //sharpen and blur the composited image before it is drawn to screens and buffers
    
    fbo_blur.begin();
    
  
    
    
    
    shader_blur.begin();
    
    fbo_draw.draw(0,0);
    shader_blur.setUniform1f("blurAmnt",gui->blur_amount);
    shader_blur.end();
    
    
    fbo_blur.end();
    
    
    
    fbo_draw.begin();
    
   
     
     
    //so add a radius and chi variable to this
    //then figure out how to switch on and off and route properly
   
    shader_sharpen.begin();
    fbo_blur.draw(0,0);
    shader_sharpen.setUniform1f("sharpAmnt",gui->sharpen_amount);
    shader_sharpen.end();
   
    
    //fbo_blur.draw(0,0);
    
    fbo_draw.end();
    
    
    //___--_------___-_-_______-----___-
    
    /*this part gets drawn to screen*/
    ofSetColor(ofColor::white);
    
    ofPushMatrix();
    //add seperate switchs for this and fbo
    ofTranslate(ofGetWidth()/2.0,ofGetHeight()/2.0);
    
   // ofRotateZRad(oo*TWO_PI/ii);
    //looks like there needds to be seperate rotations for camera stuff and framebuffer stuffs
    ofTranslate(0,0,0);
    fbo_draw.draw(-ofGetWidth()/2.0,-ofGetHeight()/2.0);
    ofPopMatrix();
    //audiovisualizer biz
    
   
    
    
     
     
    
 
 
  
    
    
    
   

   
    
    
    
  
    
    
    
    //feed the previous frame into position 0 (index0)
    
    pastFrames[abs(fbob-framedelayoffset)-1].begin(); //eeettt
    
    
    ofPushMatrix();
  
    //recenter the coordinates so 0,0 is at the center of the screen
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
   
    //  ofRotateZRad(.01);
    ofTranslate(ff,gg,hh);
    ofRotateYRad(ss);
    ofRotateXRad(aa);
    ofRotateZRad(dd);
     ofRotateZRad(oo*TWO_PI/ii);
   
    
    fbo_draw.draw(-ofGetWidth()/2,-ofGetHeight()/2);
   
    ofPopMatrix();
    
    
    pastFrames[abs(fbob-framedelayoffset)-1].end(); //eeettt
    //-----____---____---__-__---____-----_--_-
    
    
    
    
   
    
    
    
    
    
    
    
    
    
    
    
    
   
  
    
    int ofappchannel1= gui->channel1;
    
    
 
    
    ofSetHexColor(0xFFFFFF);
 
    
    
    
    //add a switch for this
    if(gui->syphonOutput==1){
    mainOutputSyphonServer.publishScreen();
    }
    
    incIndex(); // increment framecount and framedelayoffset eeettt
}


 
 /****************************************************/



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='3'){
        aa=ss=dd=ff=gg=hh=0;
    }
    
   
    
    if(key=='2'){
          loop.play();
    }
    
 
    if(key=='1'){
        for(int i=0;i<fbob;i++){
            pastFrames[i].begin();
        
            ofClear(0,0,0,255);
        
            pastFrames[i].end();
        }
        
        fbo_draw.begin();
        ofClear(0,0,0,255);
        fbo_draw.end();
    }
    //if(key=='q'){sw1==0;}
    
    if(key=='a'){aa+=0.0001;}
    if(key=='z'){aa-=0.0001;}
    if(key=='s'){ss+=0.0001;}
    if(key=='x'){ss-=0.0001;}
    
    if(key=='d'){dd+=0.0001;}
    if(key=='c'){dd-=0.0001;}
    
    if(key=='f'){ff+=0.0001;}
    if(key=='v'){ff-=0.0001;}
    
    if(key=='g'){gg+=0.0001;}
    if(key=='b'){gg-=0.0001;}
    if(key=='h'){hh+=0.01;}
    if(key=='n'){hh-=0.01;}
    
    
    if(key=='j'){jj+=0.1;}
    if(key=='m'){jj-=0.1;}
    if(key=='k'){kk+=0.1;}
    if(key==','){kk-=0.1;}
    
   
    
    if(key==';'){scale1+=0.01;}
    if(key=='/'){scale1-=0.01;}
    
    if(key=='['){scale2+=0.01;}
    if(key==']'){scale2-=0.01;}
    
    if(key=='q'){qq+=0.001;cout << "qq"<<qq<< endl;}
    if(key=='w'){qq-=0.001;cout << "qq"<<qq<< endl;}
    if(key=='e'){ee+=.1;cout << "ee"<<ee<< endl;}
    if(key=='r'){ee-=.1;cout << "ee"<<ee<< endl;}
    
    
    if(key=='u'){ii+=1;}
    if(key=='i'){ii-=1;}
    if(key=='o'){oo+=.1;}
    if(key=='p'){oo-=.1;}
    
    if(key=='t'){tt+=.01;}
    if(key=='y'){tt-=.01;}
    
    
    if(key=='2'){amp+=.001;}
    if(key=='3'){amp-=.001;}
    


}

/************************/
//--------------------------------------------------------------
void ofApp::exit() {
	
	
}



//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
   
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
