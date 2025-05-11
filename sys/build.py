import os
import sys
import subprocess
from pathlib import Path

def run(cmd):
    print(cmd)
    res = subprocess.call(cmd)
    if res:
        print(f"{cmd} return non-zero exit code: {res}")
        sys.exit(1)

proot = Path(".").resolve()

arch = sys.argv[1]
bits = sys.argv[2]

cc = ["clang", "-static", "-target", f"{arch}-none-none", "-I../include", "-ffreestanding", "-nostdlib", f"-m{bits}", f"-DARCH=ARCH_{arch.upper()}", "-c"]

tasks = []
for root, _, files in os.walk(proot):
    for f in files:
        if f.endswith(".o"):
            break
        source = Path(root) / f
        output = Path(proot) / "build" / (f + '.o')
        if f.endswith(".c"):
            tasks.append([*cc, str(source), "-o", str(output)])
        elif f.endswith(".s"):
            tasks.append(["nasm", "-f", f"elf{bits}", str(source), "-o", str(output)])

run(["rm", "-rf", "build"])
run(["mkdir", "-p", "build"])
            
for task in tasks:
    run(task)

objects = ([str(f) for f in (Path(proot) / "build").glob("*.o")])
print(objects)

run([f"ld.lld", "-T", "link.ld", *objects,  "-o",  "../krnl"])
