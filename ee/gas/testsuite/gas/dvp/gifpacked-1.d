#as:
#objdump: -dr
#name: gifpacked-1

.*: +file format .*

Disassembly of section .vutext:

0+0000 <foo>:
   0:	00 00 00 00 	gifpacked regs={prim},nloop=0
   4:	00 00 00 10 
   8:	00 00 00 00 
   c:	00 00 00 00 

0+0010 .*:
  10:	00 00 00 00 	gifpacked regs={rgbaq},nloop=0
  14:	00 00 00 10 
  18:	01 00 00 00 
  1c:	00 00 00 00 

0+0020 .*:
  20:	00 00 00 00 	gifpacked regs={st},nloop=0
  24:	00 00 00 10 
  28:	02 00 00 00 
  2c:	00 00 00 00 

0+0030 .*:
  30:	00 00 00 00 	gifpacked regs={uv},nloop=0
  34:	00 00 00 10 
  38:	03 00 00 00 
  3c:	00 00 00 00 

0+0040 .*:
  40:	00 00 00 00 	gifpacked regs={xyzf2},nloop=0
  44:	00 00 00 10 
  48:	04 00 00 00 
  4c:	00 00 00 00 

0+0050 .*:
  50:	00 00 00 00 	gifpacked regs={xyz2},nloop=0
  54:	00 00 00 10 
  58:	05 00 00 00 
  5c:	00 00 00 00 

0+0060 .*:
  60:	00 00 00 00 	gifpacked regs={tex0_1},nloop=0
  64:	00 00 00 10 
  68:	06 00 00 00 
  6c:	00 00 00 00 

0+0070 .*:
  70:	00 00 00 00 	gifpacked regs={tex0_2},nloop=0
  74:	00 00 00 10 
  78:	07 00 00 00 
  7c:	00 00 00 00 

0+0080 .*:
  80:	00 00 00 00 	gifpacked regs={clamp_1},nloop=0
  84:	00 00 00 10 
  88:	08 00 00 00 
  8c:	00 00 00 00 

0+0090 .*:
  90:	00 00 00 00 	gifpacked regs={clamp_2},nloop=0
  94:	00 00 00 10 
  98:	09 00 00 00 
  9c:	00 00 00 00 

0+00a0 .*:
  a0:	00 00 00 00 	gifpacked regs={xyzf},nloop=0
  a4:	00 00 00 10 
  a8:	0a 00 00 00 
  ac:	00 00 00 00 

0+00b0 .*:
  b0:	00 00 00 00 	gifpacked regs={xyzf3},nloop=0
  b4:	00 00 00 10 
  b8:	0c 00 00 00 
  bc:	00 00 00 00 

0+00c0 .*:
  c0:	00 00 00 00 	gifpacked regs={xyz3},nloop=0
  c4:	00 00 00 10 
  c8:	0d 00 00 00 
  cc:	00 00 00 00 

0+00d0 .*:
  d0:	00 00 00 00 	gifpacked regs={a_d},nloop=0
  d4:	00 00 00 10 
  d8:	0e 00 00 00 
  dc:	00 00 00 00 

0+00e0 .*:
  e0:	00 00 00 00 	gifpacked regs={nop},nloop=0
  e4:	00 00 00 10 
  e8:	0f 00 00 00 
  ec:	00 00 00 00 

0+00f0 .*:
  f0:	00 00 00 00 	gifpacked regs={xyzf,xyzf3,xyz3},nloop=0
  f4:	00 00 00 30 
  f8:	ca 0d 00 00 
  fc:	00 00 00 00 

0+0100 .*:
 100:	03 00 00 00 	gifpacked regs={xyzf,xyzf3,xyz3},nloop=3
 104:	00 00 00 30 
 108:	ca 0d 00 00 
 10c:	00 00 00 00 
 110:	00 00 0a 00 
 114:	00 00 00 00 
 118:	4c 00 00 00 
 11c:	00 00 00 00 
 120:	00 00 0a 00 
 124:	00 00 00 00 
 128:	4c 00 00 00 
 12c:	00 00 00 00 
 130:	00 00 0a 00 
 134:	00 00 00 00 
 138:	4c 00 00 00 
 13c:	00 00 00 00 
 140:	00 00 0a 00 
 144:	00 00 00 00 
 148:	4c 00 00 00 
 14c:	00 00 00 00 
 150:	00 00 0a 00 
 154:	00 00 00 00 
 158:	4c 00 00 00 
 15c:	00 00 00 00 
 160:	00 00 0a 00 
 164:	00 00 00 00 
 168:	4c 00 00 00 
 16c:	00 00 00 00 
 170:	00 00 0a 00 
 174:	00 00 00 00 
 178:	4c 00 00 00 
 17c:	00 00 00 00 
 180:	00 00 0a 00 
 184:	00 00 00 00 
 188:	4c 00 00 00 
 18c:	00 00 00 00 
 190:	00 00 0a 00 
 194:	00 00 00 00 
 198:	4c 00 00 00 
 19c:	00 00 00 00 

0+01a0 .*:
 1a0:	01 00 00 00 	gifpacked prim=0x42,regs={a_d},nloop=1
 1a4:	00 40 21 10 
 1a8:	0e 00 00 00 
 1ac:	00 00 00 00 
 1b0:	00 00 0a 00 
 1b4:	00 00 00 00 
 1b8:	4c 00 00 00 
 1bc:	00 00 00 00 

0+01c0 .*:
 1c0:	01 80 00 00 	gifpacked prim=0x42,regs={a_d},nloop=1,eop
 1c4:	00 40 21 10 
 1c8:	0e 00 00 00 
 1cc:	00 00 00 00 
 1d0:	00 00 0a 00 
 1d4:	00 00 00 00 
 1d8:	4c 00 00 00 
 1dc:	00 00 00 00 

0+01e0 .*:
 1e0:	01 80 00 00 	gifpacked prim=0x42,regs={a_d},nloop=1,eop
 1e4:	00 40 21 10 
 1e8:	0e 00 00 00 
 1ec:	00 00 00 00 
 1f0:	00 00 0a 00 
 1f4:	00 00 00 00 
 1f8:	4c 00 00 00 
 1fc:	00 00 00 00 

0+0200 .*:
 200:	01 00 00 00 	gifpacked prim=0x42,regs={a_d},nloop=1
 204:	00 40 21 10 
 208:	0e 00 00 00 
 20c:	00 00 00 00 
 210:	00 00 0a 00 
 214:	00 00 00 00 
 218:	4c 00 00 00 
 21c:	00 00 00 00 

0+0220 .*:
 220:	01 00 00 00 	gifpacked regs={a_d},nloop=1
 224:	00 00 00 10 
 228:	0e 00 00 00 
 22c:	00 00 00 00 
 230:	00 00 0a 00 
 234:	00 00 00 00 
 238:	4c 00 00 00 
 23c:	00 00 00 00 

0+0240 .*:
 240:	00 80 00 00 	gifpacked regs={},nloop=0,eop
 244:	00 00 00 00 
 248:	00 00 00 00 
 24c:	00 00 00 00 

0+0250 .*:
 250:	00 80 00 00 	gifpacked regs={},nloop=0,eop
 254:	00 00 00 00 
 258:	00 00 00 00 
 25c:	00 00 00 00 
