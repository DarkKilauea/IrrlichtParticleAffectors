#include <irrlicht.h>
#include "CSplineAffector.h"
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

int main()
{
	//Start up the engine (OpenGL)
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640,480));

	//Grab pointers to the driver and scenemanager
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->setWindowCaption(L"Spline Affector Demo");

	//Create our array of points
	core::array<core::vector3df> waypointarray;
	waypointarray.push_back(core::vector3df(0,100,0));
	waypointarray.push_back(core::vector3df(100,200,0));
	waypointarray.push_back(core::vector3df(0,300,0));
	waypointarray.push_back(core::vector3df(-100,200,0));
	waypointarray.push_back(core::vector3df(-100,0,0));
	waypointarray.push_back(core::vector3df(-200,0,0));

	//Setup the particle system scene node
	scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode();
	scene::IParticleEmitter* eaf = ps->createPointEmitter(core::vector3df(0,0,0),50,100,video::SColor(255,255,255,255),video::SColor(255,255,255,255),10000,20000,0);
	ps->setEmitter(eaf);
	eaf->drop();

	//Add the Spline Affector
	scene::IParticleAffector* aff = new scene::CSplineAffector(waypointarray, 1, 0.5, 1, true);
	ps->addAffector(aff);
	aff->drop();

	//Some material stuff
	ps->setMaterialTexture(0,driver->getTexture("../media/smoke.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	ps->setMaterialFlag(video::EMF_ZBUFFER,false);
	ps->setMaterialFlag(video::EMF_LIGHTING,false);

	// add a static camera
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(0,core::vector3df(0,0,-200),core::vector3df(0,100,0));

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
			core::stringw str = L"Spline Affector Demo [";
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