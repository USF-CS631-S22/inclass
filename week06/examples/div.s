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
	.file	"div.c"
	.text
	.global	__aeabi_idiv
	.align	2
	.global	main
	.arch armv6
	.syntax unified
	.arm
	.fpu vfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	ldr	r3, [fp, #-28]
	add	r3, r3, #4
	ldr	r3, [r3]
	mov	r0, r3
	bl	atoi
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-28]
	add	r3, r3, #8
	ldr	r3, [r3]
	mov	r0, r3
	bl	atoi
	str	r0, [fp, #-12]
	ldr	r1, [fp, #-12]
	ldr	r0, [fp, #-8]
	bl	__aeabi_idiv
	mov	r3, r0
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-16]
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	main, .-main
	.ident	"GCC: (Raspbian 10.2.1-6+rpi1) 10.2.1 20210110"
	.section	.note.GNU-stack,"",%progbits
