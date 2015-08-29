#ifndef __I_PARTICLE_COLOR_MORPH_AFFECTOR_H_INCLUDED__
#define __I_PARTICLE_COLOR_MORPH_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"
#include "irrArray.h"

namespace irr
{
namespace scene
{

class IParticleColorMorphAffector : public IParticleAffector
{
public:

	//! Gets Color Array
	virtual const core::array<video::SColor>& getColorArray() const = 0;

	//! Sets Color Array
	virtual void setColorArray( core::array<video::SColor>& colorArray ) = 0;

	//! Gets Time Array
	virtual const core::array<u32>& getTimeArray() const = 0;

	//! Sets Time Array
	virtual void setColorArray( core::array<u32>& timeArray ) = 0;

	//! Returns whether smooth is enabled
	virtual bool isSmooth() const = 0;

	//! Sets smooth
	virtual void setSmooth( bool smooth = true ) = 0;

	//! Gets emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_COLOR_MORPH; }
};

}; // end namespace scene
}; // end namespace irr

#endif // __I_PARTICLE_COLOR_MORPH_AFFECTOR_H_INCLUDED__

