#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include "Object.h"

void PlayerCreate(Object *this);
void PlayerLogic(Object *this, Object *player, uint64_t delta);
#endif
