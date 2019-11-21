# lil_waaaves
a tiny version of video_waaaves with less over all functionality and flexibility but perhaps a better introduction to the structures and signal paths of working with digital feedback systems


(this is the same instructions for the full size video_waaaves program)
a video mixer, framebuffer delay, and feedback resynthesis engine built in openFrameworks https://openframeworks.cc/

![Image description](https://github.com/ex-zee-ex/VIDEO_WAAAVES_1_5/blob/master/hypercuuube.png)

requires ofxSyphon https://github.com/astellato/ofxSyphon, 
ofxMidi https://github.com/danomatika/ofxMidi, 
and ofxDatGui https://github.com/braitsch/ofxDatGui addons

for windows and linux check the noSyphon folder for alternate versions of some files to copy over into the src folder to get u up and running in syphon free zones.  although i have been told that simply installing the ofxSyphon addon will make sure the code compiles on any operating system, i still recommend following this step to optimize performance.

![Image description](https://github.com/ex-zee-ex/VIDEO_WAAAVES_1_5/blob/master/swirl.png)

if you have never used oF and/or Xcode before here are some troubleshooting tips to try before contacting me
1. the entire folder structure needs to be intact and moved into the apps/myApps folder within the openframeworks folder
2. try running project generator and importing this folder (with the abovementioned addons) if theres still errors
3. https://openframeworks.cc/setup/xcode/ has some advice on how to troubleshoot troublesome addons as well so check this out too!

![Image description](https://github.com/ex-zee-ex/VIDEO_WAAAVES_1_5/blob/master/vlcsnap-2019-08-10-22h55m38s489.png)

numereous secret keyboard commands


to rotate and shift framebuffer xyz positions a,z,s,x,d,c,f,v,g,b,h,n,t,y can all be used, the numerical key '3' resets all positions

the numerical key '1'clears the framebuffer

![Image description](https://github.com/ex-zee-ex/VIDEO_WAAAVES_1_5/blob/master/vlcsnap-2019-08-10-22h57m07s147.png)



https://youtu.be/PYapmZSiSE4 is a handy dandy video tutorial on how to get started playing around in heres!


https://vimeo.com/andreijay for many examples of this program in action.  



some notes on controls!

so i will fully admit that many of the controls are obscure and nearly occult in their nomenclature.  user experience is not my forte so any feedback is totally welcome.  either way here is a little guide to some of the more confusing controls

fb0 and fb1 both refer to channels available to mix in from the framebuffer delay line ( a 2 second long delay line consisting of the past 60 frames which have been drawn to the screen)

luma key V and luma key T refer to luma key Value (the brightness value which is keyed out) and luma key Threshold (the amount of area around the value which is also keyed out).  they work in somewhat unintuitive ways, luma key V at 0 keys out the brightest part of the input and luma key V at 1 keys out the blackest part.  for some reason the threshold thing also works inverted to how one would intuit, luma key T at 0 keys out almost the entire span from 0 to 1 around the value while luma key T at 100 keys out basically nothing.  

mix just means fading between channels. a value of 0 passes through the original channel unchanged while a value of 1 passes through only the mixed channel.  values below 0 and above 1 work in fun and unexpected ways.  often times when one ends up in a state where the screen seems to be frozen up or locked into some solid color you can try changing values of mix for each of the fb0 and fb1 to mix more of the camera or syphon inputs in to get a reset on the feedback loops.  

blur and sharpen happen downstream from all of the mixing and other processing and are fed into the feedback loops as well so they have potentially unexpected effects from the naturally artefact amplifying effects of video feedback loops.  small values of sharpen (.03 to .13 or so) will darken the total output considerably and have an edge detect effect upon fb0 and fb1 when the brightness is on full.  larger values of sharpen (.13 on up) will have a more traditional sharpening effect upon the final draw.  


in the subfolders labeled fb0ops and fb1ops are a host of controls for affecting hue, saturation, brightness, and position of the framebuffer being mixed in.  i'm still testing all of these out in terms of how they should appear and how they should scale so bear with me!  
huex, saturationx, and brightx are all scaled from 0 to 20 on the gui but the actual effects are multipying the hsb values by the numbers rescaled from 0 to 2.0.  because multiplicative attenuations like this have an exponental effect when fed into a feedback loop it can be best to start out with moving these values between 9.0 and 11.0 to see more subtle effects of what these do, larger and smaller values will have more unpredictable and chaotic effects in practice.  hue saturation and brightness invert switches multiply each channel by -1 to extend the total range of attenuation from -2 to 2.  

huex mod, hue offset, and hue lfo all are mainly intended to adjust the hue attenuation in ways that vary the behavior up from the standard hue cycling modes, some combinations of these 3 parameters along with the huex parameter can actually affect saturation and brightness as well in surprising ways.  often times if you end up in a situation where all the hue seems to dissapear and you would like to get some back it can help to slowly move huex mod around until you start to see some strobeing effects kick in.  


x displace, y displace, z displace, and rotate all affect the general location of the framebuffer in relation to the frame being redrawn.  these can have very similar effects to that of moving a camera around while it is pointed at a screen to control the shapes and speeds of feedback effects.  for slower and softer feedback patterns try x and y displace at values between -2 and 2 and z displace values between 99 and 101 (yes for some reason z displace goes from 90 to 110 with 100 being no change in z position.  its totally weird i know!).  rotate is scaled from -PI/4 to PI/4 and happens after each of the xyz displaces occur so it an be used to get spiraling effects
