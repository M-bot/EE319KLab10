#ifndef SPIKE_H
#define SPIKE_H
#include <stdint.h>
#include "Object.h"

void SpikeCreate(Object *this, uint8_t x, uint8_t y, uint8_t dmg);
void SpikeLogic(Object *this, Object *player, uint64_t delta);
#endif
