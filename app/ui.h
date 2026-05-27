#ifndef UI_H_
#define UI_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    bool center;
    bool up;
    bool down;
    bool left;
    bool right;
} UI_Input_t;

void UI_Init(void);
void UI_Process(UI_Input_t input);

#endif /* UI_H_ */
