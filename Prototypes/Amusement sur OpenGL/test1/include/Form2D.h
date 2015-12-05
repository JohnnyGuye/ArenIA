#ifndef FORM2D_H
#define FORM2D_H

#include <Vector3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Form2D
{
    public:
        /** Default constructor */
        Form2D();
        /** Default destructor */
        virtual ~Form2D();
        /** Access m_height
         * \return The current value of m_height
         */
        virtual float GeHeight() { return m_height; }
        /** Access m_width
         * \return The current value of m_width
         */
        virtual float GetWidth() { return m_width; }

        void Transformation(float tfact = 1.f, float rfact = 1.f) const;

        //Setters
        /** Set m_rotation
         * \param rotation A vector with the angle in degres of rotation
         * around the axis, x, y and z
         */
        void SetRotation(Vector3 rotation);

        /** Set m_translation
         * \param translation A vector with the unit of distance between the
         * old position and the position where you want this form
         */
        void SetTranslation(Vector3 val);

        /** Set m_rotation
         * \param x rotation Gives the rotation degres around the x-axis
         * \param y rotation Gives the rotation degres around the y-axis
         * \param z rotation Gives the rotation degres around the z-axis
         */
        void SetRotation(float x, float y, float z);

        /** Set m_translation
         * \param x Gives the translation in unit of distance between the old
         * position, and the new position on the x-axis of this form
         * \param y Gives the translation in unit of distance between the old
         * position, and the new position on the y-axis of this form
         * \param z Gives the translation in unit of distance between the old
         * position, and the new position on the z-axis of this form
         */
        void SetTranslation(float x, float y, float z);

        //Getters
        /** Access m_rotation
         * \return The current value of m_rotation
         */
        Vector3 GetRotation() { return m_rotation; }

        /** Access m_translation
         * \return The current value of m_translation
         */
        Vector3 GetTranslation() { return m_translation; }

        /** Access m_texture
         * \return The current value of m_texture
         */
        sf::Texture GetTexture() { return m_texture; }

    protected:
        float m_height; //!< The height of the surface
        float m_width; //!< The width of the surface
        sf::Texture m_texture; //!< The texture applied on the surface
        Vector3 m_translation; //!< The translation vector of this form
        Vector3 m_rotation; //!< The rotation vector of this form
};

#endif // FORM2D_H
