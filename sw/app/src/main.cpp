#include <libdrivers/gpio.hpp>
#include <libdrivers/uart.hpp>
#include <libmisc/delay.hpp>
#include <cctype>

void send_dot(uint8_t pin) {
    gpio.set_pin(pin, true);
    udelay(1000);                  // dot = 1s
    gpio.set_pin(pin, false);
    udelay(1000);                  // space = 1s
}

void send_dash(uint8_t pin) {
    gpio.set_pin(pin, true);
    udelay(3000);                  // dash = 3s
    gpio.set_pin(pin, false);
    udelay(1000);                  // space = 1s
}

void send_char_space() {
    udelay(2000); // 1s after signal +2s for 3s char space
}

void send_morse(const char* text, uint8_t pin) {
    for (const char* p = text; *p; ++p) {
        char c = toupper(*p);
        uart.write(c);
        uart.write("\n");
        switch (c) {
            case 'A': send_dot(pin); send_dash(pin);                                 break;
            case 'B': send_dash(pin); send_dot(pin); send_dot(pin); send_dot(pin);   break;
            case 'C': send_dash(pin); send_dot(pin); send_dash(pin); send_dot(pin);  break;
            case 'G': send_dash(pin); send_dash(pin); send_dot(pin);                 break;
            case 'J': send_dot(pin); send_dash(pin); send_dash(pin); send_dash(pin); break;
            case 'K': send_dash(pin); send_dot(pin); send_dash(pin);                 break;
            case 'R': send_dot(pin); send_dash(pin); send_dot(pin);                  break;
            case 'U': send_dot(pin); send_dot(pin); send_dash(pin);                  break;
            case 'Z': send_dash(pin); send_dash(pin); send_dot(pin); send_dot(pin);  break;
            default: /* skip unused chars */                                         break;
        }
        send_char_space();
    }
}

void send_sos(uint8_t pin) {
    // SOS = ... --- ...
    for (int i = 0; i < 3; ++i) send_dot(pin);
    send_char_space();
    for (int i = 0; i < 3; ++i) send_dash(pin);
    send_char_space();
    for (int i = 0; i < 3; ++i) send_dot(pin);
    send_char_space();
}

int main() {
    // uart.write("INFO: application started\n");

    gpio.set_pin(0, true);
    
    // SOS -> gpio_dout[1]
    send_sos(1);

    // Jakub -> gpio_dout[2]
    send_morse("JAKUB", 2);

    // Brzazgacz -> gpio_dout[3]
    send_morse("BRZAZGACZ", 3);

    gpio.set_pin(0, false);

    while (true){};
    return 0;
}
