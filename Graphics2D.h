void Graphics2DInit(void);
void Render(void);
void DrawImage(uint16_t x, uint16_t y, const uint16_t * image, uint16_t w, uint16_t h);
void ClearBuffer(void);
void DrawImageScreen(uint16_t x, uint16_t y, const uint16_t * image, uint16_t w, uint16_t h, uint8_t rot);
void DrawWall(uint8_t rot, uint8_t door);
void DrawHearts(uint8_t life, uint8_t max);
void DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor);
void DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void DrawMap(void);
void DrawBorderRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1,uint16_t color2);
uint8_t AddSprite(const unsigned short * image, uint8_t width, uint8_t height, uint8_t initialx, uint8_t initialy);
void UpdateSprite(uint8_t unique, uint8_t screenx, uint8_t screeny);
uint8_t RemoveSprite(uint8_t unique);
void UpdateDoor(uint8_t d);
void UpdateHeart(uint8_t max, uint8_t current);
uint8_t GetNextUnique(void);

struct sprite {
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	uint8_t unique;
	const unsigned short * image;
};
typedef struct sprite Sprite;
