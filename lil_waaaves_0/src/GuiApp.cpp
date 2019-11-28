/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"


int fbob=60;

int guiscale=275;

void GuiApp::setup(){
    
    ofBackground(0);
    
    guisignal = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    guisignal->addFRM();
    guisignal->addBreak();
    
    guisignal->addTextInput("Signal Flow", "# open frameworks #");
    vector<string> channel1options ={"channel1 none","channel1 cam1","channel1 syphon"};
  
 
    guisignal->addDropdown("SELECT A camera", channel1options);
   
  
    vector<string> FBmixoptions ={"FB none","FB blend","FB key"};
    vector<string> FB1mixoptions ={"FB1 none","FB1 blend","FB1 key"};
    
 
    
   
    
    
    
    
  

   
    
   
    
    
    
    ///FBmixcontrols
    guisignal->addDropdown("FB0_mixoptions", FBmixoptions);
    ofxDatGuiFolder* fb0mix_thingsfolder = guisignal->addFolder("FB0mixthings", ofColor::white);
    
    fb0blendslider=fb0mix_thingsfolder->addSlider("mix amnt",-5.0,5.0);
    fb0brightkeyamountslider=fb0mix_thingsfolder->addSlider("luma key V",0.00,1.00);
    fb0brightkeythreshslider=fb0mix_thingsfolder->addSlider("luma key T",0.00,1.00);
    
    
    
    fb0brightkeyamountslider->bind(fb0lumakeyvalue);
    fb0brightkeythreshslider->bind(fb0lumakeythresh);
    fb0delayamountslider=fb0mix_thingsfolder->addSlider("fb0 delay amnt",0,fbob-1);
    
    fb0blendslider->bind(fb0blend);
  
    fb0delayamountslider->bind(fb0delayamnt);
    
    fb0_hflip_toggle=fb0mix_thingsfolder->addToggle("fb0 h mirror",false);
    fb0_vflip_toggle=fb0mix_thingsfolder->addToggle("fb0 v mirror",false);
    
    

    
    
    
   
    ///FB1mixcontrol
    guisignal->addDropdown("FB1_mixoptions", FB1mixoptions);
    ofxDatGuiFolder* fb1mix_thingsfolder = guisignal->addFolder("FB1mixthings", ofColor::white);
    
    fb1blendslider=fb1mix_thingsfolder->addSlider("mix amnt",-5.0,5.0);
    fb1brightkeyamountslider=fb1mix_thingsfolder->addSlider("luma key V",0.00,1.00);
    fb1brightkeythreshslider=fb1mix_thingsfolder->addSlider("luma key T",0.00,1.00);
    
    fb1brightkeyamountslider->bind(fb1lumakeyvalue);
    fb1brightkeythreshslider->bind(fb1lumakeythresh);
    
    fb1blendslider->bind(fb1blend);
    
    fb1delayamountslider=fb1mix_thingsfolder->addSlider("fb1 delay amnt",0,fbob-1);
    
    fb1delayamountslider->bind(fb1delayamnt);
    
    fb1_hflip_toggle=fb1mix_thingsfolder->addToggle("fb1 h mirror",false);
    fb1_vflip_toggle=fb1mix_thingsfolder->addToggle("fb1 v mirror",false);


    
  

    
    
   

    
    
  
    
    blur_amount_slider=guisignal->addSlider("blur amount",0.0,5.0);
    blur_amount_slider->bind(blur_amount);
    
    sharpen_amount_slider=guisignal->addSlider("sharpen amount",0.0,.3);
    sharpen_amount_slider->bind(sharpen_amount);

    
    cam1_scale_slider=guisignal->addSlider("cam1 scale",0,2);
    cam1_scale_slider->bind(cam1_scale);
    
    syphon_scale_slider=guisignal->addSlider("syphon scale",0,2);
    syphon_scale_slider->bind(syphon_scale);
  
    
    
    cam1_hflip_toggle=guisignal->addToggle("cam1 h mirror",false);
    cam1_vflip_toggle=guisignal->addToggle("cam1 v mirror",false);
    

    syphonOutputtoggle=guisignal->addToggle("syphon out",false);
    tetrahedron_switch_toggle=guisignal->addToggle("tetrahedron",false);
    guisignal->onDropdownEvent(this, &GuiApp::onDropdownEvent);
    //guisignal->onColorPickerEvent(this, &GuiApp::onColorPickerEvent);
    
    //registertolistentoevents
    guisignal->onButtonEvent(this, &GuiApp::onButtonEvent);
    
    
    
    
    ///-----------------------------------
    guithings = new ofxDatGui(guiscale,0 );//ofxDatGuiAnchor::TOP_RIGHT );
    guithings->addBreak();
    
    
    
    
    
    
    //channel1 hsb manipulation strip
    ofxDatGuiFolder* channel1_thingsfolder = guithings->addFolder("channel1things", ofColor::white);
    
    channel1hueslider= channel1_thingsfolder->addSlider("ch1hue ", -5.0, 5.0);
    channel1saturationslider= channel1_thingsfolder->addSlider("ch1saturation ", -5.0, 5.0);
    channel1brightslider= channel1_thingsfolder->addSlider("ch1brightness ", -5.0, 5.0);
    
    
   
    channel1satwraptoggle=channel1_thingsfolder->addToggle("ch1satwrap",false);
    channel1brightwraptoggle=channel1_thingsfolder->addToggle("ch1brightwrap",false);
    
    channel1huepowmaptoggle=channel1_thingsfolder->addToggle("ch1huepowmap",false);
    channel1satpowmaptoggle=channel1_thingsfolder->addToggle("ch1satpowmap",false);
    channel1brightpowmaptoggle=channel1_thingsfolder->addToggle("ch1brightpowmap",false);
    
    channel1huepowmapslider= channel1_thingsfolder->addSlider("ch1huepowmap", -4.0, 4.0);
    channel1saturationpowmapslider= channel1_thingsfolder->addSlider("ch1satpowmap", -4.0, 4.0);
    channel1brightpowmapslider= channel1_thingsfolder->addSlider("ch1brightpowmap", -4.0, 4.0);
    
  
   // channel1_thingsfolder->expand();
    
    
    
    
  

    
    
    
 
    

    
    
    //bind the gui channel1
    channel1hueslider->bind(channel1hue);
    channel1saturationslider->bind(channel1saturation);
    channel1brightslider->bind(channel1bright);
    
    channel1huepowmapslider->bind(channel1huepowmap);
    channel1saturationpowmapslider->bind(channel1saturationpowmap);
    channel1brightpowmapslider->bind(channel1brightpowmap);
    
  
    
    //fb0
    ofxDatGuiFolder* fb0_opsfolder = guithings->addFolder("fb0ops", ofColor::white);
    fb0_hue_slider= fb0_opsfolder->addSlider("hue_x ", 0.0, 20.0);
    fb0_saturation_slider= fb0_opsfolder->addSlider("sat_x ", 0.0, 20.0);
    fb0_bright_slider= fb0_opsfolder->addSlider("bright_x", 0.0, 20.0);
    
    fb0_hue_invert_toggle=fb0_opsfolder->addToggle("hue0 invert",0);
    fb0_saturation_invert_toggle=fb0_opsfolder->addToggle("saturationg0 invert",0);
    fb0_bright_invert_toggle=fb0_opsfolder->addToggle("bright0 invert",0);
    
    fb0_huex_mod_slider= fb0_opsfolder->addSlider("huex_mod", 0.0, 20.0);
    fb0_huex_offset_slider= fb0_opsfolder->addSlider("huex_offset", -20.0, 20.0);
    fb0_huex_lfo_slider= fb0_opsfolder->addSlider("huex_lfo", -20.0, 20.0);
    
    fb0_x_displace_slider= fb0_opsfolder->addSlider("x_displace", -20.0, 20.0);
    fb0_y_displace_slider= fb0_opsfolder->addSlider("y_displace", -20.0, 20.0);
    fb0_z_displace_slider= fb0_opsfolder->addSlider("z_displace", 90, 110.0);
    fb0_rotate_slider=fb0_opsfolder->addSlider("rotate", -157.07, 157.07);
    
    
    
    fb0_hue_slider->bind(fb0_hue);
    fb0_saturation_slider->bind(fb0_saturation);
    fb0_bright_slider->bind(fb0_bright);
    fb0_huex_mod_slider->bind(fb0_huex_mod);
    fb0_huex_offset_slider->bind(fb0_huex_offset);
    fb0_huex_lfo_slider->bind(fb0_huex_lfo);
    fb0_x_displace_slider->bind(fb0_x_displace);
    fb0_y_displace_slider->bind(fb0_y_displace);
    fb0_z_displace_slider->bind(fb0_z_displace);
    fb0_rotate_slider->bind(fb0_rotate);
    
    //fb1
    ofxDatGuiFolder* fb1_opsfolder = guithings->addFolder("fb1ops", ofColor::white);
    fb1_hue_slider= fb1_opsfolder->addSlider("hue_x ", 0.0, 20.0);
    fb1_saturation_slider= fb1_opsfolder->addSlider("sat_x ", 0.0, 20.0);
    fb1_bright_slider= fb1_opsfolder->addSlider("bright_x", 0.0, 20.0);
    
    fb1_hue_invert_toggle=fb1_opsfolder->addToggle("hue1 invert",0);
    fb1_saturation_invert_toggle=fb1_opsfolder->addToggle("saturationg1 invert",0);
    fb1_bright_invert_toggle=fb1_opsfolder->addToggle("bright1 invert",0);
    
    fb1_huex_mod_slider= fb1_opsfolder->addSlider("huex_mod", 0.0, 20.0);
    fb1_huex_offset_slider= fb1_opsfolder->addSlider("huex_offset", -20.0, 20.0);
    fb1_huex_lfo_slider= fb1_opsfolder->addSlider("huex_lfo", -20.0, 20.0);
    
    fb1_x_displace_slider= fb1_opsfolder->addSlider("x_displace", -20.0, 20.0);
    fb1_y_displace_slider= fb1_opsfolder->addSlider("y_displace", -20.0, 20.0);
    fb1_z_displace_slider= fb1_opsfolder->addSlider("z_displace", 90, 110);
    fb1_rotate_slider=fb1_opsfolder->addSlider("rotate", -157.07, 157.07);
    
    
    
    fb1_hue_slider->bind(fb1_hue);
    fb1_saturation_slider->bind(fb1_saturation);
    fb1_bright_slider->bind(fb1_bright);
    fb1_huex_mod_slider->bind(fb1_huex_mod);
    fb1_huex_offset_slider->bind(fb1_huex_offset);
    fb1_huex_lfo_slider->bind(fb1_huex_lfo);
    fb1_x_displace_slider->bind(fb1_x_displace);
    fb1_y_displace_slider->bind(fb1_y_displace);
    fb1_z_displace_slider->bind(fb1_z_displace);
    fb1_rotate_slider->bind(fb1_rotate);
    
    
    //cam1
    ofxDatGuiFolder* cam1_pixelfolder = guithings->addFolder("cam1 pixelate", ofColor::white);
    cam1_pixel_toggle=cam1_pixelfolder->addToggle("cam1 pixel switch",0);
    cam1_pixel_scale_slider=cam1_pixelfolder->addSlider("quantisation",0,256);
    cam1_pixel_mix_slider=cam1_pixelfolder->addSlider("mix",-2,2);
    cam1_pixel_brightscale_slider=cam1_pixelfolder->addSlider("bright scale",-10,10);
    
    
    cam1_pixel_scale_slider->bind(cam1_pixel_scale);
    cam1_pixel_mix_slider->bind(cam1_pixel_mix);
    cam1_pixel_brightscale_slider->bind(cam1_pixel_brightscale);
    
    
    
    
    
    
    //fb0
    ofxDatGuiFolder* fb0_pixelfolder = guithings->addFolder("fb0 pixelate", ofColor::white);
    fb0_pixel_toggle=fb0_pixelfolder->addToggle("fb0 pixel switch",0);
    fb0_pixel_scale_slider=fb0_pixelfolder->addSlider("quantisation",0,256);
    fb0_pixel_mix_slider=fb0_pixelfolder->addSlider("mix",-2,2);
    fb0_pixel_brightscale_slider=fb0_pixelfolder->addSlider("bright scale",-10,10);
    
    
    fb0_pixel_scale_slider->bind(fb0_pixel_scale);
    fb0_pixel_mix_slider->bind(fb0_pixel_mix);
    fb0_pixel_brightscale_slider->bind(fb0_pixel_brightscale);
    
    //fb1
    ofxDatGuiFolder* fb1_pixelfolder = guithings->addFolder("fb1 pixelate", ofColor::white);
    fb1_pixel_toggle=fb1_pixelfolder->addToggle("fb1 pixel switch",0);
    fb1_pixel_scale_slider=fb1_pixelfolder->addSlider("quantisation",0,256);
    fb1_pixel_mix_slider=fb1_pixelfolder->addSlider("mix",-2,2);
    fb1_pixel_brightscale_slider=fb1_pixelfolder->addSlider("bright scale",-10,10);
    
    
    fb1_pixel_scale_slider->bind(fb1_pixel_scale);
    fb1_pixel_mix_slider->bind(fb1_pixel_mix);
    fb1_pixel_brightscale_slider->bind(fb1_pixel_brightscale);
    
   
    
    //registertolistentoevents
    guithings->onButtonEvent(this, &GuiApp::onButtonEvent);
    
    
    //----------------------
    //use this for how to manipulate each framebuffer in space seperatly
    //so for each one we want to have seperate vert shader controls as well
    //i think we start from there, then figure out how to replicate all those rotations and stuff
    //in more concise shader terms
    //s
   
    
  
   /*
    
    guiFBops= new ofxDatGui(2*guiscale,0 );
    guiFBops->addBreak();
    
    
    
    
  
    
    
   
    
    

 
    guiFBops->onButtonEvent(this, &GuiApp::onButtonEvent);
    
    */
    
    //pixelations functions
    
    /*
    guiPixelate= new ofxDatGui(2*guiscale,0 );
    guiPixelate->addBreak();
    
    //cam1
    ofxDatGuiFolder* cam1_pixelfolder = guiPixelate->addFolder("cam1 pixelate", ofColor::white);
    cam1_pixel_toggle=cam1_pixelfolder->addToggle("cam1 pixel switch",0);
    cam1_pixel_scale_slider=cam1_pixelfolder->addSlider("quantisation",0,256);
    cam1_pixel_mix_slider=cam1_pixelfolder->addSlider("mix",-2,2);
    cam1_pixel_brightscale_slider=cam1_pixelfolder->addSlider("bright scale",-10,10);
    
    
    cam1_pixel_scale_slider->bind(cam1_pixel_scale);
    cam1_pixel_mix_slider->bind(cam1_pixel_mix);
    cam1_pixel_brightscale_slider->bind(cam1_pixel_brightscale);
    
   
    
  
    

    //fb0
    ofxDatGuiFolder* fb0_pixelfolder = guiPixelate->addFolder("fb0 pixelate", ofColor::white);
    fb0_pixel_toggle=fb0_pixelfolder->addToggle("fb0 pixel switch",0);
    fb0_pixel_scale_slider=fb0_pixelfolder->addSlider("quantisation",0,256);
    fb0_pixel_mix_slider=fb0_pixelfolder->addSlider("mix",-2,2);
    fb0_pixel_brightscale_slider=fb0_pixelfolder->addSlider("bright scale",-10,10);


    fb0_pixel_scale_slider->bind(fb0_pixel_scale);
    fb0_pixel_mix_slider->bind(fb0_pixel_mix);
    fb0_pixel_brightscale_slider->bind(fb0_pixel_brightscale);
    
    //fb1
    ofxDatGuiFolder* fb1_pixelfolder = guiPixelate->addFolder("fb1 pixelate", ofColor::white);
    fb1_pixel_toggle=fb1_pixelfolder->addToggle("fb1 pixel switch",0);
    fb1_pixel_scale_slider=fb1_pixelfolder->addSlider("quantisation",0,256);
    fb1_pixel_mix_slider=fb1_pixelfolder->addSlider("mix",-2,2);
    fb1_pixel_brightscale_slider=fb1_pixelfolder->addSlider("bright scale",-10,10);
    
    
    fb1_pixel_scale_slider->bind(fb1_pixel_scale);
    fb1_pixel_mix_slider->bind(fb1_pixel_mix);
    fb1_pixel_brightscale_slider->bind(fb1_pixel_brightscale);
    
   
    
    
  
    
    
    
    
 
    guiPixelate->onButtonEvent(this, &GuiApp::onButtonEvent);
     
     */
    ofxDatGuiLog::quiet();
    
  }
    //-----------------------------

