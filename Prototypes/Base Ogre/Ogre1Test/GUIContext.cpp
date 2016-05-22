#include "GUIContext.h"
#include "ExceptionArenIA.h"
#include <OGRE\OgreLogManager.h>

using namespace Ogre;
using namespace Gorilla;

#pragma warning(disable : 4355)
//-------------------------------------------------------------PANE
GUI::Pane::Pane(Ogre::Vector2 position, Ogre::Vector2 dimension)
	: parent_(this),
	dirty_(true),
	initialized_(false),
	position_(position),
	dimension_(dimension)
{
}

GUI::Pane* GUI::Pane::init(Layer* layer)
{
	layer_ = layer;
	back_ = layer_->createRectangle(position_, dimension_);
	back_->background_colour(Gorilla::Colours::Sienna);
	back_->border(2, Gorilla::Colours::Brown);
	return this;
}

void GUI::Pane::hide()
{
	if(shown_)
	{
		for(auto it = childrens_.begin(); it != childrens_.end(); it++)	(*it)->hide();
		shown_ = false;
	}
}

void GUI::Pane::show()
{
	if(!shown_)
	{
		for(auto it = childrens_.begin(); it != childrens_.end(); it++)	(*it)->show();
		shown_ = true;
	}
}

bool GUI::Pane::isVisible()
{
	return shown_;
}

GUI::Pane::~Pane()
{
	for(auto it = childrens_.begin(); it != childrens_.end(); it++)	delete (*it);
}


void GUI::Pane::setPosition(Ogre::Vector2 pos)
{
	position_ = pos;
}

void GUI::Pane::resize(Ogre::Vector2 dim)
{
	dimension_ = dim;
}

bool GUI::Pane::intersect(Ogre::Vector2 point)
{
	if(point.x < position_.x || 
		(point.x > position_.x + dimension_.x) ||
		(point.y < position_.y) || 
		(point.y > position_.y + dimension_.y) )
		return false;
	return true;
}

bool GUI::Pane::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(dirty_)
	{
		dirty_ = update(evt);
		for(auto it = childrens_.begin(); it != childrens_.end(); it++)
		{
			(*it)->frameRenderingQueued(evt);
		}
	}
	return true;
}

bool GUI::Pane::update(const Ogre::FrameEvent& evt)
{
	return false;
}

void GUI::Pane::dirty()
{
	dirty_ = true;
}

bool GUI::Pane::keyPressed( const OIS::KeyEvent& arg)
{
	for(auto it = childrens_.begin(); it != childrens_.end(); it++)
	{
		(*it)->keyPressed(arg);
	}
    return true;
}

bool GUI::Pane::keyReleased(const OIS::KeyEvent &arg)
{
    for(auto it = childrens_.begin(); it != childrens_.end(); it++)
	{
		(*it)->keyReleased(arg);
	}
    return true;
}

bool GUI::Pane::mouseMoved(const OIS::MouseEvent &arg)
{
	Ogre::Vector2 mouse(Ogre::Real(arg.state.X.abs), Ogre::Real(arg.state.Y.abs));
	for(auto it = childrens_.begin(); it != childrens_.end(); it++)
	{
		(*it)->mouseMoved(arg);
	}
	if(!intersect(mouse))	return false;
    return true;
}

bool GUI::Pane::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	Ogre::Vector2 mouse(Ogre::Real(arg.state.X.abs), Ogre::Real(arg.state.Y.abs));
	if(!intersect(mouse))	return false;
	for(auto it = childrens_.begin(); it != childrens_.end(); it++)
	{
		(*it)->mousePressed(arg, id);
	}
    return true;
}

bool GUI::Pane::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	Ogre::Vector2 mouse(Ogre::Real(arg.state.X.abs), Ogre::Real(arg.state.Y.abs));
	for(auto it = childrens_.begin(); it != childrens_.end(); it++)
	{
		(*it)->mouseReleased(arg, id);
	}
	if(!intersect(mouse))	return false;
    return true;
}

