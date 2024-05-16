#ifndef __MCUPICO_74_HC165_H__
#define __MCUPICO_74_HC165_H__

#include <stdint.h>

/**
 * 74HC165 driver.
 */
class HC165 {
private:
    uint8_t _clk, _lat, _dat;
    uint8_t _init;

public:
    HC165(uint8_t clk, uint8_t lat, uint8_t dat);

public:
    /**
     * initialize 165 driver.
     */
    void init();
    
    /**
     * Trigger the latch to capture parralel inputs. 
     */
    void latch() const;

    /**
     * Read a bit.
     */
    bool bitIn() const;

    /**
     * Read a byte.
     */
    uint8_t byteIn() const;

    /**
     * Read an word.
     */
    uint16_t wordIn() const;

    /**
     * Read a dword.
     */
    uint32_t dwordIn() const;

    /**
     * Read bits from 165.
     * @param unit byte count to trigger latch.
     * @example
     * if unit == 2: latch will be triggered for every 2 bytes.
    */
    void multiIn(uint8_t unit, uint8_t* buf, uint32_t len) const;
};

#endif