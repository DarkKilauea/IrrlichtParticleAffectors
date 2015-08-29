#include <irrlicht.h>
#include "CCollisionResponseAffector.h"
#include "CScaleAffector.h"
#include "CColorMorphAffector.h"
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

//Small event receiver
class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main()
{
	//Remembers whether the flame effect should follow the camera or not
	bool FireFollow = true;

	//Start up the engine (OpenGL)
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640,480));

	//create and set the event receiver
	MyEventReceiver receiver;
	device->setEventReceiver(&receiver);

	//Grab pointers to the driver and scenemanager
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	device->setWindowCaption(L"FlameThrower Demo");

	//Create Quake 3 level
	device->getFileSystem()->addZipFileArchive("../media/map-20kdm2.pk3");
	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* q3node = 0;

	if (q3levelmesh)
		q3node = smgr->addOctTreeSceneNode(q3levelmesh->getMesh(0));

	//Create triangle selector
	scene::ITriangleSelector* selector = 0;
	if (q3node)
	{		
		q3node->setPosition(core::vector3df(-1350,-130,-1400));

		selector = smgr->createOctTreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
		q3node->setTriangleSelector(selector);
	}

	//Setup the particle system scene node
	scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode();
	scene::IParticleEmitter* eaf = ps->createPointEmitter(core::vector3df(0,0,0),200,400,video::SColor(255,255,255,255),video::SColor(255,255,255,255),500,1000,5);
	ps->setEmitter(eaf);
	
	//Add affectors
	scene::IParticleAffector* aff = new scene::CCollisionResponseAffector(selector,0.5);
	ps->addAffector(aff);
	aff->drop();

	scene::IParticleAffector* aff2 = new scene::CScaleAffector(core::vector2df(6,6));
	ps->addAffector(aff2);
	aff2->drop();

	core::array<video::SColor> colorarray;
	colorarray.push_back(video::SColor(255,0,0,255));
	colorarray.push_back(video::SColor(255,255,255,0));
	colorarray.push_back(video::SColor(255,255,255,0));
	colorarray.push_back(video::SColor(255,255,0,0));
	colorarray.push_back(video::SColor(0,0,0,0));

	scene::IParticleAffector* aff3 = new scene::CColorMorphAffector(colorarray);
	ps->addAffector(aff3);
	aff3->drop();

	//Some Material stuff
	ps->setMaterialFlag(video::EMF_LIGHTING,false);
	ps->setMaterialTexture(0,driver->getTexture("../media/fireball.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	ps->setMaterialFlag(video::EMF_ZBUFFER,false);
	ps->setParticleSize(core::dimension2df(16,16));

	// add a first person shooter style user controlled camera
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0,100,250,-1,0,0,true);
	scene::ISceneNodeAnimatorCollisionResponse* anim = smgr->createCollisionResponseAnimator(selector,camera,core::vector3df(20,40,20),core::vector3df(0,-1,0),core::vector3df(0,15,0));
	camera->addAnimator(anim);
	anim->drop();

	if(selector)
		selector->drop();

	int lastFPS = -1;

	// draw everything
	while(device->run())
	{
		if(receiver.IsKeyDown(irr::KEY_KEY_F))
		{
			FireFollow = !FireFollow;
		}

		//Positions and aims the flamethrower effect
		if(FireFollow)
		{
		core::vector3df campos = camera->getAbsolutePosition();
		core::vector3df target = camera->getTarget();
		core::vector3df view = target - campos;
		view.normalize().setLength(0.3);
		eaf->setDirection(view);

		ps->setPosition(camera->getAbsolutePosition() + core::vector3df(0,-15,0) + view.setLength(10));
		}

		driver->beginScene(true, true, video::SColor(255,64,64,64));
		smgr->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"FlameThrower Demo [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

	eaf->drop();
	// delete device
	device->drop();
	return 0;
}