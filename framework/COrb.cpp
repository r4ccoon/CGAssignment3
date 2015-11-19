#include "COrb.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

// use this function to draw a sphere of specific radius at the current origin
void drawSphere( float radius );

void COrb::draw()
{
	//////////////////////////////////////////////////////////////////////
	// TO IMPLEMENT:
	// 
	// - apply scenegraph node transformations
	// - draw this orb
	// - further traverse scenegraph by calling childrens draw() function
	//////////////////////////////////////////////////////////////////////	
}


//==============================================================================
//  COrb implementation
//==============================================================================

// helper function to draw a sphere
void drawSphere( float radius )
{
	static GLUquadric *qsphere=0;
	static bool firstCall=true;
	if( firstCall ) 
	{
		qsphere = gluNewQuadric();
		firstCall = false;
	}
	gluSphere( qsphere, radius, 32,32 );
}

COrb::COrb( float radius, float distance )
: m_radius(radius), m_dist2father(distance)
{ 	
	setColor(1,1,1);   // default color = white
}

// d'tor
COrb::~COrb()
{
	for( int i=0; i < m_satellites.size(); ++i )
		delete m_satellites[i];				
}

// add a satellite
COrb* COrb::addChild( float radius, float distance )
{
	COrb* sat = new COrb(radius,distance);
	m_satellites.push_back( sat );
	return sat;
}

// set planet radius
void COrb::setRadius( float radius ) 
{ 
	m_radius = radius; 
}

// set distance to father
void COrb::setDistance( float dist ) 
{ 
	m_dist2father = dist; 
}	

// set planet color
void COrb::setColor( float r, float g, float b )
{ 
	m_color[0]=r; m_color[1]=g; m_color[2]=b; 
}
