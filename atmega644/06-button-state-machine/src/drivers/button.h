#ifndef BUTTON_H_
#define BUTTON_H_

enum button_state
{
    RELEASED,
    PRE_PUSHED,
    PUSHED,
    PRE_RELEASED
};

enum button_state button_state_get(void);

#endif /* BUTTON_H_ */