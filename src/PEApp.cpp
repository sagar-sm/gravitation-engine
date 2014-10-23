#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"
#include "cinder/Utilities.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"

#define NUM_INITIAL_PARTICLES 500

using namespace ci;
using namespace ci::app;
using namespace std;

class PEApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    // PARAMS
    params::InterfaceGlRef	mParams;
    
    // CAMERA
    CameraPersp			mCam;
    Quatf				mSceneRotation;
    Vec3f				mEye, mCenter, mUp;
    Vec3f               mNewPos, mNewVel;
    float               mNewRadius, mNewMass;
    float				mCameraDistance;
    bool                mEnableLight;
    
    ParticleSystem      system;
    float				mZoneRadius;


};

void PEApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1280, 720 );
    settings->setFrameRate( 60.0f );
}

void PEApp::setup()
{
    
    mZoneRadius		= 30.0f;
    mEnableLight    = false;
    
    // SETUP CAMERA
    mCameraDistance = 500.0f;
    mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
    mCenter			= Vec3f::zero();
    mUp				= Vec3f::yAxis();
    mNewPos           = Vec3f(100, 10, 0);
    mNewVel         = Vec3f(0, 0.5, 0);
    mNewMass        = 1;
    mNewRadius      = 3;
    mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    // SETUP PARAMS
    mParams = params::InterfaceGl::create( "Gravitation", Vec2i( 200, 520 ) );
    mParams->addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
    mParams->addSeparator();
    mParams->addParam( "Eye Distance", &mCameraDistance, "min=-5000.0 max=10500.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams->addSeparator();
    mParams->addParam( "Enable Lights", &mEnableLight, "key=l" );
    mParams->addSeparator();
    mParams->addParam("New Pos", &mNewPos, "step=10.0 keyIncr=p keyDecr=P");
    mParams->addSeparator();
    mParams->addParam("New Velocity", &mNewVel, "step=10.0 keyIncr=v keyDecr=V");
    mParams->addSeparator();
    mParams->addParam("New Radius", &mNewRadius, "step=10.0 keyIncr=r keyDecr=R");
    mParams->addSeparator();
    mParams->addParam("New Mass", &mNewMass, "step=5.0 keyIncr=m keyDecr=M");
    
    
    // CREATE PARTICLE SYSTEM
    //system.add( NUM_INITIAL_PARTICLES );
    system.add( Particle(Vec3f(10, 10, 0), Vec3f(0, 0, 0), 20, 200) );
    system.add( Particle(Vec3f(290, 10, 0), Vec3f(0, 1.2, 0), 9 , 20) );
    system.add( Particle(Vec3f(330, 10, 0), Vec3f(0, 0.3, 0), 3, 5) );
    
    
}

void PEApp::mouseDown( MouseEvent event )
{
    mNewPos = Vec3f(event.getX()-getWindowWidth()/2, getWindowHeight()/2 - event.getY(), mNewPos.z);
    system.add( Particle(mNewPos, mNewVel, mNewRadius, mNewMass) );
}

void PEApp::update()
{
    // UPDATE CAMERA
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    // UPDATE PARTICLE CONTROLLER AND PARTICLES
    system.update();
}

void PEApp::draw()
{
    gl::clear( Color( 0, 0, 0 ), true );
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    if(mEnableLight){
        glEnable( GL_LIGHTING );
        // Enable light0:
        glEnable( GL_LIGHT0 );
    }
    else {
        glDisable(GL_LIGHTING);
    }
    // DRAW PARTICLES
    system.draw();
    
    // DRAW PARAMS WINDOW
    mParams->draw();
}

CINDER_APP_NATIVE( PEApp, RendererGl )
