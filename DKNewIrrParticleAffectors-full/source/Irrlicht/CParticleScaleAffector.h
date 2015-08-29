#ifndef __C_PARTICLE_SCALE_AFFECTOR_H_INCLUDED__
#define __C_PARTICLE_SCALE_AFFECTOR_H_INCLUDED__

#include "IParticleScaleAffector.h"

namespace irr
{
namespace scene
{

class CParticleScaleAffector : public IParticleScaleAffector
{
public:

	CParticleScaleAffector(core::vector2df& targetScale, u32 timeToFullyScaled = 0);

	//! Affects a particle
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Get target scale
	virtual const core::vector2df& getTargetScale() const { return TargetScale; }

	//! Get time till particles are fully scaled
	virtual u32 getTimeToFullyScaled() const { return TimeToFullyScaled; }

	//! Set target scale
	virtual void setTargetScale( const core::vector2df& targetScale ) { TargetScale = targetScale; }

	//! Set time till particles are fully scaled
	virtual void setTimeToFullyScaled( u32 timeToFullyScaled ) { TimeToFullyScaled = timeToFullyScaled; }

private:
	core::vector2df TargetScale;
	u32 TimeToFullyScaled;
};

}; // end namespace scene
}; // end namespace irr

#endif

