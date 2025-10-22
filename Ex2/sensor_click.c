uint8_t move_button_pressed = 0;
uint8_t turn_button_pressed = 0;

//uint8_t check_pressed(sensor_ports_e port) {
//}

void move_button() {
    sensor_touch_clicked_t last_button_state = SensorTouch_released;
    sensor_touch_clicked_t button_state = SensorTouch_released;

    while(1) {
        Delay(100);
        last_button_state = button_state;
        Touch_Clicked(Port_0, &button_state);
        if (last_button_state == SensorTouch_released && button_state == SensorTouch_clicked) {
            move_button_pressed = 1;
        } else {
            move_button_pressed = 0;
        }
    }
}

void turn_button() {
    sensor_touch_clicked_t last_button_state = SensorTouch_released;
    sensor_touch_clicked_t button_state = SensorTouch_released;

    while(1) {
        Delay(100);
        last_button_state = button_state;
        Touch_Clicked(Port_3, &button_state);
        if (last_button_state == SensorTouch_released && button_state == SensorTouch_clicked) {
            turn_button_pressed = 1;
        } else {
            turn_button_pressed = 0;
        }
    }

}

void do_action() {
    MotorPortInit(Port_A);
    MotorPortInit(Port_B);
    motor_dir_t motorDir = Motor_dir_forward;


    while(1) {
        if (move_button_pressed) {

        } else if (turn_button_pressed) {
            if (motorDir == Motor_dir_backward) {
                motorDir = Motor_dir_forward;
            } else {
                motorDir = Motor_dir_backward;
            }

        }
    }
}


int main() {
    SensorConfig(Port_0, SensorTouch);
    SensorConfig(Port_3, SensorTouch);

    CreateAndStartTask(move_button);
    CreateAndStartTask(turn_button);

    StartScheduler();

    return 0;
}
