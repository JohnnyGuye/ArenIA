#ifndef CONE_H
#define CONE_H

#include <Vector3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

class Cone
{
    public:
        /** Default constructor */
        Cone(float height = 1.f, float baseRadius = 1.f);
        /** Default destructor */
        virtual ~Cone();

        //Framework methods
        virtual void Update(sf::Time& time);
        virtual void Draw(sf::Time& time);

        //Setters
        void SetTranslation(Vector3 translation);
        void SetRotation(Vector3 rotation);

        virtual void SetTranslation(float x,float y, float z);
        virtual void SetRotation(float x, float y, float z);

        /** Access m_height
         * \return The current value of m_height
         */
        float Getheight() { return m_height; }
        /** Set m_height
         * \param val New value to set
         */
        void Setheight(float val) { m_height = val; }
        /** Access m_baseRadius
         * \return The current value of m_baseRadius
         */
        float GetbaseRadius() { return m_baseRadius; }
        /** Set m_baseRadius
         * \param val New value to set
         */
        void SetbaseRadius(float val) { m_baseRadius = val; }
    protected:
        float m_height; //!< Member variable "m_height"
        float m_baseRadius; //!< Member variable "m_baseRadius"
        Vector3 m_rotation;
        Vector3 m_translation;
};

#endif // CONE_H
