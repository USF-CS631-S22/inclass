	.arch armv6
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"ctypes_gen.c"
	.text
	.align	2
	.global	main
	.arch armv6
	.syntax unified
	.arm
	.fpu vfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #44
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	sub	r3, fp, #32
	str	r3, [fp, #-12]
	sub	r3, fp, #33
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-12]
	add	r3, r3, #4
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
	mov	r3, #1
	str	r3, [fp, #-20]
	mov	r3, #2
	str	r3, [fp, #-24]
	mov	r3, #3
	str	r3, [fp, #-8]
	mov	r3, #4
	str	r3, [fp, #-28]
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-24]
	cmp	r2, r3
	ble	.L2
	ldr	r3, [fp, #-20]
	add	r3, r3, #1
	str	r3, [fp, #-20]
.L2:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-28]
	cmp	r2, r3
	bls	.L3
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L3:
	ldr	r3, [fp, #-32]
	asr	r3, r3, #2
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-8]
	lsr	r3, r3, #2
	str	r3, [fp, #-8]
	mov	r3, #0
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	main, .-main
	.ident	"GCC: (Raspbian 10.2.1-6+rpi1) 10.2.1 20210110"
	.section	.note.GNU-stack,"",%progbits
