#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <string>

#include "cobble.h"
#include "Rectangle.h"
#include "MarkZero.h"

class AppWindow
{
        public:
                AppWindow();
                AppWindow(unsigned int width,
                          unsigned int length,
                          const char* title,
                          const sf::ContextSettings
                          );
                AppWindow(const AppWindow& other);
                AppWindow& operator=(const AppWindow&);
                virtual ~AppWindow();

                //Main application loop
                void Run();

                //Framework methods
                virtual bool Init();
                /** \brief Initis the Application
                ** create contexts for OpenGL and other pre-calcs some features
                **/

                virtual void Update(sf::Time& time);
                /** \brief update the calcs for the game
                ** Calculation of all between two frames
                **/

                virtual void Render(sf::Time& time);
                /** \brief Render the OpenGL back scene and the SFML 2D layer
                **  Draw all forms from OpenGL contexts and SFML contexts
                **/

                virtual void Cleanup();
                /** \brief Cleans the board
                **/

        protected:

                float   m_width,
                        m_height;

                sf::Clock m_clock;
                sf::Window m_window;


                MarkZero m_mark;
                Cobble m_cob1;

};


#endif // APPWINDOW_H
