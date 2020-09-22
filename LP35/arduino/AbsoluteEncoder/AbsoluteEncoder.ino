// https://forum.arduino.cc/index.php?topic=110250.0

const int PIN_CLK_NEG = 5;
const int PIN_CLK_POS = 6;
const int PIN_DATA    = 7;

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

static void clockPulse(void)
{
    clockLow();
    clockHigh();
}

void setup(void) 
{
    Serial.begin(115200);

    pinMode(PIN_CLK_NEG, OUTPUT);
    pinMode(PIN_CLK_POS, OUTPUT);
    pinMode(PIN_DATA, INPUT);

    clockHigh();
}


void loop(void) 
{
    uint16_t pos = 0;

    for (uint8_t i=0; i<10; i++) {

        clockPulse();

        uint8_t b = digitalRead(PIN_DATA) == HIGH ? 1 : 0;
        pos += b * pow(2, 10-(i+1));
    }

    for (uint8_t i=0; i<6; i++) {
        clockPulse();
    }

    clockPulse();

    Serial.println(pos);
}
