/**
 * Q16 Fixed-Point Arithmetic Library — Implementation
 *
 * @file q16.c
 *
 * @brief Implements the Q16 utility functions used across the firmware for
 *        converting fixed-point values to display-friendly whole + tenths format.
 *
 * All operations here avoid division (expensive on PIC18 at ~100-200 cycles
 * for 32-bit). Instead, fractional extraction uses the identity:
 *   tenths_digit = (fractional_part * 10) >> 16
 * which is a single 16x16->32 multiply followed by a 16-bit shift.
 */

#include "q16.h"
#include <stdbool.h>

void q16_split_whole_tenths(int32_t value_q16, int16_t *whole, uint8_t *tenths) {
    /* Handle sign: work with absolute value, apply sign to whole at the end */
    bool negative = (value_q16 < 0);
    uint32_t abs_val;

    if (negative) {
        abs_val = (uint32_t)(-value_q16);
    } else {
        abs_val = (uint32_t)value_q16;
    }

    /* Extract integer part: upper 16 bits of absolute value */
    uint16_t int_part = (uint16_t)(abs_val >> Q16_SHIFT);

    /* Extract fractional tenths digit:
     * The lower 16 bits represent the fraction (0x0000 = 0.0, 0xFFFF = 0.9999...).
     * Multiplying by 10 and taking the upper 16 bits gives the first decimal digit.
     * This avoids division entirely — just a multiply and shift. */
    uint16_t frac_bits = (uint16_t)(abs_val & 0xFFFFu);
    *tenths = (uint8_t)(((uint32_t)frac_bits * 10u) >> 16);

    /* Apply sign to whole part */
    if (negative) {
        *whole = -(int16_t)int_part;
    } else {
        *whole = (int16_t)int_part;
    }
}
