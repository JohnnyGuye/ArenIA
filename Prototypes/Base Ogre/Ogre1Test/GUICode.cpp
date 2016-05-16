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
	text_ = layer->createMarkupText(14, pos_.x, pos_.y, Ogre::StringUtil::BLANK);
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

	for(it = start; it != end; it++)
	{
		for(unsigned int i = 0; i < (*it).length() ; i++)
		{
			switch ((*it).at(i))
			{
			case '\t':
				ss << "    ";
			default:
				ss << (*it).at(i);
			}
		}
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
***************** Flow Chart AREA ************************
*********************************************************/
GUI::FlowChartArea::FlowChartArea(const Ogre::Vector2& pos,const Ogre::Vector2& dim)
	: dirty_(true),
	initialised_(false),
	pos_(pos),
	dim_(dim)
{
}

void GUI::FlowChartArea::init(Gorilla::Layer* layer)
{
	initialised_ = true;
	layerBack_ = layer;
	background_ = layerBack_->createRectangle(pos_, dim_);
	background_->background_image("rect_violet");
	blocs_.push_back(new Start(layer, Ogre::Vector2(600, 200)));
	blocs_.push_back(new End(layer, Ogre::Vector2(600, 400)));
}

GUI::FlowChartArea::~FlowChartArea()
{
	if(!initialised_)
		return;
}

void GUI::FlowChartArea::update()
{
	dirty_ = false;
}

bool GUI::FlowChartArea::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(dirty_)
		update();
	return true;
}

bool GUI::FlowChartArea::mouseMoved(const OIS::MouseEvent &arg)
{
	for(auto it = blocs_.begin() ; it != blocs_.end() ; it++)
	{
		(*it)->mouseMoved(arg);
	}
	return true;
}

bool GUI::FlowChartArea::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for(auto it = blocs_.begin() ; it != blocs_.end() ; it++)
	{
		(*it)->mousePressed(arg, id);
	}
	switch(id)
	case OIS::MB_Middle:
		
		break;
	return true;
}

bool GUI::FlowChartArea::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	for(auto it = blocs_.begin() ; it != blocs_.end() ; it++)
	{
		(*it)->mouseReleased(arg, id);
	}
	return true;
}

/*********************************************************
********************** BLOCS *****************************
*********************************************************/

/** Basic bloc **/
GUI::FlowChartArea::Bloc::Bloc(Gorilla::Layer* layer, Ogre::Vector2 pos, Ogre::Vector2 dim, const Ogre::String& sprite)
	: layer_(layer),
	onHold_(false),
	rect_(nullptr),
	hitBox_(nullptr)
{
	rect_ = layer_->createRectangle(pos, dim);
	rect_->background_image(sprite);
}

GUI::FlowChartArea::Bloc::~Bloc()
{
	layer_->destroyRectangle(rect_);
}

bool GUI::FlowChartArea::Bloc::mouseMoved(const OIS::MouseEvent &arg)
{
	Ogre::Vector2 mp((float)arg.state.X.abs, (float)arg.state.Y.abs);

	Ogre::Real nX = mp.x + topLeftDist_.x,
		nY = mp.y + topLeftDist_.y;

	bool intersect = false;
	if(onHold_)
	{
		rect_->left(nX);
		rect_->top(nY);
		hitBox_->left(nX);
		hitBox_->top(nY);
	}
	else
	{
		if(hitBox_->intersects(mp))
		{
			hitBox_->border(5, Gorilla::Colours::White);
			intersect = true;
		}
		else
		{
			hitBox_->border(2, Gorilla::Colours::Black);
			intersect = false;
		}
		
		
	}
	return intersect;
}

bool GUI::FlowChartArea::Bloc::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	Ogre::Vector2 mousePosition(Ogre::Real(arg.state.X.abs),Ogre::Real(arg.state.Y.abs));
	if(hitBox_->intersects(mousePosition))
	{
		onHold_ = true;
		topLeftDist_ = Ogre::Vector2(hitBox_->left(), hitBox_->top()) - mousePosition;
		return true;
	}
	return false;
}

