#include <stdio.h>
#include "rz_state_ctrl.h"

enum 
{ 
    STATE_IDLE = 0,
    STATE_1,
    STATE_2,
    STATE_3,
};



struct rz_state g_states[] =
{

    __ADD_RZ_STATE(STATE_IDLE, "IDLE", 0xFFFFFFFF),
    __ADD_RZ_STATE(STATE_1, "state 1 la", 0xFFFFFFFF),
    __ADD_RZ_STATE(STATE_2, "state 2 here", 0x3),
    __ADD_RZ_STATE(STATE_3, "i am state 3", 0x3),
};

struct rz_state_ctrl g_st_ctrl;


int main(void)
{
    int rc;
    g_st_ctrl.state = g_states;

    state_ctrl_reg(&g_st_ctrl, sizeof(g_states));

    print_state_info(&g_st_ctrl);

    printf("set index 2\n");
    rc =set_next_state(&g_st_ctrl, 2);
    printf("rc = %d\n", rc);

    rc = check_sw_flags(&g_st_ctrl);
    printf("check flag rc = %d\n", rc);

    rc = is_StageChanging(&g_st_ctrl);
    printf("is switching = %d\n", rc);

    g_states[0].swFlag = 1;
    g_states[1].swFlag = 1;
    g_states[2].swFlag = 1;
    g_states[3].swFlag = 1;

    rc = check_sw_flags(&g_st_ctrl);
    printf("check flag again rc = %d\n", rc);

    printf("do switch to 2\n");
    sw_state(&g_st_ctrl);

    printf("set index 3\n");
    rc =set_next_state(&g_st_ctrl, 2);
    printf("rc = %d\n", rc);



    return 0; 
}






