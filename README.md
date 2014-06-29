Hephaestus Library
==================
My design goal for the Hephaestus library was to create a set of loosely coupled or even independent components rather than developing a large, monolithic game engine. One the one hand the library is supposed to provide toolkit classes and functions for general common operations with a high degree of reusability; on the other hand there are components which do not provide much functionality in themselves, but define a template for how the game classes should be organised.

Big words for a small library, I know. But these were initially my thoughts when I started working on this project. The library in its current form is far from complete, but it is usuable (see Examples below).

Design Fundamentals.
--------------------
Much of the design philosophy behind Hephaestus lib follows Gold's great book about object-oriented game development and even some components follow very closely the concrete design ideas laid out in his book. A good example is the sound resource management. The following dependency graph illustrates how various components contribute functionality to the subsystem.

<img src="http://chrisschuette.github.io/HephaestusLibrary/ResourceMgmt.png"></img>

A *Bundle* is an interface for managing collections of game data files (sounds, textures, ...). The only implementation of the *Bundle* interface (currently) provided by the library is the (development friendly) *DirectoryBundle* which implements a *Bundle* is the files contained in a given directory. *Bundle*s can be attached to a file server which manages a queue of load *Request*s for a specific *Resource*. Extracting a certain group of bytes 

Examples.
---------

### SuperAsteroids ###
<img src="http://chrisschuette.github.io/HephaestusLibrary/SuperAsteroid.png"></img>

SuperAsteroids is my take on the classic 1979 arcade space shooter. The asteroid is actually read in as an SVG and breaks into randomly generated pieces when struck with a laser beam, allowing the player to shoot them “to vertices”.

Some gameplay footage of me failing horribly at my own game can be seen [here](https://vimeo.com/98917928).

### Night & Day ###
<img src="http://chrisschuette.github.io/HephaestusLibrary/NightAndDay.png"></img>

Night & Day is a sketch of a puzzle platformer inspired by Sparpweed’s amazing game. Hephaestus engine uses internally Erin Catto’s Box2D as a physics simulator engine.

Some gameplay footage can be seen [here](https://vimeo.com/98908413).

Dependencies.
-------------
The following libraries are needed to successfully compile the project
* [libconfig](http://www.hyperrealm.com/libconfig/)
* [OpenGL](http://www.opengl.org)
* [GLEW](http://glew.sourceforge.net/)
* [GLFW](http://www.glfw.org/)
* [FreeType](http://freetype.org/)
* [Boost](http://www.boost.org/)
* [DevIL](http://openil.sourceforge.net/)
* [Box2D](http://box2d.org/)
* [OpenAL](http://kcat.strangesoft.net/openal.html)
* [VorbisFile](http://www.vorbis.com/)


References.
-----------
Ideas from the following references contributed substantially to the development of the library

* [Object-oriented Game Development, 	Julian Gold, Pearson Education, 2004](http://www.openisbn.com/isbn/9780321176608/)
* [Game Programming Gems 5: Component Based Object Management, 	Bjarne Rene, 2005](http://www.openisbn.com/isbn/9781584503521/)
