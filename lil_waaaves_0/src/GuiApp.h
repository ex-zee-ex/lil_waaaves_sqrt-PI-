#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class GuiApp : public ofBaseApp{
    
public:
public:
    void setup();
    void update();
    void draw();
  
    ofxDatGui* guisignal;
    ofxDatGui* guithings;
    
    ofxDatGui* guiFBops;
    ofxDatGui* guiPixelate;
    
    
    //syphon output switch
    ofxDatGuiToggle* syphonOutputtoggle;
    bool syphonOutput=0;
    


    
    
    //channel1 hsb control strip
    ofxDatGuiSlider* channel1brightslider;
    ofxDatGuiSlider* channel1hueslider;
    ofxDatGuiSlider* channel1saturationslider;
    
    ofxDatGuiSlider* channel1brightpowmapslider;
    ofxDatGuiSlider* channel1huepowmapslider;
    ofxDatGuiSlider* channel1saturationpowmapslider;

    
 
    ofxDatGuiButton* channel1satwraptoggle;
    ofxDatGuiButton* channel1brightwraptoggle;
    
    ofxDatGuiButton* channel1huepowmaptoggle;
    ofxDatGuiButton* channel1satpowmaptoggle;
    ofxDatGuiButton* channel1brightpowmaptoggle;
    
    ofxDatGuiButton* channel1hueinverttoggle;
    ofxDatGuiButton* channel1satinverttoggle;
    ofxDatGuiButton* channel1brightinverttoggle;

    
    
    
    
   
    
   
    
    
    
   


 
    
    
    
    ofxDatGuiDropdown* ddchannel1;
   
  
    
    
    
    //FBmixcontrolstipe
    ofxDatGuiSlider* fb0brightkeyamountslider;
    ofxDatGuiSlider* fb0brightkeythreshslider;
    ofxDatGuiSlider* fb0blendslider;
    ofxDatGuiSlider* fb0delayamountslider;
    
    ofxDatGuiButton* fb0_hflip_toggle;
    ofxDatGuiButton* fb0_vflip_toggle;
    
    ofxDatGuiSlider* fb1brightkeyamountslider;
    ofxDatGuiSlider* fb1brightkeythreshslider;
    ofxDatGuiSlider* fb1blendslider;
    ofxDatGuiSlider* fb1delayamountslider;
    
    ofxDatGuiButton* fb1_hflip_toggle;
    ofxDatGuiButton* fb1_vflip_toggle;
    
  

    
    
    //vertex displacement controls
    
    
    //blur and sharpen controls
    ofxDatGuiSlider* blur_amount_slider;
    ofxDatGuiSlider* sharpen_amount_slider;
    
    
    

    //fbop controls
    ofxDatGuiSlider* fb0_hue_slider;
    ofxDatGuiSlider* fb0_saturation_slider;
    ofxDatGuiSlider* fb0_bright_slider;
    
    ofxDatGuiSlider* fb0_huex_mod_slider;
    ofxDatGuiSlider* fb0_huex_offset_slider;
    ofxDatGuiSlider* fb0_huex_lfo_slider;
    
    ofxDatGuiSlider* fb0_x_displace_slider;
    ofxDatGuiSlider* fb0_y_displace_slider;
    ofxDatGuiSlider* fb0_z_displace_slider;
    
    ofxDatGuiButton* fb0_hue_invert_toggle;
    ofxDatGuiButton* fb0_saturation_invert_toggle;
    ofxDatGuiButton* fb0_bright_invert_toggle;
    
    
    //fb1
    ofxDatGuiSlider* fb1_hue_slider;
    ofxDatGuiSlider* fb1_saturation_slider;
    ofxDatGuiSlider* fb1_bright_slider;
    
    ofxDatGuiSlider* fb1_huex_mod_slider;
    ofxDatGuiSlider* fb1_huex_offset_slider;
    ofxDatGuiSlider* fb1_huex_lfo_slider;
    
    ofxDatGuiSlider* fb1_x_displace_slider;
    ofxDatGuiSlider* fb1_y_displace_slider;
    ofxDatGuiSlider* fb1_z_displace_slider;
    
    ofxDatGuiButton* fb1_hue_invert_toggle;
    ofxDatGuiButton* fb1_saturation_invert_toggle;
    ofxDatGuiButton* fb1_bright_invert_toggle;
    
   


    //pixelations
    
    //cam1
    ofxDatGuiButton* cam1_pixel_toggle;
    ofxDatGuiSlider* cam1_pixel_scale_slider;
    ofxDatGuiSlider* cam1_pixel_mix_slider;
    ofxDatGuiSlider* cam1_pixel_brightscale_slider;
    
    bool cam1_pixel_switch=0;
    int cam1_pixel_scale=64;
    float cam1_pixel_mix=1;
    float cam1_pixel_brightscale=0;
    
   
    
    
    //fb0
    ofxDatGuiButton* fb0_pixel_toggle;
    ofxDatGuiSlider* fb0_pixel_scale_slider;
    ofxDatGuiSlider* fb0_pixel_mix_slider;
    ofxDatGuiSlider* fb0_pixel_brightscale_slider;
 
    bool fb0_pixel_switch=0;
    int fb0_pixel_scale=64;
    float fb0_pixel_mix=1;
    float fb0_pixel_brightscale=0;
    
    //fb1
    ofxDatGuiButton* fb1_pixel_toggle;
    ofxDatGuiSlider* fb1_pixel_scale_slider;
    ofxDatGuiSlider* fb1_pixel_mix_slider;
    ofxDatGuiSlider* fb1_pixel_brightscale_slider;
    
    bool fb1_pixel_switch=0;
    int fb1_pixel_scale=64;
    float fb1_pixel_mix=1;
    float fb1_pixel_brightscale=0;
    
   
    
    
    //camera and syphon rescalings
    ofxDatGuiSlider* cam1_scale_slider;
    float cam1_scale=1;
    
    ofxDatGuiSlider* syphon_scale_slider;
    float syphon_scale=1;
    
  

    
   
    
    
    //masterframebuffermixcontrolstrip
    ofxDatGuiSlider* masterframebufferdelayamountslider;
   // ofxDatGuiSlider* masterframebuffermixslider;
    
    
    
 
    
    
    //fbmixcontrolstrip
    float fb0lumakeyvalue=0.1;
    float fb0lumakeythresh=0.6;
    int fb0delayamnt=0;
    float fb0blend=.1;
    
    
    float fb1lumakeyvalue=0.1;
    float fb1lumakeythresh=0.6;
    int fb1delayamnt=0;
    float fb1blend=.1;
    
  

    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
  
    
    int channel1=1;
   
    
  
    int FBmix=0;
    int FB1mix=0;
  
    
    //h and v flip controls
    ofxDatGuiButton* cam1_hflip_toggle;
    ofxDatGuiButton* cam1_vflip_toggle;

    bool cam1_hflip_switch=0;
    bool cam1_vflip_switch=0;
    
   

    

    bool fb0_hflip_switch=0;
    bool fb0_vflip_switch=0;
    
    bool fb1_hflip_switch=0;
    bool fb1_vflip_switch=0;

  

    bool fb3_hflip_switch=0;
    bool fb3_vflip_switch=0;
    
    
    //rotations
    ofxDatGuiSlider* fb0_rotate_slider;
    float fb0_rotate=0;
    
    ofxDatGuiSlider* fb1_rotate_slider;
    float fb1_rotate=0;
    
   
   
    
   
    
    
   
    
    
    //tetrahedron switch
    ofxDatGuiButton* tetrahedron_switch_toggle;
    bool tetrahedron_switch=0;
    
  
    
       
    //blur and sharpen variables
    float blur_amount=0.0;
    float sharpen_amount=0.0;
    
    
    //fb0
    float fb0_x_displace=0.0;
    float fb0_y_displace=0.0;
    float fb0_z_displace=100.0;
  
    
    float fb0_hue=10.0;
    float fb0_saturation=10.0;
    float fb0_bright=10.0;
    
    float fb0_huex_mod=10.0;
    float fb0_huex_offset=0.0;
    float fb0_huex_lfo=0.0;
    
    bool fb0_hue_invert=0;
    bool fb0_saturation_invert=0;
    bool fb0_bright_invert=0;
    
    //fb1
    float fb1_x_displace=0.0;
    float fb1_y_displace=0.0;
    float fb1_z_displace=100.0;

    float fb1_hue=10.0;
    float fb1_saturation=10.0;
    float fb1_bright=10.0;
    
    float fb1_huex_mod=10.0;
    float fb1_huex_offset=0.0;
    float fb1_huex_lfo=0.0;
    
    bool fb1_hue_invert=0;
    bool fb1_saturation_invert=0;
    bool fb1_bright_invert=0;
    
  

    
    //channel1 variables
    float channel1bright=1.0;
    float channel1hue=1.0;
    float channel1saturation=1.0;
    
    float channel1brightpowmap=1.0;
    float channel1huepowmap=1.0;
    float channel1saturationpowmap=1.0;
    
    bool channel1satwrap=0;
    bool channel1brightwrap=0;
    
    bool ch1hue_powmaptoggle=0;
    bool ch1sat_powmaptoggle=0;
    bool ch1bright_powmaptoggle=0;
    
  
    
  
    
    
  
   
   };
