#ifndef __MCUPICO_74_HC595_H__
#define __MCUPICO_74_HC595_H__

#include <stdint.h>

/**
 * 74HC595 driver.
 */
class HC595 {
private:
    uint8_t _clk, _lat, _dat;
    uint8_t _init;

public:
    HC595(uint8_t clk, uint8_t lat, uint8_t dat);

public:
    /**
     * initialize 595 driver.
     */
    void init();

    /**
     * put a bit to HC595. 
     */
    void bitOut(bool bit) const;

    /**
     * put a byte to HC595.
     */
    void byteOut(uint8_t byte) const;

    /**
     * put an word to HC595.
     */
    void wordOut(uint16_t word) const;

    /**
     * put a dword to HC595.
     */
    void dwordOut(uint32_t dword) const;

    /**
     * trigger the latch in 595.
     */
    void latch() const;

    /**
     * write bits to HC595. 
     * @param unit byte count to trigger latch.
     * @example
     * if unit == 2: latch will be triggered for every 2 bytes.
     */
    void multiOut(uint8_t unit, const uint8_t* buf, uint32_t len) const;

};

#endif