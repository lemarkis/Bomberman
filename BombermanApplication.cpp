
#include "BombermanApplication.h"

//---------------------------------------------------------------------------
BombermanApplication::BombermanApplication(void)
{
}
//---------------------------------------------------------------------------
BombermanApplication::~BombermanApplication(void)
{
}

//---------------------------------------------------------------------------
void BombermanApplication::createScene(void)
{
	// Create your scene here
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5), Ogre::ColourValue(0.5, 0.5, 0.5), Ogre::Vector3(1, 1, -1));

	Ogre::v1::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh"); //resolution path to mesh

}
//---------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#ifdef __cplusplus
extern "C" {
#endif

	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
	{
		// Create application object
		BombermanApplication app;

		try
		{
			app.go();
		}
		catch(Ogre::Exception& e)
		{
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
