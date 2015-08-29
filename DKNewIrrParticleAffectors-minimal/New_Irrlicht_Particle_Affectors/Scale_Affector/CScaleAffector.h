/******************************************************************************
*  Copyright (C) 2008 Joshua Jones (aka. Dark_Kilauea)                        *
*  This software is provided 'as-is', without any express or implied          *
*  warranty.  In no event will the authors be held liable for any damages     *
*  arising from the use of this software.                                     *
*                                                                             *
*  Permission is granted to anyone to use this software for any purpose,      *
*  including commercial applications, and to alter it and redistribute it     *
*  freely, subject to the following restrictions:                             *
*                                                                             *
*  1. The origin of this software must not be misrepresented; you must not    *
*     claim that you wrote the original software. If you use this software    *
*     in a product, an acknowledgment in the product documentation would be   *
*     appreciated but is not required.                                        *
*  2. Altered source versions must be plainly marked as such, and must not be *
*     misrepresented as being the original software.                          *
*  3. This notice may not be removed or altered from any source distribution. *
*                                                                             *
******************************************************************************/

#ifndef __C_SCALE_AFFECTOR_H_INCLUDED__
#define __C_SCALE_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"

namespace irr
{
namespace scene
{

class CScaleAffector : public IParticleAffector
{
public:
	//! Creates a scale affector.
	/** This affector modifies the size of individual particles to a target size.
	\param targetScale: The size the particles should be at at the end of the time period.
	\param timeToFullyScaled: If 0, the scale will be applied over the lifetime of the particle.
	Otherwise, the particle will reach the new scale in this many ms.
	*/
	CScaleAffector(core::vector2df& targetScale, u32 timeToFullyScaled = 0);

	//! Called automatically by irrlicht to apply the effect
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Get emitter type (faked since there isn't a type for us, so we'll just say we don't have a type)
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_NONE; }

	//! Get target scale
	const core::vector2df& getTargetScale() const { return TargetScale; }

	//! Get time till particles are fully scaled
	u32 getTimeToFullyScaled() const { return TimeToFullyScaled; }

	//! Set target scale
	void setTargetScale( const core::vector2df& targetScale ) { TargetScale = targetScale; }

	//! Set time till particles are fully scaled
	void setTimeToFullyScaled( u32 timeToFullyScaled ) { TimeToFullyScaled = timeToFullyScaled; }

private:
	core::vector2df TargetScale;
	u32 TimeToFullyScaled;
};

}; // end namespace scene
}; // end namespace irr

#endif
