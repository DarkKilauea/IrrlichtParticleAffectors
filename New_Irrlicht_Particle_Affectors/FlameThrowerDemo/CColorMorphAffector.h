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

#ifndef __C_COLOR_MORPH_AFFECTOR_H_INCLUDED__
#define __C_COLOR_MORPH_AFFECTOR_H_INCLUDED__

#include "IParticleAffector.h"
#include "irrArray.h"

namespace irr
{
namespace scene
{

class CColorMorphAffector : public IParticleAffector
{
public:

	//! Creates a color morph affector.
	/** This affector modifies the color of particles according to an array of SColors.
	It can either interpolate these colors over the lifetime of the particle, or follow a set
	of user defined times.
	\param colorlist: Array of colors you want to be interpolated over the lifetime of the particles.
	\param timelist: Overrides default behavior and forces each corresponding color to be set at the times in the array.
	\param smooth: Whether to smoothly change from color to color.
	*/
	CColorMorphAffector(core::array<video::SColor> colorlist, bool smooth = true, core::array<u32> timelist = core::array<u32>());

	//! Called automatically by irrlicht to apply the effect
	void affect(u32 now, SParticle* particlearray, u32 count);

	//! Gets Color Array
	const core::array<video::SColor>& getColorArray() const { return ColorList; }

	//! Sets Color Array
	void setColorArray( core::array<video::SColor>& colorArray ) { ColorList = colorArray; }

	//! Gets Time Array
	const core::array<u32>& getTimeArray() const { return TimeList; }

	//! Sets Time Array
	void setColorArray( core::array<u32>& timeArray ) { TimeList = timeArray; }

	//! Returns whether smooth is enabled
	bool isSmooth() const { return Smooth; }

	//! Sets smooth
	void setSmooth( bool smooth = true ) { Smooth = smooth; }

	//! Get emitter type (faked since there isn't a type for us, so we'll just say we don't have a type)
	virtual E_PARTICLE_AFFECTOR_TYPE getType() const { return EPAT_NONE; }

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

