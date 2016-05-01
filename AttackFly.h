#ifndef ATTACKFLY_H
#define ATTACKFLY_H
#include <stdint.h>
#include "Object.h"

void AttackFlyCreate(Object *this, uint8_t x, uint8_t y);
void AttackFlyLogic(Object *this, Object *player, uint64_t delta);
#endif
