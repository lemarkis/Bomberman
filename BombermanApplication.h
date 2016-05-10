
#ifndef __BombermanApplication_h_
#define __BombermanApplication_h_

#include "BaseApplication.h"
#include "OgreEntity.h"

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
