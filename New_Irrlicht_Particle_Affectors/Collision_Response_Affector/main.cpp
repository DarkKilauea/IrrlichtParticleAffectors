#include <irrlicht.h>
#include "CCollisionResponseAffector.h"
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

int main()
{
	//Start up the engine (OpenGL)
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640,480));

	//Grab pointers to the driver and scenemanager
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->setWindowCaption(L"Collision Response Affector Demo");

	//Grab the Quake 3 map
	device->getFileSystem()->addZipFileArchive("../media/map-20kdm2.pk3");

	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* q3node = 0;

	if (q3levelmesh)
		q3node = smgr->addOctTreeSceneNode(q3levelmesh->getMesh(0));

	scene::ITriangleSelector* selector = 0;
	
	//Create our triangle selector
	if (q3node)
	{		
		q3node->setPosition(core::vector3df(-1350,-130,-1400));

		selector = smgr->createOctTreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
		q3node->setTriangleSelector(selector);
	}

	//Setup the particle system scene node
	scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode();
	scene::IParticleEmitter* eaf = ps->createPointEmitter(core::vector3df(0,-0.14,0),100,200,video::SColor(255,255,255,255),video::SColor(255,255,255,255),1000,2000,30);
	ps->setEmitter(eaf);
	eaf->drop();

	//Add the Collision Response Affector
	scene::IParticleAffector* aff = new scene::CCollisionResponseAffector(selector,1);
	ps->addAffector(aff);
	aff->drop();

	//Setup some material stuff
	ps->setMaterialFlag(video::EMF_LIGHTING,false);
	ps->setPosition(core::vector3df(-128,0,10));
	ps->setMaterialTexture(0,driver->getTexture("../media/particle.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	ps->setMaterialFlag(video::EMF_ZBUFFER,false);
	ps->setParticleSize(core::dimension2df(32,32));

	// add a first person shooter style user controlled camera
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0,100,250,-1,0,0,true);
	scene::ISceneNodeAnimatorCollisionResponse* anim = smgr->createCollisionResponseAnimator(selector,camera,core::vector3df(20,40,20),core::vector3df(0,-1,0),core::vector3df(0,15,0));
	camera->addAnimator(anim);
	anim->drop();

	if(selector)
		selector->drop();

	int lastFPS = -1;

	// draw everything (should be self explanitory, otherwise check out the collision tutorial)
	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(255,64,64,64));
		smgr->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"Collision Response Affector Demo [";
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