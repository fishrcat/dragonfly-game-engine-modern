#pragma once

namespace df {

class Vector {
public:
  Vector() = default;
  Vector(float x, float y);

  float getX() const noexcept;
  float getY() const noexcept;

  void setX(float x) noexcept;
  void setY(float y) noexcept;

  Vector operator+(const Vector& other) const noexcept;
  Vector& operator+=(const Vector& other) noexcept;

  bool operator==(const Vector& other) const noexcept;
  bool operator!=(const Vector& other) const noexcept;

private:
  float m_x{0.0f};
  float m_y{0.0f};
};

}  // namespace df
