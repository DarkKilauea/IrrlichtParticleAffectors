#include <irrlicht.h>
#include "CScaleAffector.h"
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

int main()
{
	//Start up the engine (OpenGL)
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640,480));

	//Grab pointers to the driver and scenemanager
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->setWindowCaption(L"Scale Affector Demo");

	//Setup the particle system scene node
	scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode();
	scene::IParticleEmitter* eaf = ps->createBoxEmitter(core::aabbox3df(-10,-1,-10,10,1,10),core::vector3df(0,0.03,0),50,100,video::SColor(255,255,255,255),video::SColor(255,255,255,255),5000,10000, 10);
	ps->setEmitter(eaf);
	eaf->drop();

	//Add the Scale Affector
	scene::IParticleAffector* aff = new scene::CScaleAffector(core::vector2df(4,4),0);
	ps->addAffector(aff);
	aff->drop();

	//Add a fade out affector to improve the effect
	scene::IParticleAffector* aff3 = ps->createFadeOutParticleAffector(video::SColor(0,0,0,0),10000);
	ps->addAffector(aff3);
	aff3->drop();

	//Some material stuff
	ps->setParticleSize(core::dimension2df(20,20));
	ps->setMaterialTexture(0,driver->getTexture("../media/smoke.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	ps->setMaterialFlag(video::EMF_ZBUFFER,false);
	ps->setMaterialFlag(video::EMF_LIGHTING,false);

	// add a static camera
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(0,core::vector3df(0,100,-300),core::vector3df(0,100,0));

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