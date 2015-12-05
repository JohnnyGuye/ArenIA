#ifndef MARKZERO_H
#define MARKZERO_H

#include "Cone.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

class MarkZero
{
    public:
        /** Default constructor */
        MarkZero();
        /** Default destructor */
        virtual ~MarkZero();

        //Framework methods
        virtual void Update(sf::Time& time);
        virtual void Draw(const sf::Time& time) const;
    protected:
};

#endif // MARKZERO_H
