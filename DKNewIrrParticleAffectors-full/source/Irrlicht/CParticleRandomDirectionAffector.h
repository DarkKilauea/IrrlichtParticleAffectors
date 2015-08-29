#ifndef __C_PARTICLE_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__
#define __C_PARTICLE_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__

#include "IParticleRandomDirectionAffector.h"

namespace irr
{
namespace scene
{

class CParticleRandomDirectionAffector : public IParticleRandomDirectionAffector
{
public:

	CParticleRandomDirectionAffector(f32 scope = 0.1, u32 changeFrequency = 500);

	//! Affects a particle.
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Gets the amount the change in direction deviates from the particles' start vector
	virtual f32 getScope() const { return Scope; }

	//! Gets how often the affector changes the particles' direction
	virtual u32 getChangeFrequency() const { return ChangeFrequency; }

	//! Sets the amount the change in direction deviates from the particles' start vector
	virtual void setScope( f32 scope ) { Scope = scope; }

	//! Sets how often the affector changes the particles' direction
	virtual void setChangeFrequency( u32 changeFrequency ) { ChangeFrequency = changeFrequency; }


private:
	f32 Scope;
	u32 ChangeFrequency;
	u32 LastTime;
};

}; // end namespace scene
}; // end namespace irr

#endif
