SECTIONS {
	first 0x00000000 : { clock.o a_watch_dog.o c_sdram.o d_nand.o e_clock.o }
	second 0x30000000 : AT(4096) {   b_led.o}
}
