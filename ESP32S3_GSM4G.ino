#define MODEM_RX 18
#define MODEM_TX 17

void setup()
{
    Serial.begin(115200);

    Serial2.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);

    Serial.println("ESP32 UART started");
}

void loop()
{
    // PC -> A7672S
    while (Serial.available())
    {
        Serial2.write(Serial.read());
    }

    // A7672S -> PC
    while (Serial2.available())
    {
        Serial.write(Serial2.read());
    }
}