#ifndef FORM3D_H
#define FORM3D_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Vector3.h"

class Form3D
{
	public:
		Form3D();
		/**
		* @brief create a 3D Form using these points
		*
		* @param Points is a tab with all the points
		* @param nbPoints is the number of points you want
		*/
		Form3D(Vector3 *Points, int &nbPoints );

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

		virtual ~Form3D();

    protected:
        //Draw a face of the form
        virtual void DrawFace(const Vector3 a, const Vector3 b, const Vector3 c, const Vector3 Color) const;

        //Draw lines of the form
        virtual void DrawLine(const Vector3 a, const Vector3 b) const;


	protected:
		int m_nbPoints;
		Vector3 *m_points; 	///An array containing all the points for this form
        Vector3 m_color[32];     ///An array containing the panel of colors drawable on faces

        bool m_profil;  ///True if you have to display the profil
        Vector3 m_profil_color; ///The color of this profil
};

#endif // FORM3D_H
