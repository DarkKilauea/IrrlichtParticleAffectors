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

#ifndef __C_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__
#define __C_RANDOM_DIRECTION_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"

namespace irr
{
namespace scene
{

class CRandomDirectionAffector : public IParticleAffector
{
public:
	//! Creates a random direction affector.
	/** This affector modifies the vector of particles with a random direction.
	\param scope: How much the new random direction should vary from the starting direction
	\param changeFrequency: How much time in ms before we apply a new random direction for all particles
	*/
	CRandomDirectionAffector(f32 scope = 0.1, u32 changeFrequency = 500);

	//! Called automatically by irrlicht to apply the effect
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Get emitter type (faked since there isn't a type for us, so we'll just say we don't have a type)
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_NONE; }

	//! Gets the amount the change in direction deviates from the particles' start vector
	f32 getScope() const { return Scope; }

	//! Gets how often the affector changes the particles' direction
	u32 getChangeFrequency() const { return ChangeFrequency; }

	//! Sets the amount the change in direction deviates from the particles' start vector
	void setScope( f32 scope ) { Scope = scope; }

	//! Sets how often the affector changes the particles' direction
	void setChangeFrequency( u32 changeFrequency ) { ChangeFrequency = changeFrequency; }

private:
	f32 Scope;
	u32 ChangeFrequency;
	u32 LastTime;
};

}; // end namespace scene
}; // end namespace irr

#endif
