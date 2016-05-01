#ifndef HORF_H
#define HORF_H
#include <stdint.h>
#include "Object.h"

void HorfCreate(Object *this, uint8_t x, uint8_t y);
void HorfLogic(Object *this, Object *player, uint64_t delta);
#endif
