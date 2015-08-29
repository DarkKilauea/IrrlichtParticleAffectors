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

#ifndef __C_SPLINE_AFFECTOR_H_INCLUDED__
#define __C_SPLINE_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"
#include "irrArray.h"

namespace irr
{
namespace scene
{

class CSplineAffector : public IParticleAffector
{
public:

	//! Creates a spline affector.
	/** This affector attracts particles to follow along a user defined spline.
	\param points: Array of points in the spline.
	\param speed: How quickly the particles should move along the spline.
	\param tightness: Affects the spline's tightness.  0.5 is usually fine.
	\param attraction: How much the particles should try to stay with the spline.
	High values tend to override other affectors.
	\param deleteAtFinalPoint: If true, this will cause particles to self-distruct when they hit the final spline point.
	*/
	CSplineAffector(core::array<core::vector3df> points, f32 speed = 1.0f, f32 tightness = 0.5f, f32 attraction = 1.0f, bool deleteAtFinalPoint = false );

	//! Called automatically by irrlicht to apply the effect
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Get emitter type (faked since there isn't a type for us, so we'll just say we don't have a type)
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_NONE; }

	//! Gets array of spline points
	const core::array<core::vector3df>& getPoints() const { return Points; }

	//! Gets the speed of the particles along the spline
	f32 getSpeed() const { return Speed; }

	//! Gets the tightness of the spline
	f32 getTightness() const { return Tightness; }

	//! Gets the attraction of the particles towards the spline
	f32 getAttraction() const { return Attraction; }

	//! Gets whether the particles will self-distruct at the final spline point
	bool isDeleteAtFinalPoint() const { return DeleteAtFinalPoint; }

	//! Sets array of spline points
	void setPoints( core::array<core::vector3df>& points ) { Points = points; }

	//! Sets the speed of the particles along the spline
	void setSpeed( f32 speed ) { Speed = speed; }

	//! Sets the tightness of the spline
	void setTightness( f32 tightness ) { Tightness = tightness; }

	//! Sets the attraction of the particles towards the spline
	void setAttraction( f32 attraction ) { Attraction = attraction; }

	//! Sets whether the particles will self-distruct at the final spline point
	void setDeleteAtFinalPoint( bool deleteAtFinalPoint ) { DeleteAtFinalPoint = deleteAtFinalPoint; }


private:
	core::array<core::vector3df> Points;
	f32 Speed;
	f32 Tightness;
	f32 Attraction;
	bool DeleteAtFinalPoint;
	inline s32 clamp(s32 idx, s32 size);
};

}; // end namespace scene
}; // end namespace irr

#endif

