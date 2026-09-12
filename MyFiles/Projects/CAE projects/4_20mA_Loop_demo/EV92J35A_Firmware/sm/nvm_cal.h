/**
 * NVM Calibration Storage — EEPROM persistence for hardware calibration constants
 *
 * @file nvm_cal.h
 *
 * @brief Provides read/write/validate/invalidate for the calibration data
 *        stored in the PIC18F56Q71's 256-byte EEPROM (Data Flash Memory).
 *
 * A valid-marker byte (0xCA) at offset 0 distinguishes a calibrated device
 * from a fresh/erased chip (where EEPROM reads 0xFF). On first boot of an
 * uncalibrated device, NvmCal_IsValid() returns false and compile-time
 * defaults are used.
 */

#ifndef NVM_CAL_H
#define NVM_CAL_H

#include <stdint.h>
#include <stdbool.h>

#define NVM_CAL_VALID_MARKER  (0xCAu)

typedef struct {
    uint8_t  marker;             /* 0xCA = valid calibration stored */
    uint8_t  digipot_trim;       /* MCP4152 wiper position */
    uint16_t afe_dac_trim;       /* MCU DAC1 offset trim code */
    uint16_t dac_at_4mA;         /* External DAC code for 4.000 mA */
    uint16_t dac_at_20mA;        /* External DAC code for 20.000 mA */
    uint16_t adc_at_sensor_low;  /* ADC reading at sensor 0 PSI */
    uint16_t adc_at_sensor_high; /* ADC reading at sensor 50 PSI */
} NvmCalData_t;

/**
 * @brief Check if valid calibration data is stored in EEPROM.
 * @return true if the marker byte == NVM_CAL_VALID_MARKER
 */
bool NvmCal_IsValid(void);

/**
 * @brief Read the stored calibration data from EEPROM.
 * @param out Pointer to struct to fill with stored values.
 */
void NvmCal_Read(NvmCalData_t *out);

/**
 * @brief Write calibration data to EEPROM.
 * @param data Pointer to struct containing values to store.
 */
void NvmCal_Write(const NvmCalData_t *data);

/**
 * @brief Invalidate stored calibration (write 0xFF to marker byte).
 * After this call, NvmCal_IsValid() returns false and the next init
 * will use compile-time defaults.
 */
void NvmCal_Invalidate(void);

#endif /* NVM_CAL_H */
