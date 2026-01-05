#include <df/vector.h>

namespace df
{

Vector::Vector(float x, float y) : m_x{x}, m_y{y}
{
}

float Vector::getX() const noexcept
{
    return m_x;
}

float Vector::getY() const noexcept
{
    return m_y;
}

void Vector::setX(float x) noexcept
{
    m_x = x;
}

void Vector::setY(float y) noexcept
{
    m_y = y;
}

Vector Vector::operator+(const Vector& other) const noexcept
{
    return Vector{m_x + other.m_x, m_y + other.m_y};
}

Vector& Vector::operator+=(const Vector& other) noexcept
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

bool Vector::operator==(const Vector& other) const noexcept
{
    return m_x == other.m_x && m_y == other.m_y;
}

bool Vector::operator!=(const Vector& other) const noexcept
{
    return !(*this == other);
}

}  // namespace df