/*
void GuiApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "onColorPickerEvent: " << e.target->getLabel() << " " << e.target->getColor() << endl;
    ofSetBackgroundColor(e.color);
    
    
    //need to set up label based if statements here
    keyColorFromPicker=e.target->getColor();
}
 
 
 */
//another thing to thinkabout with dropdown events is
//that i could just have one dropdown event
//and seperate the same inputs from diferent dropdowns
//by like ch2_cam2 etc and then the 1 function can shunt everything
    void GuiApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
    {
        cout << "onDropdownEvent: " << e.target->getLabel() << " Selected" << endl;
        
        
        if(e.target->getLabel()=="channel1 none"){
            channel1=0;
            
        }//endife1

        
        if(e.target->getLabel()=="channel1 cam1"){
            channel1=1;
        
        }//endife1
        
      
            
    
        if(e.target->getLabel()=="channel1 syphon"){
            channel1=2;
            
        }//endife2
        
        
        
     

        
        
       
        
     
        
        if(e.target->getLabel()=="FB none"){
            FBmix=0;
        }
        
        
        
        if(e.target->getLabel()=="FB blend"){
            FBmix=1;
            
        }//endife1
        
        if(e.target->getLabel()=="FB key"){
            FBmix=2;
        }
        
        if(e.target->getLabel()=="FB1 none"){
            FB1mix=0;
        }
        
        
        if(e.target->getLabel()=="FB1 blend"){
            FB1mix=1;
            
        }//endife1
        
        if(e.target->getLabel()=="FB1 key"){
            FB1mix=2;
        }
        
      


        
     
        
       
     
      

        

    

        
        
        
        
        
        
    }


