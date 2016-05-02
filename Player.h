#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include "Object.h"

#define PLAYER_WIDTH 11
#define PLAYER_HEIGHT 14

void PlayerCreate(Object *this);
void PlayerLogic(Object *this, Object *player, uint64_t delta);
#endif
