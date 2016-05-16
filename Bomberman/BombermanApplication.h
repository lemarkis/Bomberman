/*
-----------------------------------------------------------------------------
Filename:    BombermanApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
	  |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#ifndef __BombermanApplication_h_
#define __BombermanApplication_h_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class BombermanApplication : public BaseApplication
{
public:
	BombermanApplication(void);
	virtual ~BombermanApplication(void);

protected:
	virtual void createScene(void);
};

//---------------------------------------------------------------------------

#endif // #ifndef __BombermanApplication_h_

//---------------------------------------------------------------------------
