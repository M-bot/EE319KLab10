#define WIDTH 160
#define HEIGHT 128
#define ROOM_WIDTH 140
#define ROOM_HEIGHT 80 
#define HUD_HEIGHT (HEIGHT-ROOM_HEIGHT-WALL*2)
#define HEART_X (WIDTH-54)
#define HEART_Y (HUD_HEIGHT)/2-8
#define WALL 10
#define ITEM_SIZE (HUD_HEIGHT*5/8)
#define ITEM_Y (HUD_HEIGHT*3/16)
#define ITEM_X (HEART_X-ITEM_SIZE-5)
#define ARROW_X (ITEM_X-ITEM_SIZE-5)
#define MAP_SIZE ((HUD_HEIGHT-8)/5)
#define MAP_CENTER_X (ARROW_X/2)
#define MAP_CENTER_Y (HUD_HEIGHT/2)

#define BLACK 0x0000
#define DARK_GRAY 0x18C3
#define GRAY 0x39C7
#define LIGHT_GRAY 0x738E
#define WHITE 0xFFFF

#define MAX_SPRITES 100

#define UPDATE_DOOR 0x1
#define UPDATE_HEART 0x2

#define DIMMER_PIN 0x20

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
void DrawBuffer(void);
void CheckUpdates(void);

struct sprite {
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	uint8_t unique;
	const unsigned short * image;
};
typedef struct sprite Sprite;
