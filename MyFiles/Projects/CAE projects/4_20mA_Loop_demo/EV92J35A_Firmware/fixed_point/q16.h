/**
 * Q16 Fixed-Point Arithmetic Library
 *
 * @file q16.h
 *
 * @brief Provides the Q16 (16 fractional bits) fixed-point representation used
 *        throughout the firmware to eliminate floating-point math on the
 *        PIC18F56Q71's 1 MHz core (no hardware FPU).
 *
 * Q16 format:
 *   A real number is stored as an int32_t scaled by 65536 (2^16).
 *   The upper 16 bits hold the integer (signed) part; the lower 16 bits
 *   hold the fractional part.
 *
 *   Example: 12.75 is stored as 12.75 * 65536 = 835,584 (0x000CC000)
 *            -3.5  is stored as -3.5  * 65536 = -229,376 (0xFFFC8000)
 *
 * Arithmetic:
 *   Addition/subtraction of two Q16 values is normal int32_t add/sub.
 *   Multiplying a Q16 value by an integer produces a Q16 result directly.
 *   Multiplying two Q16 values requires a right-shift of 16 after the multiply.
 *
 * Why Q16 and not Q8 or Q24:
 *   - Q16 provides 1/65536 = 0.0000153 resolution (far exceeds our 0.1 display)
 *   - The worst-case intermediate (TF4: 81920 * 4095 = 335 million) still fits
 *     in int32_t with 6.4x headroom
 *   - Extraction of the integer part is a 16-bit shift, which on PIC18 compiles
 *     to efficient byte-move instructions
 */

#ifndef Q16_H
#define Q16_H

#include <stdint.h>

/* Number of fractional bits in the Q16 representation */
#define Q16_SHIFT   (16)

/* The scaling factor: 2^16 = 65536 */
#define Q16_ONE     (65536L)

/**
 * Convert a compile-time integer constant to Q16.
 * Example: Q16_FROM_INT(4) yields 262144L (= 4 * 65536).
 * Only valid for integer arguments — use Q16_FROM_FLOAT for fractional constants.
 */
#define Q16_FROM_INT(n)     ((int32_t)(n) * Q16_ONE)

/**
 * Convert a compile-time floating-point constant to Q16.
 * The XC8 compiler evaluates this at compile time when the argument is a
 * literal, so it incurs zero runtime cost and does NOT link the float library.
 * Example: Q16_FROM_FLOAT(1.25f) yields 81920L.
 */
#define Q16_FROM_FLOAT(f)   ((int32_t)((f) * 65536.0f))

/**
 * Split a Q16 fixed-point value into its whole (integer) part and the first
 * decimal digit (tenths). This is the standard pattern for displaying Q16
 * values as "XX.Y" on the SHARP LCD without using printf %f (which XC8 does
 * not support).
 *
 * For negative values, the whole part carries the sign and the tenths digit
 * is always positive (e.g., -6.2 yields whole=-6, tenths=2).
 *
 * Implementation uses only bit shifts and a 16x16->32 multiply — no division.
 *
 * @param value_q16  The Q16 fixed-point value to split
 * @param whole      [out] Integer part (signed)
 * @param tenths     [out] First decimal digit, 0-9 (always positive)
 */
void q16_split_whole_tenths(int32_t value_q16, int16_t *whole, uint8_t *tenths);

#endif /* Q16_H */
