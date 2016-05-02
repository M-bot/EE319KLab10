#include <stdint.h>

struct Room {
	void(*create)(void);
	uint8_t * cleared;
};
typedef struct Room Room;

void RoomCreate(Room * room, uint8_t num);
