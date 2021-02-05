#include <stdio.h>
#include "rz_state_ctrl.h"


//done
static int is_jump_valid(struct rz_state *state, uint8_t des)
{
    printf("st = %s\n", state->name);
    if (state->jump_validList & (0x1 << des)) {
        return 1;   
    }
    
    return 0;    
}


//done
int state_ctrl_reg(struct rz_state_ctrl *ctrl, int size)
{
    
    ctrl->prevState = 0;
    ctrl->nowState = 0;
    ctrl->nextState = 0;
    ctrl->state_num = size/sizeof(struct rz_state); 
    
    return 0;
}


//done
int is_StageChanging(struct rz_state_ctrl* ctrl)
{
    if (ctrl->nowState != ctrl->nextState) {
        return 1;   
    }
    return 0;
}


//done
int set_next_state(struct rz_state_ctrl* ctrl, int nextIdx)
{
    uint8_t nowIdx;

    nowIdx = ctrl->nowState;

    /* check validation */
    if (is_jump_valid(ctrl->state + nowIdx, nextIdx) == 0) {
        return  1;
    }
       
    /* set nextState */
    ctrl->nextState = nextIdx;
    
    return 0;    
}

//done
void sw_state(struct rz_state_ctrl *ctrl)
{

    ctrl->prevState = ctrl->nowState;
    ctrl->nowState = ctrl->nextState;

    for (int m = 0; m < ctrl->state_num; m++) {
        ctrl->state[m].swFlag = 0;
    }
}

//done
int check_sw_flags(struct rz_state_ctrl *ctrl)
{

    for (int m = 0; m < ctrl->state_num; m++) {
        if (!ctrl->state[m].swFlag) {
            return -1;
        }
    }
    
    return 0;
}

//done
void print_state_info(struct rz_state_ctrl *ctrl)
{
    for (int m = 0; m < ctrl->state_num; m++) {
        printf("    Index %d: %s\n", m, ctrl->state[m].name);
    }
}

