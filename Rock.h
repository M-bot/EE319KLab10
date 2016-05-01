#ifndef ROCK_H
#define ROCK_H
#include <stdint.h>
#include "Object.h"

void RockCreate(Object *this, uint8_t x, uint8_t y);
void RockLogic(Object *this, Object *player, uint64_t delta);
#endif
