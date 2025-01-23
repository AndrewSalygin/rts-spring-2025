int n = 5;
int delay_mcs[] = {10000, 1000, 500, 100, 50};
int previous_mcs[] = {0, 0, 0, 0, 0};
int output_pins[] = {3, 5, 6, 9, 10};
int led_states[] = {0, 0, 0, 0, 0};

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(output_pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    unsigned long currentMicros = micros();
    if (currentMicros - previous_mcs[i] >= delay_mcs[i]) {
      previous_mcs[i] = currentMicros;
      
      if (led_states[i] == 0) {
        led_states[i] = 127;
      } else {
        led_states[i] = 0;
      }
  
      analogWrite(output_pins[i], led_states[i]);
    } 
  }
}
