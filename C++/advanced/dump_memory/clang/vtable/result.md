- asm

``` asm
vtable for SimpleInherit:
        .quad   0
        .quad   typeinfo for SimpleInherit
        .quad   SimpleInherit::foo()

typeinfo name for SimpleInherit:
        .asciz  "13SimpleInherit"

typeinfo name for Base:
        .asciz  "4Base"

typeinfo for Base:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for Base

typeinfo for SimpleInherit:
        .quad   vtable for __cxxabiv1::__si_class_type_info+16
        .quad   typeinfo name for SimpleInherit
        .quad   typeinfo for Base

vtable for Base:
        .quad   0
        .quad   typeinfo for Base
        .quad   __cxa_pure_virtual
```
- gdb in clang

```
-exec x/10ag 0x402018
0x402018 <_ZTV13SimpleInherit+16>:	0x401260 <SimpleInherit::foo()>	0x656c706d69533331
0x402028 <_ZTS13SimpleInherit+8>:	0x74697265686e49	0x6573614234
0x402038 <_ZTI4Base>:	0x403d50 <_ZTVN10__cxxabiv117__class_type_infoE@@CXXABI_1.3+16>	0x402030 <_ZTS4Base>
0x402048 <_ZTI13SimpleInherit>:	0x403da8 <_ZTVN10__cxxabiv120__si_class_type_infoE@@CXXABI_1.3+16>	0x402020 <_ZTS13SimpleInherit>
0x402058 <_ZTI13SimpleInherit+16>:	0x402038 <_ZTI4Base>	0x0

-exec x/10xg 0x402018
0x402018 <_ZTV13SimpleInherit+16>:	0x0000000000401260	0x656c706d69533331
0x402028 <_ZTS13SimpleInherit+8>:	0x0074697265686e49	0x0000006573614234
0x402038 <_ZTI4Base>:	0x0000000000403d50	0x0000000000402030
0x402048 <_ZTI13SimpleInherit>:	0x0000000000403da8	0x0000000000402020
0x402058 <_ZTI13SimpleInherit+16>:	0x0000000000402038	0x0000000000000000

-exec x/1sb 0x402030
0x402030 <_ZTS4Base>:	"4Base"

-exec x/1sb 0x402020
0x402020 <_ZTS13SimpleInherit>:	"13SimpleInherit"
```

- gdb gcc
```
-exec x/10ag 0x8201d60
0x8201d60 <_ZTV13SimpleInherit+16>:	0x8000d6c <SimpleInherit::foo()>	0x0
0x8201d70 <_ZTV4Base+8>:	0x8201d98 <_ZTI4Base>	0x7fffff0c6320 <__cxa_pure_virtual>
0x8201d80 <_ZTI13SimpleInherit>:	0x7fffff3e5c98 <_ZTVN10__cxxabiv120__si_class_type_infoE+16>	0x8000eb0 <_ZTS13SimpleInherit>
0x8201d90 <_ZTI13SimpleInherit+16>:	0x8201d98 <_ZTI4Base>	0x7fffff3e5008 <_ZTVN10__cxxabiv117__class_type_infoE+16>
0x8201da0 <_ZTI4Base+8>:	0x8000ec0 <_ZTS4Base>	0x1

-exec x/2sg 0x8000eb0
warning: Unable to display strings with size 'g', using 'b' instead.
0x8000eb0 <_ZTS13SimpleInherit>:	"13SimpleInherit"
0x8000ec0 <_ZTS4Base>:	"4Base"
```

~ 看起来内存里倒是像汇编代码倒过来的. ~