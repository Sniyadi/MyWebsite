# EV92J35A Firmware

Official demonstration firmware for the Microchip EV92J35A 4-20 mA pressure transmitter evaluation board. Reads a 0-50 PSI pressure sensor, converts the measurement to a 4-20 mA current loop signal per the NAMUR NE43 standard, and provides a live display with calibration and diagnostic tools.

## Project Overview

This firmware demonstrates a complete industrial 4-20 mA current loop transmitter implementation on a PIC18-class microcontroller. Key features:

- **NAMUR NE43 compliant** alarm signaling (3.6 mA under-range, 21.0 mA over-range) with hysteresis
- **Constants-centric calibration** system with NVM persistence across power cycles
- **User-configurable measurement range** (any pressure sub-range within the sensor span)
- **Q16 fixed-point math** throughout (no floating-point library, ~260 cycles per conversion at 1 MHz)
- **Character-cell display driver** using only ~278 bytes of RAM (no framebuffer)

## Hardware Requirements

### EV92J35A Evaluation Board

A custom PCB integrating all required circuitry:

| Subsystem | Key Components |
|-----------|---------------|
| Microcontroller | PIC18F26Q71 (64 KB flash, 4 KB RAM, 256 B EEPROM, 1 MHz HFINTOSC) |
| Analog Front End | MCP6V14 zero-drift instrumentation amplifier |
| Loop Driver | 4-20 mA current regulation circuit (based on EV34C35A reference design) |
| External DAC | MCP48CMD21 (12-bit, SPI) |
| Digital Potentiometer | MCP4152 (8-bit, SPI, sets loop current floor) |
| Power | On-board conditioning circuitry |
| Display Connector | Breakout for Adafruit SHARP Memory Display |

### External Components

| Component | Description |
|-----------|-------------|
| Display | Adafruit 1.3" SHARP Memory Display (144x168 pixels, SPI) |
| Pressure Sensor | Strain Measurement Devices P571 (0-50 PSI, analog output) |
| Input | 5-button joystick (UP / DOWN / LEFT / RIGHT / PUSH) |

### Pin Assignments (PIC18F26Q71)

| Pin | Function |
|-----|----------|
| RA0 | ADC input (pressure sensor via AFE) |
| RA2 | DAC1 output (AFE offset trim) |
| RB0 | CS - SHARP display |
| RB1 | SPI1 SDO (shared bus) |
| RB2 | SPI1 SCK (shared bus) |
| RB3 | SPI1 SDI (shared bus) |
| RB4 | CS - MCP4152 (loop driver digipot) |
| RB5 | CS - MCP48CMD21 (loop driver DAC) |
| RC0 | Joystick PUSH |
| RC1 | Joystick LEFT |
| RC2 | Joystick UP |
| RC5 | Joystick DOWN |
| RC6 | Joystick RIGHT |

## Build Environment

- **IDE:** MPLAB Extensions for VS Code (latest)
- **Compiler:** Microchip XC8 (latest)
- **Code Generator:** MCC Melody (peripheral configuration)

### Required Compiler Setting

The NVM (EEPROM) driver requires **Address Qualifiers** to be set to **Require** under Project Properties > XC8 Compiler > Optimizations. Without this, EEPROM writes will silently fail.

### Project Structure

| Path | Purpose |
|------|---------|
| `config.mcc/` | MCC-generated peripheral drivers and `main.c` |
| `sm/` | State machine framework, context module, EEPROM configuration |
| `sm/states/` | Individual state implementations |
| `loop_driver/` | Loop driver board-level API (DAC + digipot + Current-to-DAC TF) |
| `sharp_display/` | SHARP memory display character-cell driver |
| `fixed_point/` | Q16 fixed-point arithmetic library |
| `systick/` | 10 Hz system tick timer |
| `_build/` | CMake build tree (can be deleted) |
| `out/` | Final build artifacts |

## Usage Guide

