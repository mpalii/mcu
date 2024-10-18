#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum
{
    READY, 
    MEASURING, 
    RESULT,
    FALSE_START,
    TIMEOUT
} e_state;

// void init_state_machine(void);
void handle_device_state(void);

#endif /* STATE_MACHINE_H_ */