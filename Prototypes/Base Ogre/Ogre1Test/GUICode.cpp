#include "GUICode.h"

#include <OGRE\OgrePrerequisites.h>

/*********************************************************
*********************** TEXT AREA ************************
*********************************************************/
GUI::TextArea::TextArea(const Ogre::Vector2& pos,const Ogre::Vector2& dim)
	: dirty_(true),
	initialised_(false),
	pos_(pos),
	dim_(dim)
{
}

void GUI::TextArea::init(Gorilla::Layer* layer)
{
	initialised_ = true;
	layerText_ = layer;
	text_ = layer->createMarkupText(9, pos_.x, pos_.y, Ogre::StringUtil::BLANK);
	text_->size(dim_.x, dim_.y);
	background_ = layerText_->createRectangle(pos_.x, pos_.y, dim_.x, dim_.y);
	background_->background_colour(Gorilla::Colours::AliceBlue);
	background_->border(5, Gorilla::Colours::Azure);
}

GUI::TextArea::~TextArea()
{
	if(!initialised_)
		return;
	layerText_->destroyMarkupText(text_);
}

int GUI::TextArea::append(const Ogre::String& text)
{
	lines_.push_back(text);
	dirty_ = true;
	return lines_.size();
}

int GUI::TextArea::newLine(const Ogre::String& text)
{
	int lineNum = (int)(cursor_->top() / text_->getDefaultGlyphData()->mLineHeight);
	auto it = lines_.begin();
	for(int i = 0; i < lineNum; i++)
		it++;
	lines_.insert(it, text);
	dirty_ = true;
	return lineNum + 1;
}

void GUI::TextArea::update()
{
	dirty_ = false;

	std::list<Ogre::String>::iterator it, start, end;

	start = lines_.begin();
	end = lines_.end();

	Ogre::StringStream ss;
	int i = 0;
	for(it = start; it != end; it++)
	{
		
		ss << i << " : \t" << (*it) << std::endl;
		std::cout << ss.str() << std::endl;
		i++;
	}
	text_->text(ss.str());
}

bool GUI::TextArea::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(dirty_)
		update();
	return true;
}

/*********************************************************

*********************************************************/
GUICode::GUICode(Ogre::Viewport* vp)
	: GUIElement(vp, "HUD"),
	textArea_(nullptr)
{
	width_ = screen_->getWidth();
	height_ = screen_->getHeight();

	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	//layerTop_ = screen_->createLayer(15);

	textArea_ = new GUI::TextArea(Ogre::Vector2(width_ * 0.1f, height_ * 0.01f), 
		Ogre::Vector2(width_ * 0.8f, height_ * 0.98f));
	textArea_->init(layerBase_);

	loadFile("default.lua");
}

GUICode::~GUICode(void)
{
	delete textArea_;
}

bool GUICode::loadFile(const Ogre::String& fileName)
{
	std::stringstream ss;
	ss << "../IAs/" << fileName;

	std::stringstream file;

	std::ifstream code(ss.str().c_str());

	if(!code)	return false;

	std::string read;
	while(std::getline(code, read))
	{
		textArea_->append(read);
	}

	code.close();
	return true;
}

bool GUICode::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	textArea_->frameRenderingQueued(evt);
	return true;
}

