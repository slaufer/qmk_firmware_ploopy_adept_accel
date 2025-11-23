# Exponential Acceleration Curve Keymap

This keymap implements a custom exponential approach acceleration curve for the Ploopy Adept trackball with VIA support for easy button remapping.

## Acceleration Formula

The acceleration follows the formula: `dx_eff = sign(dx) * scale * (1 - e^(-k*|dx|))`

Where:
- `dx` is the raw input from the sensor
- `k` (ACCEL_K) controls how quickly the acceleration ramps up
- `scale` (ACCEL_SCALE) sets the maximum speed multiplier

## Tuning Parameters

You can adjust these values at the top of `keymap.c`:

- **ACCEL_K**: Default 0.12 (slower acceleration)
  - Lower values (0.08-0.10): Even gentler, more gradual acceleration
  - Higher values (0.15-0.25): Faster, more aggressive acceleration

- **ACCEL_SCALE**: Default 12.0 (moderate maximum speed)
  - Lower values (8-10): Slower maximum speed
  - Higher values (15-20): Faster maximum speed

## Drag Scroll Configuration

- **PLOOPY_DRAGSCROLL_MOMENTARY**: Enabled - Drag scroll only works while the button is held down
- **PLOOPY_DRAGSCROLL_INVERT**: Enabled - Drag scroll direction is reversed

To change these behaviors, comment out the defines in `keymap.c:31-32`

## Building

```bash
qmk compile -kb ploopyco/madromys/rev1_001 -km accel
```

or

```bash
qmk flash -kb ploopyco/madromys/rev1_001 -km accel
```

## Behavior

- Small movements: Start very slow and precise
- Large movements: Quickly accelerate to maximum speed
- Drag scroll mode: Acceleration is disabled for scrolling

## VIA Support

This keymap includes VIA support, allowing you to:
- Remap buttons in real-time using the VIA software (https://www.caniusevia.com/)
- Configure up to 8 layers
- The acceleration curve continues to work regardless of button remapping

**Important**: The acceleration affects pointer movement only, not button functions. VIA lets you change button mappings while the custom acceleration curve continues to work in the background.
