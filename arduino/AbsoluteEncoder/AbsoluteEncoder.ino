// For Teensy 3.2
static const uint8_t PIN_CLK = 23;
static const uint8_t PIN_DAT = 22;
static const uint8_t PIN_CS  = 21;

static void clockup(void)
{
    digitalWrite(PIN_CLK, HIGH);
}
static void clockdown(void)
{
    digitalWrite(PIN_CLK, LOW);
}

static void MSB(void)
{
    // Most Significant Bit
    clockdown();
}

static uint16_t readpos(void)
{
    return millis();

    digitalWrite(PIN_CS, LOW);
    delayMicroseconds(1);
    MSB();

    uint16_t data = 0;

    for (uint i=0; i<16; ++i) {
        if (i<10) {
            clockup();
            data <<= 1;
            data |= digitalRead(PIN_DAT);
            clockdown();
        }
        else {
            for (uint8_t k=0; k<6; ++k) { 
                clockup();
                clockdown();
            }
        }
    }

    digitalWrite(PIN_CS, HIGH);

    return data;
}

void setup(void)
{
    Serial.begin(115200);

    //pinMode(PIN_CLK, OUTPUT);
    //pinMode(PIN_DAT, INPUT);
    //pinMode(PIN_CS,  OUTPUT);

    delay(500);
}

void loop(void)
{
    //Serial.println(readpos());
    //delay(1);

    Serial.println(millis());
}