//--------------------



void GuiApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if(e.target->getLabel()=="tetrahedron"){tetrahedron_switch=!tetrahedron_switch;}
    
    
    if(e.target->getLabel()=="cam1 pixel switch"){cam1_pixel_switch=!cam1_pixel_switch;}

    
    if(e.target->getLabel()=="fb0 pixel switch"){fb0_pixel_switch=!fb0_pixel_switch;}
    
    if(e.target->getLabel()=="fb1 pixel switch"){fb1_pixel_switch=!fb1_pixel_switch;}
    
  
    if(e.target->getLabel()=="cam1 h mirror"){cam1_hflip_switch=!cam1_hflip_switch;}
    if(e.target->getLabel()=="cam1 v mirror"){cam1_vflip_switch=!cam1_vflip_switch;}
    
  
    if(e.target->getLabel()=="fb0 h mirror"){fb0_hflip_switch=!fb0_hflip_switch;}
    if(e.target->getLabel()=="fb0 v mirror"){fb0_vflip_switch=!fb0_vflip_switch;}
    
    if(e.target->getLabel()=="fb1 h mirror"){fb1_hflip_switch=!fb1_hflip_switch;}
    if(e.target->getLabel()=="fb1 v mirror"){fb1_vflip_switch=!fb1_vflip_switch;}
    
 

    
    if(e.target->getLabel()=="hue0 invert"){fb0_hue_invert=!fb0_hue_invert;}
    
    if(e.target->getLabel()=="saturationg0 invert"){fb0_saturation_invert=!fb0_saturation_invert;}
    
    if(e.target->getLabel()=="bright0 invert"){fb0_bright_invert=!fb0_bright_invert;}
    
    if(e.target->getLabel()=="hue1 invert"){fb1_hue_invert=!fb1_hue_invert;}
    
    if(e.target->getLabel()=="saturationg1 invert"){fb1_saturation_invert=!fb1_saturation_invert;}
    
    if(e.target->getLabel()=="bright1 invert"){fb1_bright_invert=!fb1_bright_invert;}
    
  
    
    

    
    
    if(e.target->getLabel() == "syphon out"){ syphonOutput=!syphonOutput;}
    
    
    
    
    
    //channel1toggles
    if(e.target->getLabel() == "ch1huepowmap"){
        ch1hue_powmaptoggle =! ch1hue_powmaptoggle;
    }
    
    if(e.target->getLabel() == "ch1satpowmap"){
        ch1sat_powmaptoggle =! ch1sat_powmaptoggle;
    }

    
    if(e.target->getLabel() == "ch1brightpowmap"){
        ch1bright_powmaptoggle =! ch1bright_powmaptoggle;
    }
    
   


    //----
    
    if(e.target->getLabel() == "ch1satwrap"){
        channel1satwrap =! channel1satwrap;
    }
    
    if(e.target->getLabel() == "ch1brightwrap"){
        channel1brightwrap =! channel1brightwrap;
    }
    
   

 
    
  
    
}

//----------------------------------
    void GuiApp::update() {
       
    }


//------------------------------
    void GuiApp::draw() {
        
        
    }


//---------------------------




