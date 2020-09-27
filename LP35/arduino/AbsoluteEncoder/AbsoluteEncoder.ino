// https://forum.arduino.cc/index.php?topic=110250.0

static const uint8_t PIN_CLK_NEG = 5;
static const uint8_t PIN_CLK_POS = 6;
static const uint8_t PIN_DATA    = 7;

static const uint8_t BIT_RESOLUTION  = 10;

static void clockHigh(void)
{
    digitalWrite(PIN_CLK_NEG, LOW);
    digitalWrite(PIN_CLK_POS, HIGH);
}

static void clockLow(void)
{
    digitalWrite(PIN_CLK_NEG, HIGH);
    digitalWrite(PIN_CLK_POS, LOW);
}

void setup(void) 
{
    Serial.begin(115200);

    pinMode(PIN_CLK_NEG, OUTPUT);
    pinMode(PIN_CLK_POS, OUTPUT);
    pinMode(PIN_DATA, INPUT);

    clockLow();
}

void loop(void) 
{
    uint16_t pos = 0;

    for (uint8_t i=0; i<BIT_RESOLUTION; i++) {

        // Rising edge triggers transmission of next bit from encoder
        clockHigh();

        // Read next bit
        uint16_t b = digitalRead(PIN_DATA) == HIGH ? 1 : 0;

        // We start with MSB, so shift left
        pos |= b<<(BIT_RESOLUTION-(i+1));

        // Send falling edge
        clockLow();

        // We need to wait between 2 and 10 usec between sending falling edges
        delayMicroseconds(4);
    }

    // We need to wait between 10 and 30 usec for next value
    delayMicroseconds(20);

    Serial.println(pos);
}
