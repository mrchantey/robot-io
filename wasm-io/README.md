# wasm-io

## Setup

1. install wasm compiler `https://github.com/wasm3/wasm3/blob/main/docs/Installation.md`
1. Arduino -> Sketch -> Include Library -> Manage Libraries -> wasm3 -> install
1. `.vscode/c_cpp_properties.json` ensure path links are up to date

## Reference

The build process

1. a file is written in assemblyscript
1. a `binding.ts` file points to exposed c++ functions
1. a `bindings.h` file will match the assemblyscript file
1. 

### Danger Zone

- seems the built in led in nodemcu is inverted, with HIGH=OFF, LOW=ON

### Links
- [wasm3 arduino](https://github.com/wasm3/wasm3-arduino)
- [wasm3 arduino rgb light](https://github.com/vshymanskyy/Wasm3_RGB_Lamp)
- [wasm3 arduino ota upload](https://github.com/alvarowolfx/wasm-arduino-wifi)



## build options
```json
//reccomended
{
  "scripts": {
    "asbuild:debug":        "asc hello.ts -b hello.wasm --debug",
    "asbuild:optimized":    "asc hello.ts -b hello.wasm -O3s --noAssert",
    "asbuild:tiny":         "asc hello.ts -b hello.wasm -O3z --noAssert --runtime stub --use abort=",
    "build":                "npm run asbuild:optimized"
  },
  "devDependencies": {
    "assemblyscript": "*",
    "as-wasi": "*"
  }
}
//blink demo https://github.com/wasm3/wasm3-arduino/blob/main/wasm_apps/assemblyscript/package.json
{
  "license": "MIT",
  "scripts": {
    "build": "npm run asbuild:optimized && xxd -i app.wasm > app.wasm.h",
    "asbuild:optimized": "npx asc app.ts -b app.wasm -t app.wat -O3z --runtime stub --noAssert --use abort="
  },
  "devDependencies": {
    "assemblyscript": "^0.18.0"
  }
}
```