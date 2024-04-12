#!/usr/bin/env python3

import sys


def bin_to_c_array(input_file, output_file, array_name, offset):
    with open(input_file, "rb") as file:
        data = file.read()

    with open(output_file, "w") as file:
        file.write(f"uint8_t {array_name}[] = {{\n")
        line_length = 0
        for byte in data[offset - 1 :]:
            file.write(f"0x{byte:02X}, ")
            line_length += 1
            if (
                line_length == 12
            ):  # Change this value to control how many bytes per line
                file.write("\n")
                line_length = 0
        file.write("\n};\n")


bin_to_c_array(sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4], 0))
