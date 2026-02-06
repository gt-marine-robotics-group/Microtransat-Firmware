import os
import subprocess
Import("env")

# Adjust these paths to your library structure
LIB_DIR = os.path.join(env.subst("$PROJECT_DIR"), "lib")
PIO_DIR = os.path.join(LIB_DIR, "PIO") # Where your .pio files live
OUTPUT_DIR = os.path.join(LIB_DIR, "PIOFiles") # Where .pio.h should go

def generate_pio_headers(source, target, env):
    if not os.path.exists(PIO_DIR):
        print(f"PIO: Directory {PIO_DIR} not found, skipping.")
        return

    pio_files = [f for f in os.listdir(PIO_DIR) if f.endswith(".pio")]
    
    for pio_file in pio_files:
        pio_path = os.path.join(PIO_DIR, pio_file)
        header_path = os.path.join(OUTPUT_DIR, f"{pio_file}.h")
        
        print(f"PIOASM: Compiling {pio_file} -> {header_path}")
        
        # Call pioasm (provided by the Pico toolchain)
        # Using -o c-sdk to generate the C/C++ header
        result = subprocess.run([
            "pioasm", "-o", "c-sdk", pio_path, header_path
        ], shell=True)
        
        if result.returncode != 0:
            print(f"Error: pioasm failed on {pio_file}")

# We run this before headers are scanned (top-level)
env.AddPreAction("buildprog", generate_pio_headers)