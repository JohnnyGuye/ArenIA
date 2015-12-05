#ifndef Cobble_H
#define Cobble_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "Rectangle.h"

class Cobble
{
    public:
        /**
        * \brief Create a cube.
        *
        * Creat a cube with a side-length equals to m_side
        */
        Cobble(float m_sides);

        /**
        * @param m_aSide the length of x-dimension
        * @param m_bSide the length of y-dimension
        * @param m_cSide the length of z-dimension
        * Create a Cobble.
        */
        Cobble(float aSide, float bSide, float cSide);

        //Cobble(const Cobble& other);
        //Cobble& operator=(const Cobble& other);

        /**
        * Destroy the Cobble
        */
        virtual ~Cobble();

        /**
        * Clone the Cobble without the texture
        */
        Cobble(const Cobble& other);

        /**
        * Clone the Cobble into another without texture
        */
        Cobble& operator=(const Cobble& other);

        /**
        * Draw the Front side of the form
        **/
        void Draw(const sf::Time& time) const;
        /**
        *       Draw the Back side of the form
        **/
        void DrawBack(const sf::Time& time) const;

    private:
        void DrawFace(const Vector3 a, const Vector3 b, const Vector3 c, Vector3 d, const Vector3 Color) const;
        void DrawLine(const Vector3 a, const Vector3 b) const;

    protected:
        float   m_aSide,
                m_bSide,
                m_cSide;
        Vector3 m_points[8];
        Vector3 m_color[8];

        bool m_profil;
        Vector3 m_profil_color;
};

#endif // Cobble_H
