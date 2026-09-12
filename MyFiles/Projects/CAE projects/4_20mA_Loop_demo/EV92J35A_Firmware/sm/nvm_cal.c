/**
 * NVM Calibration Storage — Implementation
 *
 * @file nvm_cal.c
 *
 * @brief Reads and writes the NvmCalData_t struct to/from the PIC18F56Q71's
 *        EEPROM using the MCC-generated NVM driver (byte-at-a-time access).
 */

#include "nvm_cal.h"
#include "../config.mcc/mcc_generated_files/nvm/nvm.h"

#define CAL_DATA_SIZE  ((uint8_t)sizeof(NvmCalData_t))

bool NvmCal_IsValid(void) {
    return EEPROM_Read(EEPROM_START_ADDRESS) == NVM_CAL_VALID_MARKER;
}

void NvmCal_Read(NvmCalData_t *out) {
    uint8_t *dst = (uint8_t *)out;
    for (uint8_t i = 0; i < CAL_DATA_SIZE; i++) {
        dst[i] = EEPROM_Read(EEPROM_START_ADDRESS + i);
    }
}

void NvmCal_Write(const NvmCalData_t *data) {
    const uint8_t *src = (const uint8_t *)data;

    NVM_UnlockKeySet(UNLOCK_KEY);

    for (uint8_t i = 0; i < CAL_DATA_SIZE; i++) {
        EEPROM_Write(EEPROM_START_ADDRESS + i, src[i]);
        while (NVM_IsBusy()) { }
    }

    NVM_UnlockKeyClear();
}

void NvmCal_Invalidate(void) {
    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(EEPROM_START_ADDRESS, 0xFF);
    while (NVM_IsBusy()) { }
    NVM_UnlockKeyClear();
}
