/*
 * API bindings
 *
 * Note: each RawFunction should complete with one of these calls:
 *   m3ApiReturn(val)   - Returns a value
 *   m3ApiSuccess()     - Returns void (and no traps)
 *   m3ApiTrap(trap)    - Returns a trap
 */

m3ApiRawFunction(m3_binding_millis)
{
    m3ApiReturnType(uint32_t)

        m3ApiReturn(millis());
}

m3ApiRawFunction(m3_binding_delay)
{
    m3ApiGetArg(uint32_t, ms)

        // You can also trace API calls
        //Serial.print("api: delay "); Serial.println(ms);

        delay(ms);

    m3ApiSuccess();
}

// This maps pin modes from arduino_wasm_api.h
// to actual platform-specific values
uint8_t mapPinMode(uint8_t mode)
{
    switch (mode)
    {
    case 0:
        return INPUT;
    case 1:
        return OUTPUT;
    case 2:
        return INPUT_PULLUP;
    }
    return INPUT;
}

m3ApiRawFunction(m3_binding_pinMode)
{
    m3ApiGetArg(uint32_t, pin)
        m3ApiGetArg(uint32_t, mode)

#if !defined(PARTICLE)
            typedef uint8_t PinMode;
#endif
    pinMode(pin, (PinMode)mapPinMode(mode));

    m3ApiSuccess();
}

m3ApiRawFunction(m3_binding_digitalWrite)
{
    m3ApiGetArg(uint32_t, pin)
        m3ApiGetArg(uint32_t, value)
            digitalWrite(pin, value);
    m3ApiSuccess();
}

m3ApiRawFunction(m3_binding_getPinLED)
{
    m3ApiReturnType(uint32_t)
        m3ApiReturn(LED_PIN);
}

m3ApiRawFunction(m3_binding_print)
{
    m3ApiGetArgMem(const uint8_t *, buf)
        m3ApiGetArg(uint32_t, len)
            Serial.write(buf, len);
    m3ApiSuccess();
}

M3Result LinkArduino(IM3Runtime runtime)
{
    IM3Module module = runtime->modules;
    //this should match the file name, ie `src-ts/coreBinding.ts` maps to `coreBinding`
    const char *bindingName = "coreBinding";

    m3_LinkRawFunction(module, bindingName, "millis", "i()", &m3_binding_millis);
    m3_LinkRawFunction(module, bindingName, "delay", "v(i)", &m3_binding_delay);
    m3_LinkRawFunction(module, bindingName, "pinMode", "v(ii)", &m3_binding_pinMode);
    m3_LinkRawFunction(module, bindingName, "digitalWrite", "v(ii)", &m3_binding_digitalWrite);

    // Test functions
    m3_LinkRawFunction(module, bindingName, "getPinLED", "i()", &m3_binding_getPinLED);
    m3_LinkRawFunction(module, bindingName, "print", "v(*i)", &m3_binding_print);

    return m3Err_none;
}