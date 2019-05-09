/*
 * pico_osal.h
 * OS Abstraction Layer between PicoTCP and Chckadee Operating System
 *
 */

/* PicoTCP includes */
#include "pico_defines.h"
#include "pico_config.h"
#include "pico_stack.h"
#include "pico_osal.h"

#define osal_dbg(...)
//#define osal_dbg(...) printf(__VA_ARGS__)

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* ============= */
/* == MUTEXES == */
/* ============= */

extern void* chk_mutex_init(void);
extern void chk_mutex_deinit(void* mut);
extern void chk_mutex_lock(void* mut);
extern int chk_mutex_lock_timeout(void* mut, int timeout); 
extern void chk_mutex_unlock(void* mutex);

void* pico_mutex_init(void)
{
    return chk_mutex_init();
}

void pico_mutex_deinit(void * mutex)
{
    if (mutex != NULL) {
        chk_mutex_deinit(mutex);
    }
}

int pico_mutex_lock_timeout(void * mutex, int timeout)
{
    if (mutex != NULL) {
        return chk_mutex_lock_timeout(mutex, timeout);
    }
    return 0;
}

void pico_mutex_lock(void * mutex)
{
    if (mutex != NULL) {
        chk_mutex_lock(mutex);
    }
}

void pico_mutex_unlock(void * mutex)
{
	if (mutex != NULL) {
        chk_mutex_unlock(mutex);
    }
}

void pico_mutex_unlock_ISR(void * mutex)
{
    if (mutex != NULL) {
        chk_mutex_unlock(mutex);
    }
}

/* ============= */
/* == SIGNALS == */
/* ============= */

void * pico_signal_init(void)
{
    void * signal = pico_mutex_init();
    pico_mutex_lock(signal);
    return signal;
}

void pico_signal_deinit(void * signal)
{
    pico_mutex_deinit(signal);
}

void pico_signal_wait(void * signal)
{
    pico_signal_wait_timeout(signal, -1);
}

int pico_signal_wait_timeout(void * signal, int timeout)
{
    return pico_mutex_lock_timeout(signal, timeout);
}

void pico_signal_send(void * signal)
{
    pico_mutex_unlock(signal);
}

void pico_signal_send_ISR(void * signal)
{
    pico_mutex_unlock_ISR(signal);
}


/* ============= */
/* == THREADS == */
/* ============= */

pico_thread_t pico_thread_create(pico_thread_fn thread, void *arg, int stack_size, int prio)
{
    (void)thread;
    (void)arg;
    (void)stack_size;
    (void)prio;
    return NULL;
}

void pico_thread_destroy(pico_thread_t t)
{
    return;
}

void pico_msleep(int ms)
{
    pico_time now = PICO_TIME_MS();
    while ((pico_time)(now + ms) < PICO_TIME_MS());
}
