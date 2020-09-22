// https://forum.arduino.cc/index.php?topic=110250.0

const int PIN_CS    = 5;
const int PIN_CLOCK = 6;
const int PIN_DATA  = 7;

static void pulseClock(void)
{
    digitalWrite(PIN_CLOCK, LOW);
    digitalWrite(PIN_CLOCK, HIGH);
}   

void setup(void) 
{
    Serial.begin(115200);

    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_CLOCK, OUTPUT);
    pinMode(PIN_DATA, INPUT);

    digitalWrite(PIN_CLOCK, HIGH);
    digitalWrite(PIN_CS, LOW);
}


void loop(void) 
{
    digitalWrite(PIN_CS, HIGH);
    digitalWrite(PIN_CS, LOW);

    uint16_t pos = 0;

    for (uint8_t i=0; i<10; i++) {

        pulseClock();

        byte b = digitalRead(PIN_DATA) == HIGH ? 1 : 0;
        pos += b * pow(2, 10-(i+1));
    }

    for (uint8_t i=0; i<6; i++) {

        pulseClock();
    }

    pulseClock();

    Serial.println(pos);
}
