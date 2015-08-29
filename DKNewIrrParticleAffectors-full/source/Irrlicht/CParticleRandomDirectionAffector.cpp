#include "CParticleRandomDirectionAffector.h"
#include "os.h"

namespace irr
{
namespace scene
{

//Constructor!
CParticleRandomDirectionAffector::CParticleRandomDirectionAffector(f32 scope, u32 changeFrequency) : Scope(scope), ChangeFrequency(changeFrequency), LastTime(0)
{
}

void CParticleRandomDirectionAffector::affect(u32 now, SParticle* particlearray, u32 count)
{
	if( !Enabled )
		return;

	if( LastTime == 0)
	{
		LastTime = now;
		return;
	}

	if(now-LastTime > ChangeFrequency)
	{
		LastTime = now;

		for(u32 i=0; i<count; ++i)
		{	
			core::vector3df randomvector = core::vector3df(
				os::Randomizer::rand() % 200-100,
				os::Randomizer::rand() % 200-100,
				os::Randomizer::rand() % 200-100).normalize();
			core::vector3df finalpoint = randomvector.getInterpolated(particlearray[i].startVector,Scope);
			particlearray[i].vector = finalpoint.setLength(particlearray[i].startVector.getLength());
		}
	}
}

}; // end namespace scene
}; // end namespace irr

