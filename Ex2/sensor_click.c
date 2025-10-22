uint32_t get_time_passed_ms(uint32_t button_press_start_ms) {
    // return get_time() - start time
}

int main() {
    sensor_touch_clicked_t last_touch_state = SensorTouch_released;
    sensor_touch_clicked_t touch_state;
    bool touch_state_change = false;

    uint16_t button_press_counter = 0;
    uint32_t button_press_start_ms = 0;
    
    SensorConfig(Port_0, SensorTouch);
    while(1) {
       Touch_Clicked(Port_0, &touch_state);
       if (touch_state == SensorTouch_clicked)
          NNXT_LCD_DisplayStringAtLine(0, "Button Down");
        else
          NNXT_LCD_DisplayStringAtLine(0, "Button Up");
        if (touch != last_touch) {
            // start mesuring
            // if time_passed > x seconds, print to screen
            // stop mesuring or restart
            button_press_counter++;
            touch_sensor_pressed = true;
        } else {
            touch_sensor_pressed = false;
        }
    }
}
