#ifndef __C_PARTICLE_COLOR_MORPH_AFFECTOR_H_INCLUDED__
#define __C_PARTICLE_COLOR_MORPH_AFFECTOR_H_INCLUDED__

#include "IParticleColorMorphAffector.h"

namespace irr
{
namespace scene
{

class CParticleColorMorphAffector : public IParticleColorMorphAffector
{
public:

	CParticleColorMorphAffector(core::array<video::SColor> colorlist, 
		bool smooth = true, 
		core::array<u32> timelist = core::array<u32>());

	//! Affects a particle.
	virtual void affect(u32 now, SParticle* particlearray, u32 count);

	//! Gets Color Array
	virtual const core::array<video::SColor>& getColorArray() const { return ColorList; }

	//! Sets Color Array
	virtual void setColorArray( core::array<video::SColor>& colorArray ) { ColorList = colorArray; }

	//! Gets Time Array
	virtual const core::array<u32>& getTimeArray() const { return TimeList; }

	//! Sets Time Array
	virtual void setColorArray( core::array<u32>& timeArray ) { TimeList = timeArray; }

	//! Returns whether smooth is enabled
	virtual bool isSmooth() const { return Smooth; }

	//! Sets smooth
	virtual void setSmooth( bool smooth = true ) { Smooth = smooth; }

protected:
	core::array<video::SColor> ColorList;
	core::array<u32> TimeList;
	bool Smooth;
	u32 GetCurrentTimeSlice(u32 particleTime);
	u32 MaxIndex;
};

}; // end namespace scene
}; // end namespace irr

#endif
