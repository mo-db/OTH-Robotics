int main() {
    sensor_touch_clicked_t last_touch = SensorTouch_released;
    sensor_touch_clicked_t touch;
    bool touch_sensor_pressed = false;
    SensorConfig(Port_0, SensorTouch);
    while(1) {
       Touch_Clicked(Port_0, &touch);
       if (touch == SensorTouch_clicked)
          NNXT_LCD_DisplayStringAtLine(0, "Taster gedrueckt");
        else
          NNXT_LCD_DisplayStringAtLine(0, "Taster losgelassen");
        if (touch != last_touch) {
            touch_sensor_pressed = true;
        } else {
            touch_sensor_pressed = false;
        }
    }
}
