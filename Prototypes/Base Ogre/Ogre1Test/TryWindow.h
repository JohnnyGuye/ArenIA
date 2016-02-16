/*
-----------------------------------------------------------------------------
Filename:    TryWindow.h
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

#ifndef __TryWindow_h_
#define __TryWindow_h_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class TryWindow : public BaseApplication
{
public:
    TryWindow(void);
    virtual ~TryWindow(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TryWindow_h_

//---------------------------------------------------------------------------
