#include "CCollisionResponseAffector.h"

namespace irr
{
namespace scene
{

CCollisionResponseAffector::CCollisionResponseAffector(ITriangleSelector* selector, f32 bounce) : World(selector), Bounce(bounce)
{
	if(World)
		World->grab();
}

CCollisionResponseAffector::~CCollisionResponseAffector()
{
	if(World)
		World->drop();
}

void CCollisionResponseAffector::affect(u32 now, SParticle* particlearray, u32 count)
{
	if( !Enabled )
		return;

	if( !World )
		return;

	for(u32 i=0; i<count; ++i)
	{
		//If we aren't moving, we obviously won't collide
		if(particlearray[i].vector == core::vector3df(0,0,0))
			continue;

		core::vector3df v = particlearray[i].vector;
		core::line3df line = core::line3df(particlearray[i].pos, v);
		core::vector3df Intersection;

		//Build Triangle List
		TriangleArray.set_used(World->getTriangleCount());
		World->getTriangles(TriangleArray.pointer(), World->getTriangleCount(), TriangleCount, line);
		
		//Create Bounding Box for our particle's motion
		const f32 minX = core::min_(line.start.X, line.end.X);
		const f32 maxX = core::max_(line.start.X, line.end.X);
		const f32 minY = core::min_(line.start.Y, line.end.Y);
		const f32 maxY = core::max_(line.start.Y, line.end.Y);
		const f32 minZ = core::min_(line.start.Z, line.end.Z);
		const f32 maxZ = core::max_(line.start.Z, line.end.Z);

		//Test for possible collision (Broadpass)
		for(u32 x=0; x<TriangleCount; x++)
		{
			const core::triangle3df & triangle = TriangleArray[x];

			if(minX > triangle.pointA.X && minX > triangle.pointB.X && minX > triangle.pointC.X)
				continue;
			if(maxX < triangle.pointA.X && maxX < triangle.pointB.X && maxX < triangle.pointC.X)
				continue;
			if(minY > triangle.pointA.Y && minY > triangle.pointB.Y && minY > triangle.pointC.Y)
				continue;
			if(maxY < triangle.pointA.Y && maxY < triangle.pointB.Y && maxY < triangle.pointC.Y)
				continue;
			if(minZ > triangle.pointA.Z && minZ > triangle.pointB.Z && minZ > triangle.pointC.Z)
				continue;
			if(maxZ < triangle.pointA.Z && maxZ < triangle.pointB.Z && maxZ < triangle.pointC.Z)
				continue;

			//If we have a collision, set the reflection vector
			if(TriangleArray[x].getIntersectionWithLimitedLine(line,Intersection))
			{
				core::vector3df n = triangle.getNormal().normalize();
				particlearray[i].pos = Intersection;
				particlearray[i].vector	-= 2*n*(n.dotProduct(v));

				//Multiply by the bounce coefficient
				particlearray[i].vector *= Bounce;
			}
		}
	}

}

void CCollisionResponseAffector::setWorld(ITriangleSelector *selector)
{
	if(World)
		World->drop();
	World = 0;
	World = selector;
	if(World)
		World->grab();
}

}; // end namespace scene
}; // end namespace irr