# Missan

version 2020.1

See documentation for Missan API here: https://henkasyvert.github.io/Missan/index.html

see /games/fpsdemo for an example of how to make a game using Missan


about:

Missan Engine was written by Henrik Syvertsson as part of a project at Karlstad University. 
Currently Missan Engine supports:
* graphics: loading textures (various formats), defining your own meshes (in code, good luck)
* physics: collision detection, unconstrained rigidbody physics. (no collision avoidance in physics engine atm, though this can be simulated in script)
* Component based architecture: GameObjects are defined by the components they consist of. Some premade components exist, which implement the core functionality one would expect from a game engine: Camera, transform, renderer, rigidbody
* Support for custom components, i.e. scripting. 



things that are noticably absent, but will be added later:
* there is no graphical editor
* support for internet
* sound
* importing meshes
