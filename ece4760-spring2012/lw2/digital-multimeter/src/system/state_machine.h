#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum
{
    VCC_MEASURING,
    RES_MEASURING_1K,
    RES_MEASURING_10K,
    RES_MEASURING_100K
} e_state;

void handle_device_state(void);
e_state get_device_state(void);

#endif /* STATE_MACHINE_H_ */