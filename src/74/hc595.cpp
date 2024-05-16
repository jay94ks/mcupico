#include <mcupico/74/hc595.h>
#include <hardware/gpio.h>

HC595::HC595(uint8_t clk, uint8_t lat, uint8_t dat)
    : _clk(clk), _lat(lat), _dat(dat), _init(0)
{
}

void HC595::init() {
    if (_init == 0) {
        _init = 1;

        gpio_init(_clk);
        gpio_init(_lat);
        gpio_init(_dat);

        gpio_set_dir(_clk, GPIO_OUT);
        gpio_set_dir(_lat, GPIO_OUT);
        gpio_set_dir(_dat, GPIO_OUT);

        gpio_put(_clk, 0);
        gpio_put(_lat, 0);
        gpio_put(_dat, 0);
    }
}

void __attribute__((optimize("O0"))) HC595_DelayNs() {
    for(uint32_t i = 0; i < 10; ++i);
}

void HC595::bitOut(bool bit) const {
    gpio_put(_dat, bit ? 1 : 0);
    gpio_put(_clk, 1);
    HC595_DelayNs();

    gpio_put(_clk, 0);
    HC595_DelayNs();
}

void HC595::byteOut(uint8_t byte) const {
    for(uint8_t i = 0; i < 8; ++i) {
       bitOut((byte & (0x80u >> i)) != 0); 
    }
}

void HC595::wordOut(uint16_t word) const {
    for(uint8_t i = 0; i < 16; ++i) {
       bitOut((word & (0x8000u >> i)) != 0); 
    }
}

void HC595::dwordOut(uint32_t dword) const {
    for(uint8_t i = 0; i < 32; ++i) {
       bitOut((dword & (0x80000000u >> i)) != 0); 
    }
}

void HC595::latch() const {
    gpio_put(_lat, 1);
    gpio_put(_lat, 0);
}

void HC595::multiOut(uint8_t unit, const uint8_t* buf, uint32_t len) const {
    uint8_t counter = 0;
    while (len) {
        if (counter >= unit) {
            counter = 0;
            latch();
        }

        byteOut(*buf++);
        counter++;
        len--;
    }
}