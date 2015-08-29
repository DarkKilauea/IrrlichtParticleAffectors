#ifndef __I_PARTICLE_SPLINE_AFFECTOR_H_INCLUDED__
#define __I_PARTICLE_SPLINE_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"
#include "irrArray.h"

namespace irr
{
namespace scene
{

class IParticleSplineAffector : public IParticleAffector
{
public:

	//! Gets emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_SPLINE; }

	//! Gets array of spline points
	virtual const core::array<core::vector3df>& getPoints() const = 0;

	//! Gets the speed of the particles along the spline
	virtual f32 getSpeed() const = 0;

	//! Gets the tightness of the spline
	virtual f32 getTightness() const = 0;

	//! Gets the attraction of the particles towards the spline
	virtual f32 getAttraction() const = 0;

	//! Gets whether the particles will self-distruct at the final spline point
	virtual bool isDeleteAtFinalPoint() const = 0;

	//! Sets array of spline points
	virtual void setPoints( core::array<core::vector3df>& points ) = 0;

	//! Sets the speed of the particles along the spline
	virtual void setSpeed( f32 speed ) = 0;

	//! Sets the tightness of the spline
	virtual void setTightness( f32 tightness ) = 0;

	//! Sets the attraction of the particles towards the spline
	virtual void setAttraction( f32 attraction ) = 0;

	//! Sets whether the particles will self-distruct at the final spline point
	virtual void setDeleteAtFinalPoint( bool deleteAtFinalPoint ) = 0;

};

}; // end namespace scene
}; // end namespace irr

#endif // __I_PARTICLE_SPLINE_AFFECTOR_H_INCLUDED__