On power-up, the Microchip logo displays for 3 seconds, then the system enters MONITOR mode. Press LEFT at any time in MONITOR to access the menu.

### Menu Navigation

- **UP / DOWN** — scroll through menu items
- **PUSH** — select highlighted item

### MONITOR (Normal Operation)

Displays live pressure (PSI) and loop current (mA). The system reads the pressure sensor, converts the reading to a 4-20 mA signal, and drives the current loop.

If the measured pressure goes outside the configured range:
- Below range: drives 3.6 mA and displays "LO ALARM"
- Above range: drives 21.0 mA and displays "HI ALARM"

Alarm thresholds include hysteresis to prevent display flicker near the boundaries.

### RANGE SET (User Preference)

Defines which pressure values correspond to 4 mA and 20 mA. This is not calibration - it sets the user's desired measurement window within the sensor's physical range.

1. The system forces the loop to 4 mA. Apply the desired low-end pressure to the sensor and press RIGHT to capture.
2. The system forces the loop to 20 mA. Apply the desired high-end pressure and press RIGHT to capture.
3. Review the captured values. Press RIGHT to apply, or LEFT to cancel.

Requires system calibration to be completed first (so the DAC codes for 4/20 mA are known).

### CALIBRATE (System Calibration Wizard)

A 6-step guided procedure that characterizes the hardware. Requires an external current meter in the loop and a calibrated pressure source.

| Step | Action | Equipment |
|------|--------|-----------|
| 1. AFE Offset | Apply 0 PSI to the sensor. Adjust the MCU-integrated DAC1 to null the amplifier offset. | None |
| 2. Loop Floor | Adjust digipot until the loop reads ~3.6 mA (DAC held at 0). | Current meter |
| 3. DAC at 4 mA | Adjust DAC code until meter reads exactly 4.000 mA. | Current meter |
| 4. DAC at 20 mA | Adjust DAC code until meter reads exactly 20.000 mA. | Current meter |
| 5. Sensor Low | Apply 0 PSI, press RIGHT to capture ADC reading. | Pressure source |
| 6. Sensor High | Apply 50 PSI, press RIGHT to capture ADC reading. | Pressure source |

After confirming, all values are stored to EEPROM and persist across power cycles.

Controls during calibration:
- **UP / DOWN** — adjust current parameter
- **RIGHT** — confirm step and advance
- **LEFT** — cancel entire calibration (restores all previous values)

### MANUAL (DAC Evaluation)

Directly control the loop driver DAC output. Displays the DAC code and the corresponding computed current. Useful for:
- Comparing requested vs. actual loop current (with external meter)
- Evaluating DAC linearity
- Debugging calibration discrepancies

Controls: UP/DOWN to adjust DAC code, LEFT to return to menu.

### DEMO (Triangle Wave Sweep)

Automatically sweeps the DAC output from 0 to 4095 and back in a triangle wave pattern (step size: 64 counts per tick). Displays the current DAC code and computed mA. Useful for observing the full output range on an oscilloscope or meter.

### SPLASH (Logo Display)

Displays the Microchip logo for 3 seconds.

### FACTORY RST (Factory Reset)

Invalidates the stored calibration in EEPROM and reinitializes the system with compile-time defaults. The next power cycle will behave as if the device has never been calibrated.

## Theory of Operation

### Signal Path

```
Pressure -> Sensor (P571) -> AFE (MCP6V14) -> ADC (12-bit, burst-averaged)
    -> [ADC-to-Pressure]  -> Displayed PSI
    -> [ADC-to-Current]   -> Alarm check
    -> [ADC-to-DAC]       -> External DAC (MCP48CMD21) -> Loop current
```

The firmware converts ADC readings to engineering values using four linear transfer functions, all implemented as Q16 fixed-point slope/intercept pairs: `result = slope * input + intercept`.

### Transfer Function 1: ADC-to-Pressure

Converts the 12-bit ADC reading to pressure in PSI. Derived from two calibration points captured during the sensor characterization step.

