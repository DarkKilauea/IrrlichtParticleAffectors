#ifndef __C_PARTICLE_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__
#define __C_PARTICLE_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__

#include "IParticleCollisionResponseAffector.h"
#include "irrArray.h"
#include "triangle3d.h"

namespace irr
{
namespace scene
{

class CParticleCollisionResponseAffector : public IParticleCollisionResponseAffector
{
public:

	CParticleCollisionResponseAffector(ITriangleSelector* selector, f32 bounce = 1.0f);
	~CParticleCollisionResponseAffector();

	//! Affects a particle.
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Sets the surface the particles with collide with.
	/** \param selector: pointer to the new surface to replace the old one */
	virtual void setWorld(ITriangleSelector* selector);

	//! Gets the collision surface this affector is using
	/** \return Pointer to the affectors currect collision surface */
	virtual const ITriangleSelector* getWorld() const { return World; }

	//! Sets the bounce coefficient
	virtual void setBounce(f32 bounce) { Bounce = bounce; }

	//! Gets the bounce coefficient
	virtual const f32 getBounce() const { return Bounce; }

protected:
	ITriangleSelector* World;
	core::array<core::triangle3df> TriangleArray;
	s32 TriangleCount;
	f32 Bounce;
};

}; // end namespace scene
}; // end namespace irr

#endif

