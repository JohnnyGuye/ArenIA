#include "Form2D.h"

#include <iostream>
void Form2D::Transformation(float tfact, float rfact) const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(m_translation.X * tfact, m_translation.Y * tfact, m_translation.Z * tfact);
    glRotatef(m_rotation.X * rfact, 1.f, 0.f, 0.f);
    glRotatef(m_rotation.Y * rfact, 0.f, 1.f, 0.f);
    glRotatef(m_rotation.Z * rfact, 0.f, 0.f, 1.f);
}

void Form2D::SetTranslation(Vector3 translation)
{
    m_translation = translation;
}

void Form2D::SetRotation(Vector3 rotation)
{
    m_rotation = rotation;
}

void Form2D::SetTranslation(float x, float y, float z)
{
    m_translation.X = x;
    m_translation.Y = y;
    m_translation.Z = z;
}

void Form2D::SetRotation(float x, float y, float z)
{
    m_rotation.X = x;
    m_rotation.Y = y;
    m_rotation.Z = z;
}

Form2D::Form2D()
{
    m_translation = Vector3(0.f, 0.f, 0.f);
    m_rotation = Vector3(0.f, 0.f, 0.f);
}

Form2D::~Form2D()
{
    //dtor
}
