#include <irrlicht.h>
#include "CRandomDirectionAffector.h"
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

int main()
{
	//Start up the engine (OpenGL)
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640,480));

	//Grab pointers to the driver and scenemanager
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->setWindowCaption(L"Random Direction Affector Demo");

	//Setup the particle system scene node
	scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode();
	scene::IParticleEmitter* eaf = ps->createBoxEmitter(core::aabbox3df(-100,-1,-100,100,1,100),core::vector3df(0,-0.03,0),50,100,video::SColor(0,0,0,0),video::SColor(0,0,0,0),5000,5000);
	ps->setEmitter(eaf);
	eaf->drop();

	//Add the Random Direction Affector
	scene::IParticleAffector* aff = new scene::CRandomDirectionAffector(0.03,250);
	ps->addAffector(aff);
	aff->drop();

	//Disable Lighting
	ps->setMaterialFlag(video::EMF_LIGHTING,false);

	// add a static camera
	smgr->addCameraSceneNode(0,core::vector3df(0,0,-300),core::vector3df(0,0,0));

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
			core::stringw str = L"Scale Affector Demo [";
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