#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "COrb.h"

// use this function to draw a sphere of specific radius at the current origin
void drawSphere( float radius );

void COrb::draw()
{
    glPushMatrix();
    
        glRotatef(revAngle, 0.0, 1.0, 0.0);
        glTranslatef(m_dist2father, 0.0, 0.0);
        glRotatef(rotAngle, 0.0, 1.0, 0.0);
    
        glPushMatrix();
            glRotatef(90, 1.0, 0.0, 0.0);
            glColor3f(m_color[0], m_color[1], m_color[2]);
            drawSphere(m_radius);
        glPopMatrix();
    
    if (!m_satellites.empty()){
        for (int i = 0; i < m_satellites.size(); i++){
            COrb* orb = m_satellites[i];
            orb->draw();
        }
    }
       
    glPopMatrix();
}

//==============================================================================
//  COrb implementation
//==============================================================================

// helper function to draw a sphere
void drawSphere( float radius )
{
	static GLUquadric *qsphere = 0;
	static bool firstCall = true;
	
    if( firstCall )
	{
		qsphere = gluNewQuadric();
		firstCall = false;
	}
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	gluSphere( qsphere, radius, 32,32 );
}

COrb::COrb( float radius, float distance ):
m_radius(radius),
m_dist2father(distance)
{ 	
	setColor(1, 1, 1);   // default color = white
    
    revAngle = rotAngle = angularVelocity = 0.0f;
	rotVelocity = 10;
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

float COrb::getDistance()
{
	return m_dist2father;
}

// set planet color
void COrb::setColor( float r, float g, float b )
{ 
	m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
}
