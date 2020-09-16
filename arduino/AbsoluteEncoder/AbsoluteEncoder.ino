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
    digitalWrite(PIN_CS, LOW);
    delayMicroseconds(1);
    MSB();
    uint16_t data = 0;
    /* 
    for i in range(0,bitcount):
        if i<10:
            #print(i)
            clockup()
            for j in range(0,ns):
                data[j]<<=1  
                data[j]|=GPIO.input(PIN_DAT[j])
            clockdown()
        else:
            for k in range(0,6):
                clockup()
                clockdown()
    GPIO.output(PIN_CS,1)
    */
    return data;
}

void setup(void)
{
    Serial.begin(115200);

    pinMode(PIN_CLK, OUTPUT);
    pinMode(PIN_DAT, INPUT);
    pinMode(PIN_CS,  OUTPUT);

    delay(500);
}

void loop(void)
{
    Serial.println(millis());
}
