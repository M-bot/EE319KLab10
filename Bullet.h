#ifndef BULLET_H
#define BULLET_H
#include <stdint.h>
#include "Object.h"

void BulletCreate(Object *this, uint16_t x, uint16_t y, int16_t vx, int16_t vy, uint16_t rng, uint16_t dmg, uint8_t fp);
void BulletLogic(Object *this, Object *player, uint64_t delta);
#endif
