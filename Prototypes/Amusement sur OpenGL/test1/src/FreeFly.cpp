#include "FreeFly.h"

FreeFly::FreeFly(const Vector3 & position)
: m_position(position),
	m_phi(0),
	m_theta(0),
	m_speed(0.01),
	m_sensitivity(0.2),
	m_vMotionActive(false),
	m_hMotionActive(false)
{
	VectorsFromAngles();


}

void FreeFly::OnMouseMotion(const sf::Event::MouseMoveEvent &event)
{
}

void FreeFly::OnMouseBoutton(const sf::Event::MouseButtonEvent &event)
{
	//if((sf::Mouse::isButtonPressed()))
}

void FreeFly::OnKeyBoard(const sf::Event::KeyEvent &event){}

void FreeFly::Animate(int timestep){}

void FreeFly::SetSpeed(float speed){}

void FreeFly::SetSensitivity(float sensitivity){}

void FreeFly::SetPosition (const Vector3 &position){}

void FreeFly::look(){}

FreeFly::~FreeFly(){}

void FreeFly::VectorsFromAngles()
{
	static const Vector3 up(0.f, 0.f, 1.f);

	if(_phi > 89)
		_phi  = 89;
	else if (_phih <-89)
		_phi = -89;

	double r_temp = cos(_phi * M_PI / 180);
	m_forward.X = r_temp * cos(_theta * M_PI / 180);
	m_forward.Y = r_temp * sin(_theta * M_PI / 180);
	m_forward.Z = sin(_phi * M_PI / 180);

	m_left = up.crossProduct(m_forward);
	m_left.normalize();

	m_target = m_position + m_forward;
}
