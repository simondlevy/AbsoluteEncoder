// https://forum.arduino.cc/index.php?topic=110250.0

static const uint8_t PIN_CS    = 5;
static const uint8_t PIN_CLOCK = 6;
static const uint8_t PIN_DATA  = 7;

void setup(void) 
{
    Serial.begin(115200);

    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_CLOCK, OUTPUT);
    pinMode(PIN_DATA, INPUT);

    digitalWrite(PIN_CLOCK, HIGH);
    digitalWrite(PIN_CS, LOW);
}

static void pulseClock(void)
{
    digitalWrite(PIN_CLOCK, LOW);
    digitalWrite(PIN_CLOCK, HIGH);
}

void loop(void) 
{
    digitalWrite(PIN_CS, HIGH);
    digitalWrite(PIN_CS, LOW);

    uint16_t pos = 0;

    // Read 10 data bits
    for (uint8_t i=0; i<10; i++) {

        pulseClock();

        uint8_t b = digitalRead(PIN_DATA) == HIGH ? 1 : 0;

        pos |= b<<(10-(i+1));
    }

    // Read and ignore 6 status bits
    for (int i=0; i<6; i++) {
        pulseClock();
    }

    Serial.println(pos);
}
