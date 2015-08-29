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

#ifndef __C_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__
#define __C_COLLISION_RESPONSE_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"
#include "ITriangleSelector.h"
#include "ISceneCollisionManager.h"
#include "irrArray.h"

namespace irr
{
namespace scene
{

class CCollisionResponseAffector : public IParticleAffector
{
public:

	//! Creates a collision response affector.
	/** This affector modifies the vectors of the particles upon a collision with the
	triangle selector.
	\param selector: Pointer to the selector used for the surface the particles
	will collide with.
	\param bounce: Amount of bounce given to the particles on collision.
	1.0 means particles will bounce with the same velocity,
	less than 1 means a reduction in bounce, and greater than 1 adds more bounce. */
	CCollisionResponseAffector(ITriangleSelector* selector, f32 bounce = 1.0f);
	~CCollisionResponseAffector();

	//! Affects a particle.
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Sets the surface the particles with collide with.
	void setWorld(ITriangleSelector* selector);

	//! Gets the collision surface this affector is using
	const ITriangleSelector* getWorld() const { return World; }

	//! Sets the bounce coefficient
	void setBounce(f32 bounce) { Bounce = bounce; }

	//! Gets the bounce coefficient
	const f32 getBounce() const { return Bounce; }

	//! Get emitter type (faked since there isn't a type for us, so we'll just say we don't have a type)
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_NONE; }

protected:
	ITriangleSelector* World;
	core::array<core::triangle3df> TriangleArray;
	s32 TriangleCount;
	f32 Bounce;
};

}; // end namespace scene
}; // end namespace irr

#endif

