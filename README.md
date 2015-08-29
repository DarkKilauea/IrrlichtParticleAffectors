# IrrlichtParticleAffectors
Particle Affectors for the Irrlicht Graphics Engine.

This repository holds the source code for Particle Affectors for the [Irrlicht Graphics Engine](http://irrlicht.sourceforge.net).

This repository is an archive and is provided in the hope that it might be useful to someone.  
*I do not plan to continue maintaining this project*

Installation
------------

The "full" package intergrates the new affectors into the Irrlicht engine as if they were part of the main package.  
The "minimal" package contains just the changes required to get the scale affector to work.  The other affectors can be simply included into your project and used.

In both cases there is a diff that can be applied to your copy of the Irrlicht 1.4.1 source.

It's possible that later versions of Irrlicht applied a patch to add scale to the particle data.  In that case, the minimal patch may not be required for later versions.

Also included is the source code for some demos, in order to test that the installation worked.

Affectors Included
------------------
* Collision Response - Particles will collide with objects in the scene and "bounce" off any surfaces.
* Color Morph - Particles will change color over time based on a set of parameters.
* Random Direction - Applies a random direction change to a particle over time.
* Scale - Changes the size of particles over time.
* Spline - Applies forces to make particles follow a provided path.
