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

uint8_t keyCount = 4;
Button buttons[] = {
    {15, KEY_UP_ARROW},
    {14, KEY_RIGHT_ARROW},
    {16, KEY_DOWN_ARROW},
    {10, KEY_LEFT_ARROW}
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