//----------------------------------------------------------BUTTON
GUI::Button::Button(Ogre::Vector2 pos, Ogre::Vector2 dim)
	: Pane(pos, dim),
	clicked_(false)
{
}

GUI::Button::~Button()
{
	if(initialized_)
	{
		layer_->destroyRectangle(back_);
		layer_->destroyCaption(text_);
	}
}

GUI::Button* GUI::Button::init(Gorilla::Layer* layer)
{
	if(!initialized_)
	{
		initialized_ = true;
		layer_ = layer;
		back_ = layer->createRectangle(position_, dimension_);
		text_ = layer->createCaption(14, position_.x, position_.y+dimension_.y/2, "Bouton");
		text_->align(Gorilla::TextAlign_Centre);
		resize(dimension_);
	}
	return this;
}

void GUI::Button::setBackground(const std::string& sprite_name)
{
	back_->background_image(sprite_name);
}

void GUI::Button::setBackground(const Ogre::ColourValue& colour)
{
	back_->background_colour(colour);
}

void GUI::Button::setText(const std::string& text)
{
	text_->text(text);
}

void GUI::Button::setPosition(Ogre::Vector2 position)
{	
	Ogre::Vector2 translate(position-position_);
	GUI::Pane::setPosition(position);
	back_->position(back_->position() + translate);
	text_->left(text_->left()+translate.x);	text_->top(text_->top()+translate.y);
}

void GUI::Button::resize(Ogre::Vector2 dimension)
{
	GUI::Pane::resize(dimension);
	back_->width(dimension.x);
	back_->height(dimension.y);
	text_->width(dimension_.x);	
	text_->height(dimension_.y);
}

bool GUI::Button::mouseMoved(const OIS::MouseEvent& arg)
{
	if(GUI::Pane::mouseMoved(arg))
	{
		back_->border(2, Gorilla::Colours::AntiqueWhite);
		return true;
	}
	else
	{
		back_->border(0, Gorilla::Colours::AntiqueWhite);
		return false;
	}
}

bool GUI::Button::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	Ogre::Vector2 mouse(Ogre::Real(arg.state.X.abs), Ogre::Real(arg.state.Y.abs));
	if(intersect(mouse))
	{
		onClick();
		return (clicked_ = true);
	}
	return false;
}

bool GUI::Button::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	if(clicked_)
	{
		onRelease();
		clicked_ = false;
	}
	return false;
}

void GUI::Button::onClick()
{
	back_->border(2, Gorilla::Colours::White);
}

void GUI::Button::onRelease()
{
	back_->border(1, Gorilla::Colours::Brown);
}

void GUI::Button::hide()
{
	GUI::Pane::hide();
	back_->no_background();
	back_->no_border();
	text_->text("");
}

void GUI::Button::show()
{
	GUI::Pane::show();
	back_->background_colour(Gorilla::Colours::Sienna);
	back_->border(1, Gorilla::Colours::Brown);
	text_->text("Button");
}
//--------------------------------------------------------------------------SLIDEBAR

GUI::SlideBar::SlideBar(Ogre::Vector2 position, Ogre::Vector2 dimension, GUI::SlideBar::Orientation orientation)
	: Pane(position, dimension),
	bar_(1,0,0),
	orientation_(orientation),
	clickTop_(false),
	clickBot_(false),
	clickScroll_(false)
{
}

