#include <random>
//Engine
#include "EventOut.h"
#include "WorldManager.h"
// Project
#include "saucer.h"


Saucer::Saucer() {

    // Set up
    Object::setSprite("saucer");
    Object::setType("Saucer");

    // Initialize motion
    constexpr float left_vel = -0.25;
    Object::setVelocity(df::Vector(left_vel, 0));

    // Set starting position in world
    moveToStart();
}

auto Saucer::eventHandler(const df::Event *p_e) -> int{

    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }

    return 0;
}

void Saucer::out() {

    if (getPosition().getX() >= 0) {
        return;
    }

    moveToStart();
}

void Saucer::moveToStart() {

    df::Vector temp_pos;

    const float world_horiz = WM.getBoundary().getHorizontal();
    const float world_vert = WM.getBoundary().getVertical();

    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, RAND_MAX);

    const auto rand_offset = static_cast<float>(dist(rng) % static_cast<int>(world_horiz));
    const auto saucer_width = getBox().getHorizontal() / 2;
    const auto rand_x = world_horiz + rand_offset + saucer_width;
    temp_pos.setX(rand_x);
    const auto rand_offset_y = static_cast<float>(dist(rng) % (static_cast<int>(world_vert) - 1));
    const auto rand_y = rand_offset_y - (getBox().getVertical());
    temp_pos.setY(rand_y);

    WM.moveObject(this, temp_pos);
}
