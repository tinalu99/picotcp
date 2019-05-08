// #include "/home/tinalu/Desktop/cs161-s19-psets-tinalu99/k-pico.hh"
#include "../../../cs161-s19-psets-tinalu99/k-pico.hh"

extern void* chk_alloc(size_t sz);
extern void chk_free(void* ptr);
extern unsigned long ticks_time(void);
extern unsigned long ticks_time_ms(void);
extern void ticks_idle(void);

#define pico_zalloc(x) chk_alloc(x) 
#define pico_free(x) chk_free(x)
#define dbg chk_print


static inline unsigned long PICO_TIME(void)
{
    return ticks_time();
}

static inline unsigned long PICO_TIME_MS(void)
{
    return ticks_time_ms();
}

static inline void PICO_IDLE(void)
{
    ticks_idle();
}

