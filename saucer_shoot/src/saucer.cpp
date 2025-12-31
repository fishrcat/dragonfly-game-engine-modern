// Engine
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "WorldManager.h"
// Project
#include "explosion.h"
#include "nuke.h"
#include "points.h"
#include "saucer.h"

#include <random>

Saucer::Saucer() {

  // Set up
  Object::setSprite("saucer");
  Object::setType("Saucer");
  // TODO: Move to game config

  // Input hooks
  registerInterest(NUKE_EVENT);

  // Initialize motion
  constexpr float left_vel = -0.25;
  Object::setVelocity(df::Vector(left_vel, 0));

  // Set starting position in world
  moveToStart();
}

Saucer::~Saucer() {

  // Send event with points to view objects
  df::EventView event_view(POINTS_STRING, saucer_points, true);
  WM.onEvent(&event_view);
}

auto Saucer::eventHandler(const df::Event *p_e) -> int {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const auto *p_collision_event =
        dynamic_cast<const df::EventCollision *>(p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == NUKE_EVENT) {
    destroy();
    return 1;
  }

  return 0;
}

void Saucer::out() {

  if (getPosition().getX() >= 0) {
    return;
  }

  moveToStart();
  new Saucer;
}

void Saucer::moveToStart() {

  df::Vector temp_pos;

  const float world_horiz = WM.getBoundary().getHorizontal();
  const float world_vert = WM.getBoundary().getVertical();

  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(0, RAND_MAX);

  const auto rand_offset =
      static_cast<float>(dist(rng) % static_cast<int>(world_horiz));
  const auto saucer_width = getBox().getHorizontal() / 2;
  const auto rand_x = world_horiz + rand_offset + saucer_width;
  temp_pos.setX(rand_x);
  const auto rand_offset_y =
      static_cast<float>(dist(rng) % (static_cast<int>(world_vert) - 1));
  const auto rand_y = rand_offset_y - (getBox().getVertical());
  temp_pos.setY(rand_y);

  // Move right if necessary to avoid init collision
  df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
  while (collision_list.getCount() != 0) {
    temp_pos.setX(temp_pos.getX() + 1);
    collision_list = WM.getCollisions(this, temp_pos);
  }

  WM.moveObject(this, temp_pos);
}

void Saucer::hit(const df::EventCollision *p_c) const {

  // If bullet hits saucer - explode and respawn
  if ((p_c->getObject1()->getType() == "Bullet") ||
      (p_c->getObject2()->getType() == "Bullet")) {

    auto *p_explosion = new Explosion;
    p_explosion->setPosition(this->getPosition());

    new Saucer;
  }

  // If saucer hits hero, end the game
  if (((p_c->getObject1()->getType()) == "Hero") ||
      ((p_c->getObject2()->getType()) == "Hero")) {
    WM.markForDelete(p_c->getObject1());
    WM.markForDelete(p_c->getObject2());
  }
}

void Saucer::destroy() {
  // Create explosion.
  auto *p_explosion = new Explosion;
  p_explosion->setPosition(this->getPosition());

  // Delete self.
  WM.markForDelete(this);

  // Saucers appear stay around perpetually
  new Saucer;
}
