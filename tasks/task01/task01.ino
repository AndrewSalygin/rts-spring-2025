const int N = 5;

struct PinConfig {
  volatile uint8_t* port;
  uint8_t mask;
};

const PinConfig pins[] = {
  { &PORTD, (1 << PD3) },
  { &PORTD, (1 << PD5) },
  { &PORTD, (1 << PD6) },
  { &PORTB, (1 << PB1) },
  { &PORTB, (1 << PB2) }
};

unsigned long delayMcs[] = {10000, 1000, 500, 100, 50};
unsigned long previousMcs[N] = {0};
bool ledStates[N] = {0};

void setup() {
  for (int i = 0; i < N; i++) {
    // Data Direction Register
    volatile uint8_t* ddr = (volatile uint8_t*)(pins[i].port - 1);
    *ddr |= pins[i].mask;
  }
}

void loop() {
  for (int i = 0; i < N; i++) {
    unsigned long currentMicros = micros();
    unsigned long halfPeriod = delayMcs[i] / 2;

    if (currentMicros - previousMcs[i] >= halfPeriod) {
      if (ledStates[i]) {
        *pins[i].port &= ~pins[i].mask;
      } else {
        *pins[i].port |= pins[i].mask;
      }

      ledStates[i] ^= 1;
      previousMcs[i] = currentMicros;
    } 
  }
}
