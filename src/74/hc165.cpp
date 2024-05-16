#include <mcupico/74/hc165.h>
#include <hardware/gpio.h>

HC165::HC165(uint8_t clk, uint8_t lat, uint8_t dat)
    : _clk(clk), _lat(lat), _dat(dat), _init(0)
{
}

void HC165::init() {
    if (_init == 0) {
        _init = 1;

        gpio_init(_clk);
        gpio_init(_lat);
        gpio_init(_dat);

        gpio_set_dir(_clk, GPIO_OUT);
        gpio_set_dir(_lat, GPIO_OUT);
        gpio_set_dir(_dat, GPIO_IN);

        gpio_put(_clk, 0);
        gpio_put(_lat, 1);
    }
}

void HC165::latch() const {
    gpio_put(_lat, 0);
    gpio_put(_lat, 1);
}

bool HC165::bitIn() const {
    bool value = gpio_get(_dat);

    gpio_put(_clk, 1);
    gpio_put(_clk, 0);

    return value;
}

uint8_t HC165::byteIn() const {
    uint8_t value = 0;

    for(uint8_t i = 0; i < 8; ++i) {
        if (bitIn()) {
            value |= 1 << i;
        }
    }

    return value;
}

uint16_t HC165::wordIn() const {
    uint16_t value = 0;

    for(uint8_t i = 0; i < 16; ++i) {
        if (bitIn()) {
            value |= 1 << i;
        }
    }

    return value;
}

uint32_t HC165::dwordIn() const {
    uint32_t value = 0;

    for(uint8_t i = 0; i < 32; ++i) {
        if (bitIn()) {
            value |= 1 << i;
        }
    }

    return value;
}

void HC165::multiIn(uint8_t unit, uint8_t* buf, uint32_t len) const {
    uint8_t counter = 0;
    
    while (len) {
        if (counter >= unit) {
            counter = 0;
            latch();
        }

        *buf++ = byteIn();
        counter++;
        len--;
    }
}