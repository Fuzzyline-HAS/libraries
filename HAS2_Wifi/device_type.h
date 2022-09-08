#include "Arduino.h"

struct iotglove
{
    String device_name;
    String role;
    int life_chip;
    int taken_chip;
    int max_life_chip;
    int battery_pack;
    int max_battery_pack;
    int exp;
    int max_exp;
    int lv;
    int shift_machine;
};

struct generator
{
    String device_name;
    int battery_pack;
    int max_battery_pack;
    int shift_machine;
};

struct itembox
{
    String device_name;
    int battery_pack;
    int expPack;
    int shift_machine;
};

struct lifemachine
{
    String device_name;
    int life_chip;
    int shift_machine;
};

struct temple
{
    String device_name;
    int taken_chip;
    int shift_machine;
};

struct tagmachine
{
    /* data */
};




