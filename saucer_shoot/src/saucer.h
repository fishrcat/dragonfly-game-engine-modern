#pragma once
#include "EventCollision.h"
#include "Object.h"


class Saucer : public df::Object {

    public:
        Saucer();
        auto eventHandler(const df::Event *p_e) -> int override;

    private:
        void moveToStart();
        void out();
        void hit(const df::EventCollision *p_c) const;
        void destroy();
};