bool GUI::FlowChartArea::Bloc::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if(onHold_) onHold_ = false;
	return true;
}

/* Bloc Start */
GUI::FlowChartArea::Start::Start(Gorilla::Layer* layer, Ogre::Vector2 pos)
	: Bloc(layer, pos, Ogre::Vector2(60,60), "hexa_orange")
{
	hitBox_ = layer_->createPolygon(pos.x, pos.y, 30, 6);
	hitBox_->angle(Ogre::Degree(90.f));
	hitBox_->no_background();
}

GUI::FlowChartArea::Start::~Start()
{
}

bool GUI::FlowChartArea::Start::attach(Arrow* arrow)
{
	next_ = arrow;
	return true;
}

/* Bloc End */
GUI::FlowChartArea::End::End(Gorilla::Layer* layer, Ogre::Vector2 pos)
	: Bloc(layer, pos, Ogre::Vector2(60,60), "hexa_violet")
{
	hitBox_ = layer_->createPolygon(pos.x, pos.y, 30, 6);
	hitBox_->angle(Ogre::Degree(90.f));
	hitBox_->no_background();
}

GUI::FlowChartArea::End::~End()
{
}

bool GUI::FlowChartArea::End::attach(Arrow* arrow)
{
	previous_ = arrow;
	return true;
}

/*********************************************************
************************* ARROWS *************************
*********************************************************/
GUI::FlowChartArea::Arrow::Arrow(Gorilla::Layer* layer)
	: head_(nullptr)
{
	layer_ = layer;
	head_ = layer->createRectangle(100 , 100, 20, 20);
	head_->background_image("mousepointer");
}

GUI::FlowChartArea::Arrow::~Arrow()
{
	layer_->destroyRectangle(head_);
}

void GUI::FlowChartArea::Arrow::setStart(Bloc* bloc)
{
	start_ = bloc;
}

void GUI::FlowChartArea::Arrow::setEnd(Bloc* bloc)
{
	end_ = bloc;
}

/*********************************************************
*********************** GUICode **************************
*********************************************************/
GUICode::GUICode(Ogre::Viewport* vp)
	: GUIContext(vp, "HUDFlowChart"),
	textArea_(nullptr),
	flowChartArea_(nullptr),
	mouse_(nullptr)
{
	width_ = screen_->getWidth();
	height_ = screen_->getHeight();

	layerBackground_ = screen_->createLayer(0);
	layerBase_ = screen_->createLayer(8);
	layerFlowChart_ = screen_->createLayer(10);
	layerTop_ = screen_->createLayer(15);

	mouse_ = layerTop_->createRectangle(width_ / 2, height_ / 2, 20, 20);
	mouse_->background_image("mousepointer");

	textArea_ = new GUI::TextArea(Ogre::Vector2(width_ * 0.1f, height_ * 0.01f), 
		Ogre::Vector2(width_ * 0.8f, height_ * 0.98f));
	flowChartArea_ = new GUI::FlowChartArea(Ogre::Vector2(width_ * 0.1f, height_ * 0.01f), 
		Ogre::Vector2(width_ * 0.8f, height_ * 0.98f));
	textArea_->init(layerBase_);
	flowChartArea_->init(layerFlowChart_);

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
	//textArea_->frameRenderingQueued(evt);
	flowChartArea_->frameRenderingQueued(evt);
	return true;
}

bool GUICode::mouseMoved(const OIS::MouseEvent &arg)
{
	Ogre::Real x((float)arg.state.X.abs), 
		y((float)arg.state.Y.abs);
	mouse_->left(x);
	mouse_->top(y);
	flowChartArea_->mouseMoved(arg);
	return true;
}

bool GUICode::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	flowChartArea_->mousePressed(arg, id);
	return true;
}

bool GUICode::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	flowChartArea_->mouseReleased(arg, id);
	return true;
}