#pragma once

#include "GUIElement.h"

namespace GUI
{
	class TextArea
	{
	public:
		TextArea(const Ogre::Vector2& pos, const Ogre::Vector2& dim);
		virtual~TextArea();

		void init(Gorilla::Layer* layer);

		int append(const Ogre::String& text = "");
		int newLine(const Ogre::String& text = "");

		void update();

		bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	protected:
		std::list<Ogre::String>		lines_;
		Gorilla::MarkupText*		text_;
		Gorilla::Layer*				layerText_;
		Gorilla::Layer*				layerBack_;
		Gorilla::Rectangle*			background_;
		Gorilla::Rectangle*			cursor_;
		Ogre::Vector2				pos_;
		Ogre::Vector2				dim_;

		bool					dirty_;
		bool					initialised_;
		
	};
}

class GUICode :
	public GUIElement
{
public:
	GUICode(Ogre::Viewport*);
	~GUICode(void);

	bool GUICode::loadFile(const Ogre::String& fileName);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	Ogre::Real			width_,
						height_;
	Gorilla::Layer*		layerBase_;
	Gorilla::Layer*		layerBackground_;
	Gorilla::Layer*		layerTop_;

	GUI::TextArea*		textArea_;
};

