"""
Convert a bitmap from SSD1306 vertical-page format to SHARP memory display
horizontal format, and output a C header suitable for XC8 PIC18.

SSD1306 format: 21 pages × 144 columns, each byte = 8 vertical pixels, LSB=top
SHARP format:   168 rows × 18 bytes, each byte = 8 horizontal pixels, LSB=left

Also inverts polarity: SSD1306 uses 1=lit (white on black OLED),
SHARP uses 0=black(ink), 1=white(background). Since the Microchip logo is
white-on-black in the source, we invert so it displays as black-on-white.
"""

import re
import sys

INPUT_FILE = "MicrochipWafer_144x168.h"
OUTPUT_FILE = "microchip_logo_144x168.h"

WIDTH = 144
HEIGHT = 168
PAGES = HEIGHT // 8  # 21 pages for SSD1306 format
BYTES_PER_LINE = WIDTH // 8  # 18 bytes per SHARP scan line


def extract_bytes_from_header(filename):
    with open(filename, "r") as f:
        content = f.read()
    hex_values = re.findall(r"0x([0-9a-fA-F]{2})", content)
    return [int(h, 16) for h in hex_values]


def convert_vertical_to_horizontal(data):
    """Convert SSD1306 vertical-page data to horizontal row data."""
    # Build a 2D pixel array (height × width)
    pixels = [[0] * WIDTH for _ in range(HEIGHT)]

    # Decode SSD1306 vertical pages: data[page * WIDTH + col] contains
    # 8 vertical pixels at column `col`, rows page*8 through page*8+7,
    # with LSB = topmost pixel
    for page in range(PAGES):
        for col in range(WIDTH):
            byte = data[page * WIDTH + col]
            for bit in range(8):
                row = page * 8 + bit
                if row < HEIGHT:
                    pixels[row][col] = (byte >> bit) & 1

    # Encode as horizontal rows for SHARP display:
    # 18 bytes per row, LSB = leftmost pixel
    # Polarity inversion: source 1=lit → SHARP 0=black(ink)
    # So we invert: pixel=1 in source → bit=0 in output
    output = []
    for row in range(HEIGHT):
        for byte_idx in range(BYTES_PER_LINE):
            byte_val = 0
            for bit in range(8):
                col = byte_idx * 8 + bit
                if col < WIDTH:
                    # Invert: source pixel 1 (lit) → 0 (black/ink on SHARP)
                    if pixels[row][col] == 0:
                        byte_val |= (1 << bit)  # LSB = leftmost
            output.append(byte_val)

    return output


def write_c_header(filename, data):
    with open(filename, "w") as f:
        f.write("/**\n")
        f.write(" * Microchip logo bitmap for SHARP Memory Display (144x168, 1bpp)\n")
        f.write(" *\n")
        f.write(" * Format: horizontal, 18 bytes per row, LSB = leftmost pixel\n")
        f.write(" * Polarity: 0 = black (ink), 1 = white (background)\n")
        f.write(" * Total size: 3024 bytes (stored in program flash via const)\n")
        f.write(" */\n\n")
        f.write("#ifndef MICROCHIP_LOGO_144X168_H\n")
        f.write("#define MICROCHIP_LOGO_144X168_H\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write("#define LOGO_WIDTH   144\n")
        f.write("#define LOGO_HEIGHT  168\n\n")
        f.write("static const uint8_t microchip_logo[] = {\n")

        for row in range(HEIGHT):
            offset = row * BYTES_PER_LINE
            row_bytes = data[offset : offset + BYTES_PER_LINE]
            hex_str = ", ".join(f"0x{b:02x}" for b in row_bytes)
            f.write(f"    {hex_str},")
            if row % 8 == 7:
                f.write(f"  /* rows {row-7}-{row} */")
            f.write("\n")

        f.write("};\n\n")
        f.write("#endif /* MICROCHIP_LOGO_144X168_H */\n")


def main():
    print(f"Reading {INPUT_FILE}...")
    data = extract_bytes_from_header(INPUT_FILE)

    expected_size = PAGES * WIDTH  # 21 * 144 = 3024
    print(f"Extracted {len(data)} bytes (expected {expected_size})")
    if len(data) != expected_size:
        print(f"ERROR: Expected {expected_size} bytes, got {len(data)}")
        sys.exit(1)

    print("Converting from SSD1306 vertical-page to SHARP horizontal...")
    output = convert_vertical_to_horizontal(data)
    print(f"Output: {len(output)} bytes ({HEIGHT} rows × {BYTES_PER_LINE} bytes)")

    print(f"Writing {OUTPUT_FILE}...")
    write_c_header(OUTPUT_FILE, output)
    print("Done!")


if __name__ == "__main__":
    main()
