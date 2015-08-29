#include "CParticleSplineAffector.h"

namespace irr
{
namespace scene
{

CParticleSplineAffector::CParticleSplineAffector(core::array<core::vector3df> points, f32 speed, f32 tightness, f32 attraction, bool deleteAtFinalPoint ) : Points(points), Speed(speed), Tightness(tightness), Attraction(attraction), DeleteAtFinalPoint(deleteAtFinalPoint)
{
}

inline s32 CParticleSplineAffector::clamp(s32 idx, s32 size)
{
	return ( idx<0 ? size+idx : ( idx>=size ? idx-size : idx ) );
}

void CParticleSplineAffector::affect(u32 now, SParticle* particlearray, u32 count)
{
	if( !Enabled )
		return;

	const u32 pSize = Points.size();

	if( pSize == 0 )
		return;

	for(u32 i=0; i<count; ++i)
	{
		const f32 dt = ( (now-particlearray[i].startTime) * Speed * 0.001f );
		const f32 u = core::fract ( dt );
		const s32 idx = core::floor32( dt ) % pSize;
		//const f32 u = 0.001f * fmodf( dt, 1000.0f );

		const core::vector3df& p0 = Points[ clamp( idx - 1, pSize ) ];
		const core::vector3df& p1 = Points[ clamp( idx + 0, pSize ) ]; // starting point
		const core::vector3df& p2 = Points[ clamp( idx + 1, pSize ) ]; // end point
		const core::vector3df& p3 = Points[ clamp( idx + 2, pSize ) ];

		// hermite polynomials
		const f32 h1 = 2.0f * u * u * u - 3.0f * u * u + 1.0f;
		const f32 h2 = -2.0f * u * u * u + 3.0f * u * u;
		const f32 h3 = u * u * u - 2.0f * u * u + u;
		const f32 h4 = u * u * u - u * u;

		// tangents
		const core::vector3df t1 = ( p2 - p0 ) * Tightness;
		const core::vector3df t2 = ( p3 - p1 ) * Tightness;

		const core::vector3df& finalpoint = (p1 * h1 + p2 * h2 + t1 * h3 + t2 * h4);

		core::vector3df direction = (finalpoint - particlearray[i].pos).setLength(Attraction);
		particlearray[i].pos += direction;

		if(DeleteAtFinalPoint)
		{
			//If we touch the final point, tell the particle to self-distruct
			if(particlearray[i].pos.getDistanceFrom(Points.getLast()) < 1)
				particlearray[i].endTime = now+1;
		}
	}
}

}; // end namespace scene
}; // end namespace irr

