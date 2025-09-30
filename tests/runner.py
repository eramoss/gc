import subprocess
import sys
from pathlib import Path

test_dir = Path("./tests")

gc_exec = Path("build/gc")
if not gc_exec.exists():
    print("Error: build/gc not found. Please compile your project first.")
    sys.exit(1)

TEST_FILES = list(test_dir.glob("*.gc"))

if not TEST_FILES:
    print("No .gc files found in current directory.")
    sys.exit(0)

for test_file in TEST_FILES:
    expect_file = test_file.with_suffix(".gc.expect")

    print(f"\nRunning {test_file.name}...")

    result = subprocess.run([str(gc_exec), str(test_file)], capture_output=True, text=True)
    output = (result.stdout + result.stderr).strip()

    if not expect_file.exists():
        print(f"No .expect file for {test_file.name}, skipping check.")
        print("--- Program output ---")
        print(output)
        continue

    expected = expect_file.read_text().strip()

    if output == expected:
        print(f"✅ {test_file.name} passed")
    else:
        print(f"❌ {test_file.name} failed")
        print("--- Output ---")
        print(output)
        print("--- Expected ---")
        print(expected)
