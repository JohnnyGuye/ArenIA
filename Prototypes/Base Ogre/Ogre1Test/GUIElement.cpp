#include "GUIElement.h"
#include "ExceptionArenIA.h"
#include <OGRE\OgreLogManager.h>

#pragma warning(disable : 4355)

GUIElement::GUIElement(Ogre::Viewport* vp, const Ogre::String &atlas)
	: root_(this),
	parent_(this),
	screen_(nullptr),
	children_()
{
	
	if(!Gorilla::Silverback::getSingletonPtr())
		silverback_ = new Gorilla::Silverback();
	else
		silverback_ = Gorilla::Silverback::getSingletonPtr();

	try
	{
		if((atlas != "") && (vp!=nullptr))
		{
			silverback_->loadAtlas(atlas);
			screen_ = silverback_->createScreen(vp, atlas);
		}
	}
	catch(const std::exception e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.what(), "Atlas not loaded.", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
		exit(-1);
	}
}

GUIElement::~GUIElement(void)
{
	
	for(std::list<GUIElement*>::iterator it = children_.begin(); it != children_.end() ; it++)
	{
		if( (*it) ) delete (*it);
	}
	if(root_ == this)
	{
		silverback_->destroyScreen(screen_);
	}
}
//---------------------------------------------------------------------
Ogre::String GUIElement::getAtlasName() const
{
	return screen_->getAtlas()->get2DMaterialName();
}

//---------------------------------------------------------------------
GUIElement* GUIElement::addChild(GUIElement* elmnt)
{
	elmnt->root_ = this->root_;
	elmnt->parent_ = this;
	if(elmnt->screen_)
	{
		silverback_->destroyScreen(elmnt->screen_);;
		elmnt->screen_ = this->root_->screen_;
	}
	children_.push_back(elmnt);
	return elmnt;
}

bool GUIElement::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}