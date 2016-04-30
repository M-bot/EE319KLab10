// Sound.h
struct Sound { 
	uint32_t p;
	const uint8_t *sound;
	uint32_t size;
	uint32_t off;
	uint8_t len;
	uint8_t cnt;
	uint8_t *values;
	int32_t vi;
	uint8_t loop;
};
typedef struct Sound Sound;
void Sound_Init(void);
void Sound_Play(const uint8_t *pt, uint32_t count, uint8_t lp);
void Sound_BGM_Play(const uint8_t *pt, uint32_t count);
uint8_t Sound_Ready(void);
uint8_t Decode(Sound *cc);
