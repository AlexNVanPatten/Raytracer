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
  point3_t theBase = (*ray).base;
  vector3_t theDir = (*ray).dir;

  float px = theBase.x;
  float py = theBase.y;
  float pz = theBase.z;
  float vx = theDir.x;
  float vy = theDir.y;
  float vz = theDir.z;

  vector3_t baseVector;
  baseVector.x = px;
  baseVector.y = py;
  baseVector.z = pz;

  sphere_data_t sphere = *data;
  float radius = sphere.radius;
  point3_t center = sphere.center;
  vector3_t cVec;
  cVec.x = center.x;
  cVec.y = center.y;
  cVec.z = center.z;

  vector3_t EminusC;
  subtract(&baseVector, &cVec, &EminusC);
  
  float DdotE = dot(theDir, EminusC);
  float DdotD = dot(theDir, theDir);
  float EdotE = dot(EminusC, EminusC);

  float radical = DdotE*DdotE - DdotD*(EdotE - radius*radius);
  
  sphere_data_t* sdata = (sphere_data_t*)data;
  return false;
}

static bool sfc_hit_sphere(void* data, ray3_t* ray, float t0,
        float t1, hit_record_t* hit) 
{
static bool sfc_hit_sphere(void* data, ray3_t* ray, float t0,
			   float t1, hit_record_t* hit)
{
  point3_t theBase = (*ray).base;
  vector3_t theDir = (*ray).dir;
  float px = theBase.x;
  float py = theBase.y;
  float pz = theBase.z;
  float vx = theDir.x;
  float vy = theDir.y;
  float vz = theDir.z;
  vector3_t baseVector;
  baseVector.x = px;
  baseVector.y = py;
  baseVector.z = pz;
  float DdotE = dot(theDir, baseVector);
  float DdotD = dot(theDir, theDir);
  float EdotE = dot(baseVector, baseVector);
  
  sphere_data_t* sdata = (sphere_data_t*)data;
  return false ;
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

