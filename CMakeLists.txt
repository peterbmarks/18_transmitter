# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# When this folder is opened on its own (e.g. by the Raspberry Pi Pico VS Code
# extension) it is the top-level CMake project, so we must pull in the SDK
# ourselves. When built as part of the parent 101Things project, the parent
# already does this, so we skip it to avoid redefinitions.
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.13)
  include(pico_sdk_import.cmake)
  project(transmitter C CXX ASM)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)
  pico_sdk_init()
endif()

# Build psu_mode from the local copy so this folder is self-contained. When
# built as part of the parent repo, the parent's Library defines this target
# already, so only define it here if it doesn't exist yet.
if (NOT TARGET psu_mode)
  add_library(psu_mode psu_mode.cpp)
  target_include_directories(psu_mode PUBLIC ${CMAKE_CURRENT_LIST_DIR})
  if (PICO_CYW43_SUPPORTED)
    target_link_libraries(psu_mode pico_stdlib pico_cyw43_arch_lwip_poll)
  else()
    target_link_libraries(psu_mode pico_stdlib)
  endif()
endif()


add_executable(transmitter_serial_example_mixer
  transmitter_serial_example.cpp
  transmit.cpp
  modulator.cpp
  adc.cpp
  nco.cpp
  pwm.cpp
  signal_generator.cpp
  half_band_filter.cpp
  half_band_filter2.cpp
  cordic.cpp
)

target_compile_definitions(transmitter_serial_example_mixer PUBLIC BALANCED)
pico_generate_pio_header(transmitter_serial_example_mixer ${CMAKE_CURRENT_LIST_DIR}/stream_bits.pio)
pico_enable_stdio_usb(transmitter_serial_example_mixer 1)
pico_enable_stdio_uart(transmitter_serial_example_mixer 0)
pico_add_extra_outputs(transmitter_serial_example_mixer)
target_include_directories(transmitter_serial_example_mixer PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(transmitter_serial_example_mixer psu_mode pico_stdlib hardware_pio hardware_dma hardware_pwm hardware_adc)

add_executable(transmitter_microphone_example_mixer
  transmitter_microphone_example.cpp
  transmit.cpp
  modulator.cpp
  adc.cpp
  nco.cpp
  pwm.cpp
  signal_generator.cpp
  half_band_filter.cpp
  half_band_filter2.cpp
  cordic.cpp
)

target_compile_definitions(transmitter_microphone_example_mixer PUBLIC BALANCED)
pico_generate_pio_header(transmitter_microphone_example_mixer ${CMAKE_CURRENT_LIST_DIR}/stream_bits.pio)
pico_enable_stdio_usb(transmitter_microphone_example_mixer 1)
pico_enable_stdio_uart(transmitter_microphone_example_mixer 0)
pico_add_extra_outputs(transmitter_microphone_example_mixer)
target_include_directories(transmitter_microphone_example_mixer PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(transmitter_microphone_example_mixer psu_mode pico_stdlib hardware_pio hardware_dma hardware_pwm hardware_adc)

add_executable(transmitter_serial_example_polar_amplifier
  transmitter_serial_example.cpp
  transmit.cpp
  modulator.cpp
  adc.cpp
  nco.cpp
  pwm.cpp
  signal_generator.cpp
  half_band_filter.cpp
  half_band_filter2.cpp
  cordic.cpp
)

pico_generate_pio_header(transmitter_serial_example_polar_amplifier ${CMAKE_CURRENT_LIST_DIR}/stream_bits.pio)
pico_enable_stdio_usb(transmitter_serial_example_polar_amplifier 1)
pico_enable_stdio_uart(transmitter_serial_example_polar_amplifier 0)
pico_add_extra_outputs(transmitter_serial_example_polar_amplifier)
target_include_directories(transmitter_serial_example_polar_amplifier PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(transmitter_serial_example_polar_amplifier psu_mode pico_stdlib hardware_pio hardware_dma hardware_pwm hardware_adc)

add_executable(transmitter_microphone_example_polar_amplifier
  transmit.cpp
  transmitter_microphone_example.cpp
  modulator.cpp
  adc.cpp
  nco.cpp
  pwm.cpp
  signal_generator.cpp
  half_band_filter.cpp
  half_band_filter2.cpp
  cordic.cpp
)

pico_generate_pio_header(transmitter_microphone_example_polar_amplifier ${CMAKE_CURRENT_LIST_DIR}/stream_bits.pio)
pico_enable_stdio_usb(transmitter_microphone_example_polar_amplifier 1)
pico_enable_stdio_uart(transmitter_microphone_example_polar_amplifier 0)
pico_add_extra_outputs(transmitter_microphone_example_polar_amplifier)
target_include_directories(transmitter_microphone_example_polar_amplifier PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(transmitter_microphone_example_polar_amplifier psu_mode pico_stdlib hardware_pio hardware_dma hardware_pwm hardware_adc)
