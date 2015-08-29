#ifndef __I_PARTICLE_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__
#define __I_PARTICLE_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"

namespace irr
{
namespace scene
{

class IParticleRandomDirectionAffector : public IParticleAffector
{
public:

	//! Gets emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_RANDOM_DIRECTION; }

	//! Gets the amount the change in direction deviates from the particles' start vector
	virtual f32 getScope() const = 0;

	//! Gets how often the affector changes the particles' direction
	virtual u32 getChangeFrequency() const = 0;

	//! Sets the amount the change in direction deviates from the particles' start vector
	virtual void setScope( f32 scope ) = 0;

	//! Sets how often the affector changes the particles' direction
	virtual void setChangeFrequency( u32 changeFrequency ) = 0;

};

}; // end namespace scene
}; // end namespace irr

#endif // __I_PARTICLE_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__