GUI::SlideBar* GUI::SlideBar::init(Gorilla::Layer* layer)
{
	if(initialized_)	return this;
	layer_ = layer;

	//Common
	back_ = layer_->createRectangle(position_, dimension_);
	arrowTop_ = layer_->createRectangle(position_);

	if(orientation_ == VERTICAL)
	{
		Real sqx(dimension_.x);
		
		arrowTop_->width(sqx);	arrowTop_->height(sqx);
		arrowBot_ = layer_->createRectangle(position_ + Vector2(0, dimension_.y - sqx), Vector2(sqx, sqx));
		scroll_ = layer_->createRectangle(position_ + Vector2(0, sqx), Vector2(dimension_.x, (dimension_.y - 2*sqx) * 0.2f));
	}
	else
	{
		Real sqy(dimension_.y);
		arrowTop_->width(sqy);	arrowTop_->height(sqy);
		arrowBot_ = layer->createRectangle( position_.x + dimension_.x - sqy, position_.y, sqy, sqy);
		scroll_ = layer_->createRectangle( position_.x + sqy, position_.y, (dimension_.x - 2 * sqy) * 0.2f, dimension_.y);
	}

	show();
	return this;	
}

GUI::SlideBar::~SlideBar()
{
	if(initialized_)
	{
		layer_->destroyRectangle(back_);
		layer_->destroyRectangle(scroll_);
		layer_->destroyRectangle(arrowTop_);
		layer_->destroyRectangle(arrowBot_);
	}
}

float GUI::SlideBar::getCurrent() const
{
	return bar_.getRatio();
}

void GUI::SlideBar::setPosition(Ogre::Vector2 position)
{
	Ogre::Vector2 translate(position-position_);
	GUI::Pane::setPosition(position);
	back_->position(back_->position()+translate);
	arrowTop_->position(arrowTop_->position()+translate);
	arrowBot_->position(arrowBot_->position()+translate);
	scroll_->position(scroll_->position()+translate);
}

void GUI::SlideBar::resize(Ogre::Vector2 dimension)
{
	//TODO
}

void GUI::SlideBar::setCurrent(float ratio)
{
	if(orientation_ == VERTICAL)
	{
		if(ratio > 1 ) ratio = 1;
		if(ratio < 0) ratio = 0;

		bar_.setCurrent(ratio);

		Real maxTop(arrowTop_->top() + arrowTop_->height());
		Real maxBot(arrowBot_->top() - scroll_->height());
		scroll_->top((maxBot - maxTop) * ratio + maxTop);
	}
}

void GUI::SlideBar::regionShown(Real percent)
{
	if(orientation_ == GUI::SlideBar::VERTICAL)
	{
		scroll_->height(percent * (dimension_.y - arrowBot_->height() * 2));
	}
}

void GUI::SlideBar::hide()
{
	GUI::Pane::hide();
	back_->no_background();
	back_->no_border();
	arrowTop_->no_background();
	arrowTop_->no_border();
	arrowBot_->no_background();
	arrowBot_->no_border();
	scroll_->no_background();
	scroll_->no_border();
}

void GUI::SlideBar::show()
{
	GUI::Pane::show();
	back_->background_colour(Gorilla::Colours::SlateGray);
	back_->border(1, Gorilla::Colours::Grey);
	arrowTop_->background_image("arrow_up");
	arrowBot_->background_image("arrow_down");
	scroll_->background_colour(Gorilla::Colours::LightGray);
}

bool GUI::SlideBar::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	Ogre::Vector2 mouse(Ogre::Real(arg.state.X.abs), Ogre::Real(arg.state.Y.abs));
	if(intersect(mouse))
	{
		if(scroll_->intersects(mouse))
			clickScroll_ = true;
		else if(arrowBot_->intersects(mouse))
		{
			clickBot_ = true;
		}
		else if(arrowTop_->intersects(mouse))
		{
			clickTop_ = true;
		}
		if(clickBot_)
		{
			moveScroll(10, true);
		}
		else if(clickTop_)
		{
			moveScroll(-10, true);
		}
		return true;
	}
	return false;
}

bool GUI::SlideBar::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	if(clickTop_)		clickTop_ = false;
	if(clickBot_)		clickBot_ = false;
	if(clickScroll_)	clickScroll_ = false;
	return true;
}

