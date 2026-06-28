# Building the Transmitter Examples

This folder builds standalone for the Raspberry Pi Pico (RP2040). It produces
four flashable `.uf2` binaries:

- `transmitter_serial_example_mixer.uf2`
- `transmitter_microphone_example_mixer.uf2`
- `transmitter_serial_example_polar_amplifier.uf2`
- `transmitter_microphone_example_polar_amplifier.uf2`

You can build it two ways: with the **VS Code Pico extension** (easiest) or from
the **command line**.

## Prerequisites

The Raspberry Pi Pico SDK and ARM toolchain must be installed under
`~/.pico-sdk/`. The simplest way to get these is to install the
[Raspberry Pi Pico VS Code extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico),
which downloads them automatically. This project was built and tested against:

- Pico SDK `2.2.0`
- ARM GCC toolchain `14_2_Rel1`
- picotool `2.2.0-a4`

If your installed versions differ, adjust the paths in the commands below to match.

## Option A — VS Code Pico extension

1. Open this `18_transmitter` folder in VS Code.
2. When prompted (or via the **Raspberry Pi Pico** sidebar), let the extension
   import the project and configure CMake.
3. Click **Compile** in the status bar / Pico panel.
4. The `.uf2` files appear in the `build/` folder.

To flash, click **Run** with the Pico connected, or copy a `.uf2` onto the
board manually (see [Flashing](#flashing)).

## Option B — Command line

Run these from inside the `18_transmitter` folder.

### 1. Set up your shell (once per terminal session)

```sh
export PICO_SDK_PATH=~/.pico-sdk/sdk/2.2.0
export PATH="$HOME/.pico-sdk/cmake/"*/bin:"$HOME/.pico-sdk/ninja/"*:"$PATH"
```

### 2. Clean (optional)

```sh
rm -rf build
```

### 3. Configure

Only needed the first time, or after a clean:

```sh
cmake -S . -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DPICO_BOARD=pico \
  -DCMAKE_C_COMPILER=$HOME/.pico-sdk/toolchain/14_2_Rel1/bin/arm-none-eabi-gcc \
  -DCMAKE_CXX_COMPILER=$HOME/.pico-sdk/toolchain/14_2_Rel1/bin/arm-none-eabi-g++
```

### 4. Build

```sh
cmake --build build
```

Build a single target instead of all four:

```sh
cmake --build build --target transmitter_serial_example_mixer
```

After a code change, just re-run `cmake --build build` — Ninja recompiles only
what changed, no clean or reconfigure required.

The resulting `.uf2` files are written to `build/`.

## Flashing

**Drag and drop:** Hold the **BOOTSEL** button while plugging the Pico into USB.
It mounts as a drive named `RPI-RP2`. Copy the desired `.uf2` onto it; the board
reboots and runs the program.

**picotool:** With the Pico in BOOTSEL mode:

```sh
~/.pico-sdk/picotool/2.2.0-a4/picotool/picotool load build/transmitter_serial_example_mixer.uf2
```

## Notes

- This folder is part of the larger **101Things** repo. Its `CMakeLists.txt`
  detects whether it is the top-level project (standalone build) or a
  subdirectory of the parent build, and configures the SDK and the local
  `psu_mode` library accordingly — so both build styles work.
- The board defaults to a standard `pico`. To target a different board (e.g.
  `pico_w`), pass `-DPICO_BOARD=pico_w` at the configure step.
