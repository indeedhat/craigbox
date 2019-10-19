#include <Keyboard.h>
#include <Arduino.h>

class Button
{
    public:
    const char key;
    const char pin;

    Button(uint8_t p, uint8_t k): pin(p), key(k)
    {}

    void update()
    {
        trigger(!digitalRead(pin));
    }

    private:
    bool lastState = false;

    void trigger(bool state)
    {
        if (state == lastState) {
            return;
        }

        !state
            ? Keyboard.press(key)
            : Keyboard.release(key);

        lastState = state;
    }
};

uint8_t keyCount = 7;
Button buttons[] = {
    {3, 0x65}, // e
    {4, KEY_RETURN},
    {5, 0x71}, // q
    {6, 0x78}, // x
    {7, KEY_TAB},
    {8, 0x70}, // p
    {9, KEY_ESC}
};

void setup() {
    for (uint8_t i = 0; i < keyCount; i++) {
        pinMode(buttons[i].pin, INPUT_PULLUP);
    }

    Keyboard.begin();
}


void loop() {
    for (uint8_t i = 0; i < keyCount; i++) {
        buttons[i].update();
    }

    delay(10);
}
