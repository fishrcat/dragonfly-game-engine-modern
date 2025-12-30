//Engine
#include "EventOut.h"
#include "WorldManager.h"
// Project
#include "bullet.h"

#include "EventMouse.h"


Bullet::Bullet(const df::Vector hero_pos, const float hero_width) {

    //Set up
    Object::setSprite("bullet");
    Object::setType("Bullet");

    // Set starting position in world relative to ship
    df::Vector p(hero_pos.getX() + hero_width / 2, hero_pos.getY());
    Object::setPosition(p);

    // Init motion controller
    setSpeed(1);

    // Allow to pass through ship to avoid friendly fire
    Object::setSolidness(df::SOFT);
};

auto Bullet::eventHandler(const df::Event *p_e) -> int{

    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }

    if (p_e->getType() == df::COLLISION_EVENT) {
        const auto *p_collision_event =
            dynamic_cast<const df::EventCollision *> (p_e);
        hit(p_collision_event);
        return 1;
    }

    return 0;
}

void Bullet::out() {

    WM.markForDelete(this);
}

void Bullet::hit(const df::EventCollision *p_collision_event) {

    // Object whose move initiated the collision is Object1
    if ((p_collision_event -> getObject1() -> getType() == "Saucer") ||
        (p_collision_event -> getObject2() -> getType() == "Saucer")) {
        WM.markForDelete(p_collision_event->getObject1());
        WM.markForDelete(p_collision_event->getObject2());
    }
}
