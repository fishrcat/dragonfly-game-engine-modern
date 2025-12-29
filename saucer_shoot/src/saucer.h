#pragma once
#include "Object.h"


class Saucer : public df::Object {

    private:
        void moveToStart();
        void out();

    public:
        Saucer();
        auto eventHandler(const df::Event *p_e) -> int override;
};
