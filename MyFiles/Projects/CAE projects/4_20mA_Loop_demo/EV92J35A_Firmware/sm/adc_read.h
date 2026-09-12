#ifndef ADC_READ_H
#define ADC_READ_H

#include <stdint.h>
#include "../config.mcc/mcc_generated_files/adc/adc.h"

static inline uint16_t adc_read_filtered(void) {
    ADC_ChannelSelect(ADC_IN);
    ADC_ConversionStart();
    while (!ADC_IsConversionDone()) { }
    return (uint16_t)ADC_FilterValueGet();
}

#endif /* ADC_READ_H */
