#include "CRandomDirectionAffector.h"
#include <stdlib.h>

namespace irr
{
namespace scene
{

//Constructor!
CRandomDirectionAffector::CRandomDirectionAffector(f32 scope, u32 changeFrequency) : Scope(scope), ChangeFrequency(changeFrequency), LastTime(0)
{
}

void CRandomDirectionAffector::affect(u32 now, SParticle* particlearray, u32 count)
{
	if( !Enabled )
		return;
	if( LastTime == 0)
		LastTime = now;

	if(now-LastTime > ChangeFrequency)
	{
		LastTime = now;
		srand(now);

		for(u32 i=0; i<count; ++i)
		{	
			core::vector3df randomvector = core::vector3df(rand()%200-100,
				rand()%200-100,
				rand()%200-100).normalize();
			core::vector3df finalpoint = randomvector.getInterpolated(particlearray[i].startVector,Scope);
			particlearray[i].vector = finalpoint.setLength(particlearray[i].startVector.getLength());
		}
	}
}

}; // end namespace scene
}; // end namespace irr

