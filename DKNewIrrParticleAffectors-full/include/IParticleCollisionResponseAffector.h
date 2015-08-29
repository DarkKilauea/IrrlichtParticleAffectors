#ifndef __I_PARTICLE_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__
#define __I_PARTICLE_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"
#include "ITriangleSelector.h"

namespace irr
{
namespace scene
{

class IParticleCollisionResponseAffector : public IParticleAffector
{
public:

	//! Sets the surface the particles with collide with.
	virtual void setWorld(ITriangleSelector* selector) = 0;

	//! Gets the collision surface this affector is using to collide particles against
	virtual const ITriangleSelector* getWorld() const = 0;

	//! Sets the bounce coefficient
	virtual void setBounce(f32 bounce) = 0;

	//! Gets the bounce coefficient
	virtual const f32 getBounce() const = 0;

	//! Get emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_COLLISION; }
};

}; // end namespace scene
}; // end namespace irr

#endif // __I_PARTICLE_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__