bool GUI::SlideBar::mouseMoved(const OIS::MouseEvent& arg)
{
	
	if(clickScroll_)
	{
		Ogre::Vector2 pos(arg.state.X.rel + scroll_->left(), arg.state.Y.rel + scroll_->top());
		if(orientation_ == VERTICAL)
			moveScroll(pos.y);
		else
			moveScroll(pos.x);
	}
	return true;
}

bool GUI::SlideBar::moveScroll(Real val, bool relative)
{
	if(orientation_ == VERTICAL)
	{
		if(relative)
			val += scroll_->top();
		Real maxTop(arrowTop_->top() + arrowTop_->height());
		Real maxBot(arrowBot_->top() - scroll_->height());
	
		if(val < maxTop)		val = maxTop;
		else if(val > maxBot)	val = maxBot;

		scroll_->top( val);

		if(maxTop == maxBot)
			setCurrent(0);
		else
			setCurrent((scroll_->top() - maxTop) / (maxBot - maxTop));
	}
	return true;
}

//----------------------------------------------------------------------LIST
inline bool isVertical(GUI::List::Orientation rhs)
{
	return (rhs == GUI::List::LEFT) || (rhs == GUI::List::RIGHT);
}

GUI::List::List(Ogre::Vector2 position ,Ogre::Vector2 dimension, Orientation orientation)
	: Pane(position, dimension),
	slidebar_(nullptr),
	orientation_(orientation),
	spacing_(0.0f),
	lengthItems_(.0f),
	beginLengthItems_(.0f)
{
}

GUI::List* GUI::List::init(Gorilla::Layer* layer)
{
	if(initialized_)	return this;
	initialized_ = true;
	layer_ = layer;
	back_ = layer->createRectangle(position_, dimension_);

	Ogre::Vector2 dim(20.f, dimension_.y);
	Ogre::Vector2 pos(position_.x + dimension_.x - dim.x, position_.y);
	slidebar_= new SlideBar(pos, dim, (isVertical(orientation_) ? SlideBar::VERTICAL : SlideBar::HORIZONTAL));
	addChild(slidebar_->init(layer));
	return this;
}

GUI::List::~List()
{
	if(initialized_)
	{
		layer_->destroyRectangle(back_);
	}
}

int GUI::List::addElement(Pane* pane)
{
	Ogre::Real newW, newH, newX, newY;
	
	newX = position_.x; 
	newY = position_.y;
	if(isVertical(orientation_))
	{
		//Resize pane
		newW = dimension_.x - slidebar_->getDimension().x;
		newH = pane->getDimension().y;

		//Move pane
		if(!(blockList_.size() == 0))
		{
			Pane* p = blockList_.back();
			newY = lengthItems_ + spacing_;
		
		}
		lengthItems_ += newH + spacing_;
		Ogre::Real ratio(dimension_.y / lengthItems_);
		slidebar_->regionShown(ratio > 1 ? 1.f : ratio);
	}
	else
	{
		//Resize pane
		newW = pane->getDimension().x,
		newH = dimension_.y - slidebar_->getDimension().y;

		//Move pane
		if(!(blockList_.size() == 0))
		{
			Pane* p = blockList_.back();
			newX = lengthItems_ + spacing_;
		
		}
		lengthItems_ += newY + spacing_;
		Ogre::Real ratio(dimension_.x / lengthItems_);
		slidebar_->regionShown(ratio > 1 ? 1.f : ratio);
	}
	pane->resize(Ogre::Vector2(newW, newH ));
	pane->setPosition(Ogre::Vector2(newX, newY));
	blockList_.push_back(pane);
	addChild(pane);
	return blockList_.size();
}

void GUI::List::setPosition(Ogre::Vector2 position)
{
	GUI::Pane::setPosition(position);
}

void GUI::List::resize(Ogre::Vector2 dimension)
{

}