```
P = m_p * ADC + b_p

where:
    m_p = (P_max - P_min) / (ADC_high - ADC_low)
    b_p = P_min - m_p * ADC_low

    P_min = 0 PSI       (sensor physical minimum)
    P_max = 50 PSI      (sensor physical maximum)
    ADC_low = adc_at_sensor_low   (calibration constant: ADC reading at 0 PSI)
    ADC_high = adc_at_sensor_high (calibration constant: ADC reading at 50 PSI)
```

### Transfer Function 2: ADC-to-Current

Converts the 12-bit ADC reading to the requested loop current in mA. The mapping depends on both the sensor calibration (TF1) and the user's range settings.

```
I = m_i * ADC + b_i

where:
    m_i = (I_max - I_min) / (ADC_range_high - ADC_range_low)
    b_i = I_min - m_i * ADC_range_low

    I_min = 4.0 mA      (valid measurement band low)
    I_max = 20.0 mA     (valid measurement band high)
    ADC_range_low  = ADC count where pressure equals the user's 4 mA setpoint
    ADC_range_high = ADC count where pressure equals the user's 20 mA setpoint
```

The ADC range boundaries are computed by inverting TF1:

```
    ADC_range_low  = (P_user_low  - b_p) / m_p
    ADC_range_high = (P_user_high - b_p) / m_p

    P_user_low  = user-selected pressure at 4 mA  (from RANGE SET)
    P_user_high = user-selected pressure at 20 mA (from RANGE SET)
```

### Transfer Function 3: Current-to-DAC

Converts a milliamp value to a 12-bit DAC code. Owned by the loop_driver module. Derived from two calibration points measured with an external current meter.

```
DAC = m_d * I + b_d

where:
    m_d = (DAC_20 - DAC_4) / (20.0 - 4.0)
    b_d = DAC_4 - m_d * 4.0

    DAC_4  = dac_at_4mA   (calibration constant: DAC code producing 4.000 mA)
    DAC_20 = dac_at_20mA  (calibration constant: DAC code producing 20.000 mA)
```

### Transfer Function 4: ADC-to-DAC (Composite)

The per-tick hot path. Maps ADC reading directly to DAC code in a single multiply-add, bypassing the intermediate mA computation. This is mathematically equivalent to composing TF2 and TF3, but avoids a second multiplication (and potential Q16 overflow).

```
DAC = m_c * ADC + b_c

where:
    m_c = (DAC_20 - DAC_4) / (ADC_range_high - ADC_range_low)
    b_c = DAC_4 - m_c * ADC_range_low
```

### Q16 Fixed-Point Encoding

All slope and intercept values are stored as `int32_t` scaled by 65536 (left-shifted 16 bits). This means:

```
stored_value = real_value * 65536

Computation:  result_q16 = slope_q16 * adc_counts + intercept_q16
Integer part: result_int = result_q16 >> 16
```

The 16-bit fractional part provides a resolution of 1/65536 = 0.000015, far exceeding the 0.1 display resolution. On PIC18, extracting the integer part is a 2-byte move (the upper 16 bits of the int32).

### Alarm Behavior

After computing the loop current via TF2, the monitor state checks for out-of-range conditions:

```
If I < 3.8 mA  (alarm entry threshold):   drive 3.6 mA, display LO ALARM
If I > 20.5 mA (alarm entry threshold):   drive 21.0 mA, display HI ALARM

To clear a low alarm:   I must rise above 4.0 mA
To clear a high alarm:  I must fall below 20.0 mA
```

The asymmetric entry/exit thresholds (0.2 mA low dead band, 0.5 mA high dead band) prevent rapid toggling when ADC noise causes the signal to hover near a boundary.

## Code Architecture Overview

### State Machine Framework

The firmware is organized as a data-driven state machine with 8 states. A const array of function-pointer structs (entry/do/exit) is indexed by a contiguous enum. The framework (`sm.c`) provides:
- `SM_Init()` — enters STATE_INIT on startup
- `SM_Run()` — dispatches to the current state's `do_action` (called once per 10 Hz tick)
- `SM_Transition()` — the single enforcement point for all state changes (exit old, enter new)

