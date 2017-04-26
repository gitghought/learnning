.text
.global _start
_start:
	b RESET
undef_ins:
	b undef_ins

software_int:
	b software_int

abort_pre:
	b abort_pre

abort_data:
	b abort_data

reserve:
	.word 0

irq:
	b irq
fiq:
	b fiq


RESET:
	ldr sp, =4096
	bl disable_watchdog
	bl configClock
	bl configNand
	bl configSDRAM
	@bl stop_here

	ldr r0, =0x30000000
	mov r1, #4096
	mov r2, #4096
	bl chipRead
	@bl main

	ldr sp, =0x34000000
	ldr lr, =stop_here
	ldr pc, =mloop

stop_here:
	b stop_here

cope_to_sdram:
	mov r4, #0
	mov r5, #0x30000000	
	mov r6, #2048
	
copy_loop:
	ldr r7, [r4], #4
	str r7, [r5], #4
	cmp r4, r6
	bne copy_loop
	
	mov pc, lr

config_mem:
	mov r4, #0x48000000
	adrl r5, mem_config_val
	add r6, r5, #52 
1:
	ldr r7, [r5], #4
	str r7, [r4], #4

	cmp r5, r6
	bne 1b

	mov pc, lr

config_led:
	@ config gpfcon
	ldr r4, =0x56000050
	mov r5, #0x1500
	str r5, [r4]
	mov pc, lr
led_on:
	@ 
	ldr r6, =0x56000054
	mov r7, #0x9f
	str r7, [r6]
	mov pc, lr

disable_watch_dog:
	mov r4, #0x53000000		
	mov r5, #0
	str r5, [r4]
	mov pc, lr

.align 4
mem_config_val:
	.long 0x22011110
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00000700
	.long 0x00018005
	.long 0x00018005
	.long 0x008C07A3
	.long 0x000000B1
	.long 0x00000030
	.long 0x00000030


