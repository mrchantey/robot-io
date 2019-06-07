This is the code used by droid.io.

It is a series of bytes, and has a tree structure.
Messages are directed to branches depending on their code.





```
droid.io message code:

max buffer size : 1024 bytes
max message size : 64 bytes
all int values are encoded as 'little endian'

i -> 32 bit integer
f -> 32 bit float


69 -> droid.io message
|
|___69.0 <-> 69.15 -> network command
|   |
|   |___69.0.b*4.i*1 -> poke (ip*4,port)
|   |___69.1.b*4.i*1 -> poke reply (ip*4,port)
|
|___69.16 <-> 69.31 -> hardware command
|   |
|   |___69.16 <-> 69.24 -> display commands
|   |   |___69.16... -> print utf-8 message
|   |   |___69.17.i*4 -> set led for hh,mm,ss,ms
|   |
|   |___69.24 <-> 69.32 -> motor commands (ran)
|   |   |___69.24.f*2 -> set left and right motors
|   |   |___69.25.f*1 -> set left motor
|   |   |___69.26.f*1 -> set right motor
|   |   |___69.27.f*1 -> set aux motor 1
|   |   |___69.28.f*1 -> set aux motor 2
