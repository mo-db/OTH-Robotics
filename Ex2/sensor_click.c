#include "nnxt.h"
#include <stdio.h>

// TODO: button presses not recognized allways

// volatile disables compiler optimization
volatile uint8_t button_one_pressed = 0;
volatile uint8_t button_two_pressed = 0;


void check_button_one() {
    sensor_touch_clicked_t button_state = SensorTouch_released;
    sensor_touch_clicked_t last_button_state = SensorTouch_released;

    while(1) {
        last_button_state = button_state;
        Touch_Clicked(Port_0, &button_state);
        if (last_button_state == SensorTouch_released && button_state == SensorTouch_clicked) {
            button_one_pressed = 1;
        }
        Delay(100);
    }
}


void check_button_two() {
    sensor_touch_clicked_t button_state = SensorTouch_released;
    sensor_touch_clicked_t last_button_state = SensorTouch_released;

    while(1) {
        last_button_state = button_state;
        Touch_Clicked(Port_1, &button_state);
        if (last_button_state == SensorTouch_released && button_state == SensorTouch_clicked) {
            button_two_pressed = 1;
        }
        Delay(100);
    }
}


void do_action() {
    MotorPortInit(Port_A);
    MotorPortInit(Port_B);
    motor_dir_t motorDir = Motor_dir_forward;

    while(1) {
        if (button_one_pressed) {
            button_one_pressed = 0;
            Motor_Drive(Port_A, motorDir, 35);
            Motor_Drive(Port_B, motorDir, 35);
            Delay(1000);
            Motor_Stop(Port_A, Motor_stop_float);
            Motor_Stop(Port_B, Motor_stop_float);

        }
        else if (button_two_pressed) {
            button_two_pressed = 0;
            motorDir = (motorDir == Motor_dir_forward) ?
                Motor_dir_backward : Motor_dir_forward;
        }
    }
}


int main() {
    SensorConfig(Port_0, SensorTouch);
    SensorConfig(Port_1, SensorTouch);

    CreateAndStartTask(check_button_one);
    CreateAndStartTask(check_button_two);
    CreateAndStartTask(do_action);

    printf("Tasks were started\n");

    StartScheduler();

    return 0;
}
