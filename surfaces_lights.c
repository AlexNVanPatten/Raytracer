/** Surface functions.
 *
 *  @author N. Danner
 */

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "geom356.h"

#include "surfaces_lights.h"

/** The type of a sphere surface.
 */
typedef struct _sphere_data_t {
    /** The center of the sphere.
     */
    point3_t center ;
    /** The radius of the sphere.
     */
    float radius ;
} sphere_data_t ;

static bool sfc_hit_sphere(void* data, ray3_t* ray, float t0,
        float t1, hit_record_t* hit) ;

surface_t* make_sphere(float x, float y, float z, float radius, 
        material_t* material) 
{
  point3_t middle;
  middle.x = x;
  middle.y = y;
  middle.z = z;
  sphere_data_t theSphere;
  theSphere.center = middle;
  theSphere.radius = radius;
  surface_t sphere;
  void* spherePoint = &theSphere;
  sphere.data = spherePoint;
  sphere.material = material;
  sphere.hit_fn = &sfc_hit_sphere;
  surface_t* sPoint;
  sPoint = &sphere;
  return sPoint;
}
}

static bool sfc_hit_sphere(void* data, ray3_t* ray, float t0,
			   float t1, hit_record_t* hit)
{
  //Get the base and direction of the ray.
  point3_t theBase = (*ray).base;
  vector3_t theDir = (*ray).dir;

  //Change point into vector for vector math
  vector3_t baseVector;
  baseVector.x = theBase.x;
  baseVector.y = theBase.y;
  baseVector.z = theBase.z;

  //Dereferance Sphere
  sphere_data_t* sdata = (sphere_data_t*) data;
  sphere_data_t sphere = *sdata;

  //Get radius and center as a vector for vector math
  float radius = sphere.radius;
  point3_t center = sphere.center;
  vector3_t cVec;
  cVec.x = center.x;
  cVec.y = center.y;
  cVec.z = center.z;

  //calculate dot products for vector math
  vector3_t EminusC;
  subtract(&baseVector, &cVec, &EminusC);
  float DdotE = dot(theDir, EminusC);
  float DdotD = dot(theDir, theDir);
  float EdotE = dot(EminusC, EminusC);
  
  //Calculate radical of quadractic equation
  float radical = DdotE*DdotE - DdotD*(EdotE - radius*radius);
  
  //If radical is less than zero, no intersections, return false.
  if(radical < 0)
    {
      return false;
    }
  else
    {
      //Get root of radical if it exists.
      float root = (float) Math.Sqrt((double) radical);

      //Minus intersection is always closer, so calculate that
      float intersect = (-DdotE-root)/DdotD;
      
      //Check if intersection is within valid range
      if(intersect < t0 || intersect > t1)
	{
	  return false;
	}
      else
	{
	  //If it is, calcuate infromation for hit record.
	  (*hit).t = intersect;

	  //Calculate intersection Point
	  vector3_t vMult;
	  vector3_t vIntersection;
	  multiply(theDir, intersect, vMult);
	  subtract(baseVector, vMult, vIntersection);
	  point3_t intPoint;
	  intPoint.x = vIntersection.x;
	  intPoint.y = vIntersection.y;
	  intPoint.z = vIntersection.z;
	  (*hit).hit_pt = intPoint;

	  //Calculate Surface Normal
	  vector3_t vSNorm;
	  subtract(vIntersction, cVec, vSNorm);
	  normalize(vSNorm);
	  (*hit).normal = vSNorm;

	  return true;
	}
    }
      
  return false;
}

bool sfc_hit(surface_t* sfc, ray3_t* ray, float t0, float t1,
        hit_record_t* hit) {
    if ((sfc->hit_fn)(sfc->data, ray, t0, t1, hit)) {
        hit->sfc = sfc ;
        return true ;
    }
    else {
        return false ;
    }
}

