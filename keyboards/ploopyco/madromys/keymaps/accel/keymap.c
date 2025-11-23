/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <math.h>

// Acceleration curve parameters
// Adjust these to tune the acceleration behavior
#ifndef ACCEL_K
#    define ACCEL_K 0.1     // Controls how quickly acceleration ramps up (higher = faster ramp)
#endif
#ifndef ACCEL_SCALE
#    define ACCEL_SCALE 10.0  // Maximum multiplier for movement (adjust for comfort)
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( MS_BTN3, MS_BTN4, MS_BTN5, DRAG_SCROLL, MS_BTN1, MS_BTN2 ),
    [1] = LAYOUT( _______, _______, _______,     _______, _______, _______ ),
    [2] = LAYOUT( _______, _______, _______,     _______, _______, _______ ),
    [3] = LAYOUT( _______, _______, _______,     _______, _______, _______ )
};

// Apply exponential approach curve acceleration
static float apply_acceleration(int8_t val) {
    if (val == 0) return 0;

    float abs_val = fabsf((float)val);

    // Deadzone for sensor noise
    if (abs_val < 0.5f) return 0;

    float sign = (val > 0) ? 1.0f : -1.0f;

    // Exponential approach curve: output = scale * (1 - e^(-k * input))
    float accelerated = ACCEL_SCALE * (1.0f - expf(-ACCEL_K * abs_val));

    // Ensure at least 1 pixel movement
    if (accelerated < 1.0f) accelerated = 1.0f;

    return sign * accelerated;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Only apply acceleration to regular pointer movement, not during drag scroll
    if (!is_drag_scroll) {
        float x_accel = apply_acceleration(mouse_report.x);
        float y_accel = apply_acceleration(mouse_report.y);

        mouse_report.x = (int8_t)roundf(x_accel);
        mouse_report.y = (int8_t)roundf(y_accel);
    }

    return mouse_report;
}
