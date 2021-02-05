#ifndef RZ_STATE_CTRL
#define RZ_STATE_CTRL

#include <stdint.h>

struct rz_state
{
    uint8_t index;
    int8_t *name;
    uint8_t swFlag;
    uint32_t jump_validList;
};

struct rz_state_ctrl
{
    uint8_t prevState;
    uint8_t nowState;
    uint8_t nextState;

    uint8_t state_num;
    struct rz_state *state;
    
};

#define __ADD_RZ_STATE(i, n, v) \
    { \
        .index = i, \
        .name = n, \
        .jump_validList = v, \
    }

int state_ctrl_reg(struct rz_state_ctrl *ctrl, int size);
int is_StageChanging(struct rz_state_ctrl* ctrl);
int set_next_state(struct rz_state_ctrl* ctrl, int nextIdx);
void sw_state(struct rz_state_ctrl *ctrl);
int check_sw_flags(struct rz_state_ctrl *ctrl);
void print_state_info(struct rz_state_ctrl *ctrl);

#endif  /* RZ_STATE_CTRL */
