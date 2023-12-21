#include "bongocat.h"

#include QMK_KEYBOARD_H

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;

static bool tap_anim = false;

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

static void animate(void) {
    if (!tap_anim) {
        current_idle_frame = (current_idle_frame + 1) % NUM_IDLE_FRAMES;
        uint8_t idx = abs((NUM_IDLE_FRAMES - 1) - current_idle_frame);
        oled_write_compressed_P(idle_block_map[idx], idle_frames[idx]);

        return;
    }
}

void bongocat_render(void) {
    if (get_current_wpm() != 000) {
        oled_on();

        tap_anim = true;

        if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
            anim_timer = timer_read32();
            animate();
        }
        anim_sleep = timer_read32();
        return;
    }

    tap_anim = false;

    // Turn off screen when timer threshold elapsed or reset time since last input
    if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        oled_off();
        return;
    }

    if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate();
    }
}

void bongocat_render_tap(uint16_t keycode) {
    static uint8_t tap_anim_toggle = false;

    // Display tap frames
    tap_anim_toggle = !tap_anim_toggle;
    oled_write_compressed_P(tap_block_map[tap_anim_toggle], tap_frames[tap_anim_toggle]);
}
