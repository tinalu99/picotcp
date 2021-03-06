#include "../../cs161-s19-psets-tinalu99/k-pico.hh"
#include "pico_dev_e1000.h"

extern int e1000_send_packet(void *buf, int len);
extern uint32_t e1000_packet_get(uint8_t** ptr);
extern uint8_t* e1000_mac_addr();
extern void print_buffer(uint8_t* buf, int len);

// pico device send function -- just calls the e1000 driver send function
static int pico_e1000_send(struct pico_device *dev, void *buf, int len)
{
    int retval = e1000_send_packet(buf, len);
    (void) dev;
    /* send function must return amount of bytes put on the network - no negative values! */
    if (retval < 0)
        return 0;
    return retval;
}

// pico device poll function - gets packets from the e1000 device 
// which are stored in buf, then calls pico_stack_recv to copy 
// the packet onto the stack
static int pico_e1000_poll(struct pico_device* dev, int loop_score) {
    uint8_t* buf = NULL;
    uint32_t len = 0;

    while (loop_score > 0) {
        len = e1000_packet_get(&buf);
        if (len == 0) {
            break;
        }
        pico_stack_recv(dev, buf, len); /* this will copy the frame into the stack */
        PICO_FREE(buf);
        loop_score--;
    }
    /* return (original_loop_score - amount_of_packets_received) */
    return loop_score;
}

struct pico_device* pico_e1000_create(const char *name, uint8_t* mac_addr)
{
    /* Create device struct */
    struct pico_device* e1000_dev = PICO_ZALLOC(sizeof(struct pico_device));
    if (!e1000_dev) {
        return NULL;
    }
    /* Attach function pointers */
    e1000_dev->send = pico_e1000_send;
    e1000_dev->poll = pico_e1000_poll;

    /* Register the device in picoTCP */
    if (0 != pico_device_init(e1000_dev, name, mac_addr)) {
        dbg("Device init failed.\n");
        PICO_FREE(e1000_dev);
        return NULL;
    }
    /* Return a pointer to the device struct */ 
    return e1000_dev;
}


