
target:=clock
version :=#_v2
elf:=$(target)$(version)_elf
dis:=$(target)$(version).dis
bin:=$(target).bin
asm:=$(target).asm

asm_src := $(target)$(version).S
asm_dst :=  $(target)$(version).o


led_objs := b_led.o
watchdog_objs := a_watch_dog.o
sdram_objs := c_sdram.o
nand_objs := d_nand.o
asm_objs := $(target)$(version).o
clock_objs := e_clock.o
main_objs := x_main.o

objs := $(asm_objs) $(led_objs) $(watchdog_objs) $(sdram_objs)  $(nand_objs) $(main_objs) $(clock_objs)

$(target).bin:$(elf)
	arm-linux-objcopy -O binary -S $^ $@ 

$(elf):$(objs)
	arm-linux-ld -T$(target)$(version).lds -o $@ $^

$(asm_dst):$(asm_src)
	arm-linux-gcc -c -o $@ $<

%.o:%.c
	arm-linux-gcc -c -o $@ $<

d:
	arm-linux-objdump -D -m arm  $(elf) > $(dis)

clean:
	@rm -rf $(objs)
	@rm -rf $(elf)
	@rm -rf $(target)
	@rm -rf $(bin)
	@rm -rf $(dis)
	@rm -rf $(asm_objs)

y:
	@ctags -R .
	@ls

