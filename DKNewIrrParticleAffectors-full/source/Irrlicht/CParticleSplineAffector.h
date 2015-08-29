#ifndef __C_PARTICLE_SPLINE_AFFECTOR_H_INCLUDED__
#define __C_PARTICLE_SPLINE_AFFECTOR_H_INCLUDED__

#include "IParticleSplineAffector.h"

namespace irr
{
namespace scene
{

class CParticleSplineAffector : public IParticleSplineAffector
{
public:

	CParticleSplineAffector( core::array<core::vector3df> points, f32 speed = 1.0f, f32 tightness = 0.5f, f32 attraction = 1.0f, bool deleteAtFinalPoint = false );

	//! Affects a particle.
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Gets array of spline points
	virtual const core::array<core::vector3df>& getPoints() const { return Points; }

	//! Gets the speed of the particles along the spline
	virtual f32 getSpeed() const { return Speed; }

	//! Gets the tightness of the spline
	virtual f32 getTightness() const { return Tightness; }

	//! Gets the attraction of the particles towards the spline
	virtual f32 getAttraction() const { return Attraction; }

	//! Gets whether the particles will self-distruct at the final spline point
	virtual bool isDeleteAtFinalPoint() const { return DeleteAtFinalPoint; }

	//! Sets array of spline points
	virtual void setPoints( core::array<core::vector3df>& points ) { Points = points; }

	//! Sets the speed of the particles along the spline
	virtual void setSpeed( f32 speed ) { Speed = speed; }

	//! Sets the tightness of the spline
	virtual void setTightness( f32 tightness ) { Tightness = tightness; }

	//! Sets the attraction of the particles towards the spline
	virtual void setAttraction( f32 attraction ) { Attraction = attraction; }

	//! Sets whether the particles will self-distruct at the final spline point
	virtual void setDeleteAtFinalPoint( bool deleteAtFinalPoint ) { DeleteAtFinalPoint = deleteAtFinalPoint; }


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
