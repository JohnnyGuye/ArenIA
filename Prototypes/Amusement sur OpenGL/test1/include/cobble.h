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
        * Get a vector tab with all the colors possibly drawable
        **/
        Vector3* GetColorset();

        /**
        * Change the profil color
        * @param newColor the rvb color, ranging from 0 to 1 for each part
        **/
        void SetProfilColor(Vector3 newColor);

        /**
        * Change the profil color
        *
        * @param r The red part
        * @param v The green part
        * @param b The blue part
        **/
        void SetProfilColor(float r, float v, float b);

        /**
        * Draw the Front side of the form
        **/
        void Draw(const sf::Time& time) const;

        /**
        *       Draw the Back side of the form
        **/
        void DrawBack(const sf::Time& time) const;

    private:
        //Draw a face of the cobble
        void DrawFace(const Vector3 a, const Vector3 b, const Vector3 c, Vector3 d, const Vector3 Color) const;

        //Draw lines of the cobble
        void DrawLine(const Vector3 a, const Vector3 b) const;

    protected:
        float   m_aSide,        /// The length of the a side
                m_bSide,         /// The length of the b side
                m_cSide;        /// The length of the c side
        Vector3 m_points[8];    ///An array containing all the points for this form
        Vector3 m_color[6];     ///An array containing the panel of colors drawable on faces

        bool m_profil;  ///True if you have to display the profil
        Vector3 m_profil_color; ///The color of this profil
};

#endif // Cobble_H
