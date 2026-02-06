import os
import subprocess
Import("env")

# We use env.subst("$PROJECT_DIR") to get the absolute path to your project
# Modify these paths to point exactly where your files are
# LIB_DIR = os.path.join(env.subst("$PROJECT_DIR"), "lib", "Protobuf")
LIB_DIR = os.path.join(env.subst("$PROJECT_DIR"), "lib")
PROTO_DIR = os.path.join(LIB_DIR, "Proto")
OUTPUT_DIR = os.path.join(LIB_DIR, "ProtoFiles") # Where the .pb.c/.pb.h will go
PY_OUTPUT_DIR = os.path.join(LIB_DIR, "ProtoSim") # Where the .pb.c/.pb.h will go

def generate_nanopb_files(source, target, env):
    # Create output directory if it doesn't exist
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    proto_files = [f for f in os.listdir(PROTO_DIR) if f.endswith(".proto")]
    
    for proto_file in proto_files:
        proto_path = os.path.join(PROTO_DIR, proto_file)
        print(f"Nanopb: Compiling {proto_file}...")
        
        # We use shell=True for Windows compatibility
        result = subprocess.run([
            "nanopb_generator",
            "-I", PROTO_DIR,
            "-D", OUTPUT_DIR,
            proto_path
        ], shell=True)
        
        if result.returncode != 0:
            print(f"Error: Nanopb failed on {proto_file}")

        # 2. Generate Python Files for Testing/Host
        print(f"Protoc: Generating Python bindings for {proto_file}...")
        subprocess.run([
            "protoc",
            f"--proto_path={PROTO_DIR}",
            f"--python_out={PY_OUTPUT_DIR}",
            proto_path
        ], shell=True)

# This triggers the script every time you build
env.AddPreAction("buildprog", generate_nanopb_files)