#include "CScaleAffector.h"

namespace irr
{
namespace scene
{

CScaleAffector::CScaleAffector(core::vector2df& targetScale, u32 timeToFullyScaled) : TargetScale(targetScale), TimeToFullyScaled(timeToFullyScaled)
{
}

void CScaleAffector::affect(u32 now, SParticle* particlearray, u32 count)
{
	if( !Enabled )
		return;

	f32 LifeTime = 0;
	f32 PercentofTime = 0;
	core::vector2df scaledsize;

	for(u32 i=0; i<count; ++i)
	{
		if(TimeToFullyScaled > 0)
			LifeTime = TimeToFullyScaled;
		else
			LifeTime = particlearray[i].endTime - particlearray[i].startTime;

		PercentofTime = (now-particlearray[i].startTime)/LifeTime;
		scaledsize = particlearray[i].startSize*TargetScale;
		
		if(PercentofTime < 1)
		{
			particlearray[i].size = scaledsize.getInterpolated(particlearray[i].startSize,PercentofTime);
		}
		else
			particlearray[i].size = scaledsize;
	}

}

}; // end namespace scene
}; // end namespace irr

