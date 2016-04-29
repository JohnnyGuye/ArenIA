#include "GUICode.h"


GUICode::GUICode(Ogre::Viewport* vp)
	: GUIElement(vp, "HUD")
{
	width_ = screen_->getWidth();
	height_ = screen_->getHeight();

	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	layerTop_ = screen_->createLayer(15);

	codeArea_ = layerBase_->createMarkupText(14, width_ * 0.2f, height_ * 0.01f, "Code Charging ...");
	codeArea_->size(width_ * 0.6f, height_ * 0.9f);
	codeArea_->background(Ogre::ColourValue(0.1f,0.07f, 0.08f));

	loadFile("default.lua");
}

GUICode::~GUICode(void)
{
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
		file << read << std::endl;
	}
	codeArea_->text(file.str());

	code.close();
}

bool GUICode::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

