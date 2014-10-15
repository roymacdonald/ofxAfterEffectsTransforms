#ofxAfterEffectsTransforms#

After you have exported the keyframes from an AfterEffects layer you can load these into your OF app and transform whatever you are drawing accordingly.
I created this because I needed to dinamically "change" certain layers from an already rendered AE animation. 
This was used at an instalation where the users where photographed automatically when anyone was standing at a certain hotspot. A simple facedetection was made and each face was extracted, cropped and masked (using a provided mask image). Then this face was overlayed to the existing animation as the face for the different characters that appeared in it.

At the same time I needed to provide a simple way for the animator to make any animation wanted and update the app without me having to interfere.


##Usage

###First, on After Effects.
You will need an image that will be your mask/placeholder for the of app and/or the placeholder in your AE animation.
Make any animation you want (so far just using 2D transforms and no camera).
The mask/placeholder image will be what will be the "replaced" in the OF app.

Once ready, select the mask/placeholder in the Project pane. Then make the comp that you will render tou use in the OF app the active item (the pane should be highlighted, just click somewhere inside the comps timeline pane).
Then go to File > Scripts > Run Script File... and select the script bakeTransformsAndExport.jsx inside the ofxAfterEffectsTransforms/script folder.

Select a folder where to export all the data from the dialog that will popup.

### in your openFrameworks project.

Check the included example.
It is quite simple to use.



Licence
-------
Read `license.md`.
Installation
------------
Just drop the folder into the `openFrameworks/addons/` folder.

Dependencies
------------
None

Compatibility
------------
OF 0.8.0

Known issues
------------
So far it only works with 2D transforms, yet it should work with 3D just by making the parser to  correctlly interpret 3D transforms. I'll probably fix this soon.

Version history
------------

### Version 0.1 (10/15/14):
First version.


