#include <wasm3.h>

#include <m3_api_defs.h>
#include <m3_env.h>

// Redefine the default LED pin here, if needed
#ifndef LED_PIN
#define LED_PIN LED_BUILTIN
#endif

#define WASM_STACK_SLOTS 1024
#define NATIVE_STACK_SIZE (32 * 1024)

// For (most) devices that cannot allocate a 64KiB wasm page
#define WASM_MEMORY_LIMIT 4096
