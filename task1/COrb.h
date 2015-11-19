#ifndef CORB_H
#define CORB_H

#include <vector>

/**
	The class COrb represents an orb/satellite which may rotate around a father
	orb at a specific distance and can contain child orbs.	

	Example usage implementing a toy solar system:

	COrb sun; // this is the root of the scene graph
	COrb* earth;     // global pointers to access scene graph nodes
	COrb* moon;      // from different functions (e.g. for animation)
	COrb* apollo11; 

	void initSolarsystem()
	{
		// build a hierarchy 
		earth = sun.addChild(..);
		moon = earth->addChild(..);
		apollo11 = moon->addChild(..);	
	}
*/
class COrb
{
public:
	// c'tor
	COrb( float radius=1.f, float distance=0.f );
	// d'tor
	~COrb();
	
	// Draw planet and all satellites (traverse COrb scenegraph below this node).
	void draw();
	
	// Add a satellite as a child of this orb.
	// Returns a pointer to the newly created satellite.
	// Note that the returned object is managed by this class and should not be
	// deleted manually.
	COrb* addChild( float radius, float distance );	

	// set planet radius
	void setRadius( float radius );
    
	// set distance to father
	void setDistance( float dist );
    float getDistance();
	
    // set planet color
	void setColor( float r, float g, float b );
    
    ///
    /// angle, rotations, velocity members;
    ///
    
    // angular velocity
    float angularVelocity;
    
    // revolutions
    float revAngle;
    
    // rotations
    float rotAngle;
    float rotVelocity;

private:
	float m_radius;      // radius of planet
	float m_dist2father; // distance to father
	float m_color[3];    // color (red,green,blue)
	
	std::vector<COrb*> m_satellites; // child COrb nodes
};

#endif // CORB_H