Each state is a self-contained module with its own `.c`/`.h` files. Adding a state requires only a new enum value and a new array entry.

### Module Responsibilities

| Module | Owns |
|--------|------|
| `sm_context` | Sensor/AFE calibration constants, user range settings, derived ADC-to-Current/Pressure/DAC transfer functions, per-tick compute functions |
| `loop_driver` | Loop driver hardware (DAC, digipot), loop driver calibration constants (dac_at_4mA, dac_at_20mA, digipot_trim), Current-to-DAC transfer function |
| `nvm_cal` | EEPROM read/write for calibration persistence |
| `sharp_display` | Character-cell display with dirty-line tracking, font rendering |
| `systick` | 10 Hz tick counter, elapsed-time checks |
| `input_manager` | Debounced joystick events (IOC + TMR2 debounce) |
| `fixed_point` | Q16 arithmetic and display formatting |

### Data Flow (Normal Operation)

```raw
Pressure Sensor -> AFE (MCP6V14) -> ADC (12-bit, burst-averaged)
    -> SmContext_ComputePressure_q16()      -> Display (PSI)
    -> SmContext_ComputeLoopCurrent_mA_q16() -> Alarm check
    -> SmContext_ComputeDacFromAdc()         -> LoopDriver_SetDac() -> Loop current
```

### Constants-Centric Calibration

Raw measured hardware values are the single source of truth. All transfer function parameters are derived by `SmContext_RecomputeTransferFunctions()`, which is called:
- Once at startup (from defaults or NVM)
- After any calibration constant changes
- After range settings change

This ensures transfer functions are always mutually consistent and eliminates the possibility of partial/invalid state.

### Q16 Fixed-Point Math

All engineering computations use Q16 format (int32_t scaled by 65536). This eliminates the ~1-2 KB XC8 float library and reduces per-tick computation from ~2200 cycles to ~260 cycles. The 16-bit fractional part provides resolution of 0.000015 — far exceeding the 0.1 display requirement.

## Calibration System

### Dependency Hierarchy

```raw
Level 0: Design constants (compiled in, never change)
    ADC_MAX, AFE_DAC_MAX, LOOP_DAC_MAX, SENSOR_RANGE, VALID_CURRENT band

Level 1: Independent hardware trims
    afe_dac_trim     — MCU DAC1 code that nulls AFE offset
    digipot_trim     — MCP4152 wiper that sets ~3.6 mA floor at DAC=0

Level 2: Requires Level 1 (digipot floor must be set first)
    dac_at_4mA       — DAC code producing exactly 4.000 mA
    dac_at_20mA      — DAC code producing exactly 20.000 mA

Level 3: Requires Level 1 (AFE offset must be nulled first)
    adc_at_sensor_low  — ADC reading at 0 PSI
    adc_at_sensor_high — ADC reading at 50 PSI

Derived (recomputed automatically):
    ADC-to-Pressure, ADC-to-Current, Current-to-DAC, ADC-to-DAC (composite)
```

### NVM Storage

Calibration constants are stored in the PIC18F26Q71's 256-byte EEPROM starting at address 0. A marker byte (0xCA) indicates valid data. On startup, if the marker is present, stored values override compile-time defaults. Factory reset writes 0xFF to the marker, invalidating the stored data.

### Extended Loop Range

The current loop operates over approximately 3.6-22 mA:
- **3.6 mA** — Low alarm (NAMUR NE43 downscale burnout)
- **4.0 mA** — Low end of valid measurement band
- **20.0 mA** — High end of valid measurement band
- **21.0 mA** — High alarm (NAMUR NE43 upscale burnout)
- **~22 mA** — Hardware ceiling (DAC = 4095)

The DAC codes for 4 mA and 20 mA are calibration constants that fall within the DAC range, not at the endpoints.
