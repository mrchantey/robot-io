(module
 (type $none_=>_none (func))
 (type $i32_i32_=>_none (func (param i32 i32)))
 (type $none_=>_i32 (func (result i32)))
 (import "coreBinding" "getPinLED" (func $src-ts/coreBinding/getPinLED (result i32)))
 (import "coreBinding" "pinMode" (func $src-ts/coreBinding/pinMode (param i32 i32)))
 (import "coreBinding" "digitalWrite" (func $src-ts/coreBinding/digitalWrite (param i32 i32)))
 (global $src-ts/app/LED (mut i32) (i32.const 0))
 (memory $0 0)
 (export "_start" (func $src-ts/app/_start))
 (export "memory" (memory $0))
 (start $~start)
 (func $src-ts/app/_start
  global.get $src-ts/app/LED
  i32.const 1
  call $src-ts/coreBinding/pinMode
  loop $while-continue|0
   global.get $src-ts/app/LED
   i32.const 0
   call $src-ts/coreBinding/digitalWrite
   br $while-continue|0
  end
  unreachable
 )
 (func $~start
  call $src-ts/coreBinding/getPinLED
  global.set $src-ts/app/LED
 )
)
