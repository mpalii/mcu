#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum
{
    PRE_READY,
    READY,
    PRE_WAIT,
    WAIT,
    PRE_MEASURING,
    MEASURING,
    RESULT,
    FALSE_START,
    TIMEOUT
} e_state;

void handle_device_state(void);

#endif /* STATE_MACHINE_H_ */