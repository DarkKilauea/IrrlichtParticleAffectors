#include <irrlicht.h>
#include "CColorMorphAffector.h"
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

int main()
{
	//Start up the engine (OpenGL)
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640,480));

	//Grab pointers to the driver and scenemanager
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->setWindowCaption(L"Color Morph Affector Demo");

	//Create our array of colors
	core::array<video::SColor> colorarray;
	colorarray.push_back(video::SColor(255,255,0,0));
	colorarray.push_back(video::SColor(255,0,255,0));
	colorarray.push_back(video::SColor(255,0,0,255));
	colorarray.push_back(video::SColor(255,255,0,0));
	colorarray.push_back(video::SColor(255,0,255,0));
	colorarray.push_back(video::SColor(255,0,0,255));
	colorarray.push_back(video::SColor(255,255,0,0));
	colorarray.push_back(video::SColor(255,0,255,0));
	colorarray.push_back(video::SColor(255,0,0,255));

	//Setup the particle system scene node
	scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode();
	scene::IParticleEmitter* eaf = ps->createBoxEmitter(core::aabbox3df(-10,-10,-10,10,10,10),core::vector3df(0,0.03,0),5,10,video::SColor(0,0,0,0),video::SColor(0,0,0,0),16000,16000);
	ps->setEmitter(eaf);
	eaf->drop();

	//Add the Color Morph Affector
	scene::IParticleAffector* aff = new scene::CColorMorphAffector(colorarray);
	ps->addAffector(aff);
	aff->drop();

	//Setup some material stuff
	ps->setMaterialFlag(video::EMF_LIGHTING,false);
	ps->setParticleSize(core::dimension2df(8,8));

	// add a static camera
	smgr->addCameraSceneNode(0,core::vector3df(0,250,-500),core::vector3df(0,250,0));

	int lastFPS = -1;

	// draw everything (should be self explanitory, otherwise check out the hello world tutorial)
	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(255,64,64,64));
		smgr->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"Color Morph Affector Demo [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

	// delete device
	device->drop();
	return 0;
}