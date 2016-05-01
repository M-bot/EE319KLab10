#define MAP_DATA_SIZE 7

void Map_Init(uint64_t seed);
uint8_t Get_Room_Data(uint8_t x, uint8_t y);
uint8_t Get_Map_Data(uint8_t x, uint8_t y);
void Set_Room(uint8_t x, uint8_t y, uint8_t discur);
