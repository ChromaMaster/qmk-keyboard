#include "bongocat.h"
#include "bongocat_frames.h"

#include QMK_KEYBOARD_H

uint32_t screen_on_timeout = 0;

uint32_t idle_animation_frame_timeout = 0;
uint8_t current_idle_frame = 0;

static bool tap_animation_toggle = false;
uint32_t tap_animation_timeout = 0;

static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
        uint8_t bit = i % 8;
        uint8_t map_index = i / 8;
        uint8_t _block_map = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}

static void animate_idle(void) {
    current_idle_frame = (current_idle_frame + 1) % NUM_IDLE_FRAMES;
    uint8_t idx = abs((NUM_IDLE_FRAMES - 1) - current_idle_frame);
    oled_write_compressed_P(idle_block_map[idx], idle_frames[idx]);
}


static void animate_tap(void) {
    oled_write_compressed_P(tap_block_map[tap_animation_toggle], tap_frames[tap_animation_toggle]);
}

void bongocat_render(void) {
    // Handle OLED screen power state using the timeout.
    if (timer_elapsed32(screen_on_timeout) <= OLED_TIMEOUT) {
        if(!is_oled_on()) oled_on();
    } else {
        if(is_oled_on()) oled_off();
        return;
    }

    // Stop the tap animation if the timeout is reached
    if (timer_elapsed32(tap_animation_timeout) <= TAP_ANIMATION_TIMEOUT) {
        animate_tap();
    } else {
        // Render idle animation frame once the timeout is reached
        if (timer_elapsed32(idle_animation_frame_timeout) > IDLE_FRAME_DURATION) {
            idle_animation_frame_timeout = timer_read32();
            animate_idle();
            return;
        }
    }

    return;
}

void bongocat_toggle_tap(void){
    // Refresh the OLED screen timeout when the tap animation is toggled.
    // This will effectively turn/keep the screen on while the tap animation is active.
    screen_on_timeout = timer_read32();

    // Refresh the timeout when the tap animation is toggled.
    tap_animation_timeout = timer_read32();
    
    // Toggle the tap animation
    tap_animation_toggle = !tap_animation_toggle;
}