void GUI::List::showSlideBar(bool show)
{
	if(show)
		slidebar_->show();
	else
		slidebar_->hide();
}

void GUI::List::setSpacing(float val)
{
	spacing_ = val;
}

bool GUI::List::mouseMoved(const OIS::MouseEvent& arg)
{
	if(isVertical(orientation_))
	{
		beginLengthItems_ = (slidebar_->getCurrent() * lengthItems_);
		Real decay(position_.y - beginLengthItems_);
		if(blockList_.size() != 0)
		{
			auto e = *(blockList_.begin());
			e->setPosition(Vector2(e->getPosition().x, decay));
		}
		auto previous = blockList_.begin();
		auto it = previous;
		for(it++; it != blockList_.end() ; it++)
		{
			(*it)->setPosition(
				Vector2((*it)->getPosition().x,
				(*previous)->getPosition().y + (*previous)->getDimension().y + spacing_
				));
			previous = it;	
		}
	}
	return GUI::Pane::mouseMoved(arg);
}

//----------------------------------------------------------------------------
//-------------------------- GUIContext --------------------------------------
//----------------------------------------------------------------------------
GUIContext::GUIContext(Ogre::Viewport* vp, const Ogre::String &atlas)
	: root_(this),
	parent_(this),
	screen_(nullptr),
	children_(),
	mouseVisibility_(true)
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
		
			width_ = screen_->getWidth();
			height_ = screen_->getHeight();

			layerMouse_ = screen_->createLayer(15);
			mouse_ = layerMouse_->createRectangle(0, 0, 20, 20);
			mouse_->background_image("mousepointer");
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

GUIContext::~GUIContext(void)
{
	
	for(std::list<GUIContext*>::iterator it = children_.begin(); it != children_.end() ; it++)
	{
		if( (*it) ) delete (*it);
	}
	if(root_ == this)
	{
		silverback_->destroyScreen(screen_);
	}
}

Ogre::String GUIContext::getAtlasName() const
{
	return screen_->getAtlas()->get2DMaterialName();
}

GUIContext* GUIContext::addChild(GUIContext* elmnt)
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

GUI::Pane* GUIContext::addElement(GUI::Pane* pane)
{
	panes_.push_back(pane);
	return pane;
}

bool GUIContext::IsMouseVisible() const
{
	return mouseVisibility_;
}

void GUIContext::mouseVisibility(bool visible)
{
	if(visible && ! mouseVisibility_)
	{
		layerMouse_->show();
	}
	else if( !visible && mouseVisibility_)
	{
		layerMouse_->hide();
	}
	mouseVisibility_ = visible;
}

bool GUIContext::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	for(auto it = panes_.begin(); it != panes_.end() ; it++)
		(*it)->frameRenderingQueued(evt);
	return true;
}

//Handlers
bool GUIContext::keyPressed(const OIS::KeyEvent &arg)
{
	for(auto it = panes_.begin(); it != panes_.end() ; it++)
		(*it)->keyPressed(arg);
	return true;
}

bool GUIContext::keyReleased(const OIS::KeyEvent &arg)
{
	for(auto it = panes_.begin(); it != panes_.end() ; it++)
		(*it)->keyReleased(arg);
	return true;
}

bool GUIContext::mouseMoved(const OIS::MouseEvent &arg)
{
	Ogre::Real x((float)arg.state.X.abs), 
		y((float)arg.state.Y.abs);
	mouse_->left(x);
	mouse_->top(y);
	for(auto it = panes_.begin(); it != panes_.end() ; it++)
		(*it)->mouseMoved(arg);
	return true;
}

bool GUIContext::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for(auto it = panes_.begin(); it != panes_.end() ; it++)
		(*it)->mousePressed(arg, id);
	return true;
}

bool GUIContext::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for(auto it = panes_.begin(); it != panes_.end() ; it++)
		(*it)->mouseReleased(arg, id);
	return true;
}
