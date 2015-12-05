#include "Cone.h"

Cone::Cone(float height, float baseRadius)
:   m_height(height),
    m_baseRadius(baseRadius),
    m_rotation(0.f,0.f,0.f),
    m_translation(0.f,0.f,0.f)
{
    //ctor
}

void Cone::Update(sf::Time& time)
{

}

//TODO add Setters(Vector3)

void Cone::SetTranslation(float x, float y, float z)
{
    m_translation.X = x;
    m_translation.Y = y;
    m_translation.Z = z;
}

void Cone::SetRotation(float x, float y, float z)
{
    m_rotation.X = x;
    m_rotation.Y = y;
    m_rotation.Z = z;
}

void Cone::Draw(sf::Time& time)
{
    glLoadIdentity();
    glTranslatef(m_translation.X, m_translation.Y, m_translation.Z);
    glRotatef(m_rotation.X, 1.f, 0.f, 0.f);
    glRotatef(m_rotation.Y, 0.f, 1.f, 0.f);
    glRotatef(m_rotation.Z, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
        //for(int i = 0; i < 30; i++)
        //{
            glVertex3f(0.f, 0.f, m_height);
            glVertex3f(m_baseRadius, 0.f, 0.f);
            glVertex3f(0.f, m_baseRadius, 0.f);

            glVertex3f(0.f, 0.f, m_height);
            glVertex3f(0.f, m_baseRadius, 0.f);
            glVertex3f(-m_baseRadius, 0.f, 0.f);

            glVertex3f(0.f, 0.f, m_height);
            glVertex3f(-m_baseRadius, 0.f, 0.f);
            glVertex3f(0.f, -m_baseRadius, 0.f);

            glVertex3f(0.f, 0.f, m_height);
            glVertex3f(0.f, -m_baseRadius, 0.f);
            glVertex3f(m_baseRadius, 0.f, 0.f);
        //}
    glEnd();
}

Cone::~Cone()
{
    //dtor
}
