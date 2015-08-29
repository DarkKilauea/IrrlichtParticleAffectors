#include "CColorMorphAffector.h"

namespace irr
{
namespace scene
{

//Constructor!
CColorMorphAffector::CColorMorphAffector(core::array<video::SColor> colorlist, bool smooth, core::array<u32> timelist) : ColorList(colorlist), Smooth(smooth), TimeList(timelist)
{
}

void CColorMorphAffector::affect(u32 now, SParticle* particlearray, u32 count)
{
	if( !Enabled )
		return;

	//If empty, skip
	if(ColorList.size() == 0)
		return;

	if(TimeList.size() > ColorList.size())
		MaxIndex = ColorList.size()-1;
	else
		MaxIndex = TimeList.size()-1;

	//Default behavior: Interpolates colors over the lifetime of the particle
	if(TimeList.size() == 0)
	{
		for(u32 i=0; i<count; ++i)
		{
			video::SColor FinalColor;
			f32 LifeTime = particlearray[i].endTime - particlearray[i].startTime;
			f32 PercentofTime = (now-particlearray[i].startTime)/LifeTime;
			
			if(PercentofTime < 1)
			{
				f32 remainder = PercentofTime * (ColorList.size()-1);
				u32 elementcount = remainder;
				remainder -= elementcount;

				if(Smooth)
					FinalColor = ColorList[elementcount+1].getInterpolated(ColorList[elementcount].color,remainder);
				else
					FinalColor = ColorList[elementcount].color;

				particlearray[i].color = FinalColor;
			}
			else
				particlearray[i].color = ColorList[ColorList.size()-1].color;
		}
	}
	//Override: Sets each color at the time specified.
	else
	{
		for(u32 i=0; i<count; ++i)
		{
			video::SColor FinalColor;
			f32 currectTime = (now-particlearray[i].startTime);

			if(currectTime < TimeList[0])
				continue;

			if(currectTime > TimeList[MaxIndex])
			{
				particlearray[i].color = ColorList[MaxIndex].color;
				continue;
			}

			u32 index = GetCurrentTimeSlice(currectTime);
			f32 LifeTime = TimeList[index+1] - TimeList[index];
			if(LifeTime == 0)
				LifeTime = 1;

			f32 percent = currectTime/LifeTime;
			percent -= index-1;

			if(percent < 1)
			{
				if(Smooth)
					FinalColor = ColorList[index+1].getInterpolated(ColorList[index].color,percent);
				else
					FinalColor = ColorList[index].color;

				particlearray[i].color = FinalColor;
			}
			else
				particlearray[i].color = ColorList[index+1].color;
		}
	}

}

u32 CColorMorphAffector::GetCurrentTimeSlice(u32 particleTime)
{
	for(u32 x=0; x<=MaxIndex; x++)
	{
		if(particleTime < TimeList[x])
		{
			return x;
		}
	}
}

}; // end namespace scene
}; // end namespace irr
