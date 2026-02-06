/**
 * @file LEDPIO.cpp
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Implementation of the PIO-based LED Variable Blinking logic.
 *
 * This file implements the hardware-level interaction with the RP2040 PIO 
 * block. It handles the loading of the 'blink_input.pio' program and manages 
 * the TX FIFO pushes. 
 * @note This implementation is tuned to map motor PWMs to a "natural" blink speed
 * @see LEDPIO.h for the public API and configuration constants.
 */

#ifdef HAS_INDICATOR_LED

#include "LEDPIO.h"

// Constructor
LEDPIO::LEDPIO() {
    // Initialize internal variables if needed

}

void LEDPIO::setup(){
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_input_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_sm_config c = blink_input_program_get_default_config(offset);

    // 1. Setup the Output Pin (GPIO 16)
    sm_config_set_set_pins(&c, config::LED_PIN, 1);
    pio_gpio_init(pio, config::LED_PIN);
    pio_sm_set_consecutive_pindirs(pio, sm, config::LED_PIN, 1, true);

    // 2. Setup the Input Pin (GPIO 17)
    // This tells the 'wait' instruction which pin is index 0
    sm_config_set_in_pins(&c, config::TRIGGER_PIN); 
    pio_gpio_init(pio, config::TRIGGER_PIN);
    // Set the direction of GPIO 17 to 'input' (false)
    pio_sm_set_consecutive_pindirs(pio, sm, config::TRIGGER_PIN, 1, false);

    // 3. Optional: Set internal pull-down so it doesn't float
    gpio_pull_down(config::TRIGGER_PIN);

    // Set clock divider (same as before)
    sm_config_set_clkdiv(&c, config::PIO_CLK);

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);

    pio_sm_put(pio0, sm, 25);
}

bool LEDPIO::estop(){
    // This is handled internally in the PIO so don't need to implement
    // unless you want to tie this to the main interrupt
    return true;
}

void LEDPIO::updateBlink(uint8_t pwm) {
    uint32_t pio_delay = map(pwm, 0, 255, 100, 1);
    if (abs((int32_t)pio_delay - (int32_t)last_pio_delay) > 5) {
        if (pio_sm_is_tx_fifo_empty(pio0, sm)){
            pio_sm_put(pio0, sm, pio_delay);
            // Serial.println("re-fed");
            Serial.print("PIO Delay: "); 
            Serial.println(pio_delay);
            // pio_sm_put(pio0, sm, pio_delay);
            last_pio_delay = pio_delay;
        }
    }
}

#endif