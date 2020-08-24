Hartmann Music NeuronVS Mac VST
===============================

This contains the (modified) NeuronVS VST plug-in code for use on the Mac. It is based on the VST 2.1 SDK and can be compiled using Xcode 3.2.5 on 10.6.8 and later. Please note that it is not compatible with newer versions of Xcode/the Apple frameworks as it uses QuickDraw, which has been discontinued in 10.8 (I think). The project comes with a test engine so the sound output can be verified but without the actual NeuronVS DSP engine.

Feel free to add to the sources as you deem appropriate. Time (and distribution rights) permitting I will create a version of the latest sources with the full featured DSP library and make this available.

TODOs
=====

* Update VST 2 SDK to the latest version
* Add VST 3 support
* Update code so it uses the latest version of VSTGUILib, update for Xcode 5/10.9
* Add mouse input to the resynator controls
* Create AudioUnit version
* Add VST Windows support

Email me with any questions you might have, however, I did not develop this code so I might not be able to answer your questions. Use at your own risk. You can reach me at neuronaut [AT] bernsee [DOT] com.
