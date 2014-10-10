#ifndef _RADIO_CONTROL_H__
#define _RADIO_CONTROL_H__
#include <stdint.h>

#define RADIO_RX_SAFETY_MARGIN_US   4

typedef void (*radio_rx_cb)(uint8_t*);
typedef void (*radio_tx_cb)(void);

typedef enum
{
    RADIO_EVENT_TYPE_TX,
    RADIO_EVENT_TYPE_RX
} radio_event_type_t;


typedef struct
{
    radio_event_type_t event_type;  /* RX/TX */
    uint32_t start_time;            /* time to start the event. 0 indicates as soon as possible */
    uint8_t* packet_ptr;            /* packet pointer to use. TX ONLY */
    uint8_t access_address;         /* If TX: access address index to send on. If RX: AA enabled bitfield */
    uint8_t channel;                /* Channel to execute event on */
    union 
    {
        radio_rx_cb rx;
        radio_tx_cb tx;
    } callback;
} radio_event_t;

/**
* Starts the radio init procedure
* Must be called at the beginning of each timeslot
*/
void radio_init(void);


void radio_order(radio_event_t* radio_event);

#if 0

/**
* Send the given data packet via radio. Will abort any ongoing RX procedure, regardless of 
* how many packets have been received
*/
void radio_tx(uint8_t* data);

/**
* Set radio in RX mode. @param consectutive_receives indicates the number of packets to receive before the 
* radio goes back to disabled state
*/
void radio_rx(uint8_t consecutive_receives);

#endif

/**
* Disable the radio. Overrides any ongoing rx or tx procedures
*/
void radio_disable(void);


/**
* Radio event handler, checks any relevant events generated by the radio, and acts accordingly
*/
void radio_event_handler(void);



#endif /* _RADIO_CONTROL_H__*/
