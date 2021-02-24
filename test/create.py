m = bytearray([0 for x in range(65536)])


program =bytearray([
    0xB9, 0x90, 0x36,
])

o = [0x80, 0x00]
origin = 0x8000

m[0xFFFC] = o[1]
m[0xFFFD] = o[0]

m[0x0020] = 0x90
m[0x0021] = 0x36

m[0x3692] = 0xED

for i in range(len(program)):
     m[i+origin] = program[i]

with open("testprogram", "wb") as f:
    f.write(m)