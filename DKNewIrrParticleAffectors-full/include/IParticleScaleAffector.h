#ifndef __I_PARTICLE_SCALE_AFFECTOR_H_INCLUDED__
#define __I_PARTICLE_SCALE_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"

namespace irr
{
namespace scene
{

class IParticleScaleAffector : public IParticleAffector
{
public:

	//! Get emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_SCALE; }

	//! Get target scale
	virtual const core::vector2df& getTargetScale() const = 0;

	//! Get time till particles are fully scaled
	virtual u32 getTimeToFullyScaled() const = 0;

	//! Set target scale
	virtual void setTargetScale( const core::vector2df& targetScale ) = 0;

	//! Set time till particles are fully scaled
	virtual void setTimeToFullyScaled( u32 timeToFullyScaled ) = 0;

};

}; // end namespace scene
}; // end namespace irr

#endif // __I_PARTICLE_SCALE_AFFECTOR_H_INCLUDED__

