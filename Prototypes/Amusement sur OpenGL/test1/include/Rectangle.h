#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Form2D.h>
#include <Vector3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Rectangle: public Form2D
{
    public:

        /** Default constructor */
        Rectangle();
        /**
        * @param width : the width
        * @param height : the height
        * @param texture : the texture of that object
        * Construct an width * height rectangle with a texture applied
        */
        Rectangle(float width, float height);
        /** Default destructor */
        virtual ~Rectangle();

        //Framework methods
        virtual void Update(sf::Time& time);
        virtual void Draw(const sf::Time& time) const;

        //Getters
        /** Access m_width
         * \return The current value of m_width
         */
        float Getwidth() { return m_width; }

        /** Access m_height
         * \return The current value of m_height
         */
        float Getheight() { return m_height; }

    protected:
    private:
        float m_width; //!< The with of the rectangle"
        float m_height; //!< The height of this rectangle"
        float m_vertices[12];
};

#endif // RECTANGLE_H
