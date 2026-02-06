/**
 * @file LEDMux.cpp
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Implementation of the PIO-based LED Muxing logic.
 *
 * This file implements the hardware-level interaction with the RP2040 PIO 
 * block. It handles the loading of the 'led_mux.pio' program and manages 
 * the TX FIFO pushes. 
 * @note This implementation assumes a 4-bit mask is passed to the OSR.
 * @see LEDMux.h for the public API and configuration constants.
 */

#ifdef HAS_LED_MUX

#include "LEDMux.h"

// Constructor
LEDMux::LEDMux() {
    // Initialize internal variables if needed

}

void LEDMux::setup(){
    pio = pio0;
    uint offset = pio_add_program(pio, &led_mux_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_sm_config c = led_mux_program_get_default_config(offset);

    // Set the "out" pins starting at config::PIN_BASE, 4 pins wide
    sm_config_set_out_pins(&c, config::PIN_BASE, config::LED_BUS_SIZE);
    
    // Don't forget to set the GPIO directions!
    for(int i=0; i < config::LED_BUS_SIZE; i++) {
        pio_gpio_init(pio, config::PIN_BASE + i);
    }
    pio_sm_set_consecutive_pindirs(pio, sm, config::PIN_BASE, config::LED_BUS_SIZE, true);

    // Set clock divider (same as before)
    sm_config_set_clkdiv(&c, config::MUX_PIO_CLK);

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);

    pio_sm_put(pio, sm, 0);
}


bool LEDMux::estop(){
    // This is handled internally in the PIO so don't need to implement
    // unless you want to tie this to the main interrupt
    return true;
}

// Drop the corresponding bit mask into the state machine
void LEDMux::updateLED(config::Color color) {
    switch (color) {
        case config::Color::Red:
            pio_sm_put(pio, sm, 0b0001);
            break;
        case config::Color::Yellow:
            pio_sm_put(pio, sm, 0b0010);
            break;
        case config::Color::Green:
            pio_sm_put(pio, sm, 0b0100);
            break;
        case config::Color::Blue: 
            pio_sm_put(pio, sm, 0b1000);
            break;
        case config::Color::Off: 
            pio_sm_put(pio, sm, 0b0000);
            break;
        case config::Color::On: 
            pio_sm_put(pio, sm, 0b1111);
            break;
        default:
            pio_sm_put(pio, sm, 0b0000);
            break;
    }
}

// More elegant solution is to use pio_sm_put(pio, sm, 1 << static_cast<int>(color)) or something like that
void LEDMux::updateLEDs(uint8_t colors){
    constexpr uint32_t mask = (1u << config::LED_BUS_SIZE) - 1; // Create a mask that is length of the # of pins
    pio_sm_put(pio, sm, (mask & colors));                       // apparently it is cast to a uint32_t anyhow
}

void LEDMux::updateLEDSequence(uint32_t sequence){
    Serial.println(sequence);
    pio_sm_put(pio, sm, sequence);
};


#endif

