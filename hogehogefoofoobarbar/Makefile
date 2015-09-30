#GCC_BIN = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/
GCC_BIN = /Users/user/Documents/arm-none-eabi-gcc/bin/
OBJDIR = Builds
SOURCES = $(shell find -E . -regex '^.*\.(c(pp)?|[sS])$$' | sed -E -e 's/\.(c(pp)?|[sS])$$/.o/g')
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(filter-out $(PROJECT).o,$(SOURCES)))
CORE_SOURCES = $(shell find -E /Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple -regex '^.*\.(c(pp)?|[sS])$$' | sed -E -e 's/\.(c(pp)?|[sS])$$/.o/g')
CORE_OBJECTS = $(patsubst /Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple/%,libmaple/%,$(filter-out $(PROJECT).o,$(CORE_SOURCES)))
SYS_OBJECTS = $(shell find -E . -regex '^.*\.o$$' | sed -e 's/^.\/Builds\/.*$$//g')
INCLUDE_PATHS = -I. $(shell find -E . -regex '^.*\.h$$' | sed -e 's/^\(.*\)\/[^\/]*$$/-I\1/g' | sort | uniq)
LIBRARY_PATHS = -L/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple $(shell find -E . -regex '^.*\.a$$' | sed -e 's/^\(.*\)\/[^\/]*$$/-L\1/g' | sort | uniq)
LIBRARIES = -lmaple
# LINKER_SCRIPT = -T/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple/maple_mini/flash.ld $(shell find -E . -regex '^.*\.ld$$')
LINKER_SCRIPT = -T/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple/maple_mini/flash.ld

###############################################################################
AR      = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-ar
AS      = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-gcc
CC      = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-g++
OBJCOPY = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-objcopy
OBJDUMP = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-objdump
SIZE 	= /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/arm-none-eabi-size
DFU     = /Applications/MapleIDE.app/Contents/Resources/Java/hardware/tools/arm/bin/dfu-util

CPU = -c -mcpu=cortex-m3 -march=armv7-m -mthumb -DBOARD_maple_mini -DMCU_STM32F103CB -DSTM32_MEDIUM_DENSITY -DERROR_LED_PORT=GPIOB -DERROR_LED_PIN=1 -DMAPLE_IDE
CC_FLAGS = $(CPU) -DVECT_TAB_FLASH -DARDUINO=18 -I/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple -nostdlib -ffunction-sections -fdata-sections -Wl,--gc-sections -Wall

CXX_FLAGS = -std=gnu++14 -fno-rtti -fno-exceptions

LD_FLAGS = -mcpu=cortex-m3 -mthumb -Xlinker --gc-sections --print-gc-sections --march=armv7-m -Wall

BOARD_USB_VENDOR_ID  := 1EAF
BOARD_USB_PRODUCT_ID := 0003

ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif

ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

createObjDir:
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

all: allclean build upload

build: createObjDir $(OBJDIR)/$(PROJECT).bin

upload:
	@echo "Upload"
	./reset.py && \
	sleep 1 && \
	$(DFU) -a1 -R -d $(BOARD_USB_VENDOR_ID):$(BOARD_USB_PRODUCT_ID) -D $(OBJDIR)/$(PROJECT).bin

buildAndUpload: build upload

cleanLibMaple:
	@if [ -d libmaple ]; then rm -rf libmaple; fi

clean:
	@if [ -d $(OBJDIR) ]; then rm -rf $(OBJDIR); fi

allclean: clean cleanLibMaple

$(OBJDIR)/%.o: 	%.s
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(CPU) -x assembler-with-cpp -o $@ $<

libmaple/%.o: 	/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple/%.S
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(CPU) -x assembler-with-cpp -o $@ $<

$(OBJDIR)/%.o: 	%.S
	@echo "Assemble $<"
	@mkdir -p $(dir $@)
	$(AS) $(CPU) -x assembler-with-cpp -o $@ $<

libmaple/%.o: 	/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple/%.c
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CC)  $(CC_FLAGS) -std=gnu99 $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.o: 	%.c
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CC)  $(CC_FLAGS) -std=gnu99 $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.d: %.c
	@echo "Generate dependency of $<"
	@mkdir -p $(dir $@)
	$(CC) -MM $(CC_FLAGS) -std=gnu99 $(INCLUDE_PATHS) $< -MF $@ -MT $(@:.d=.o)

libmaple/%.o: 	/Applications/MapleIDE.app/Contents/Resources/Java/hardware/leaflabs/cores/maple/%.cpp
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CPP) $(CC_FLAGS) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.o: %.cpp
	@echo "Compile $<"
	@mkdir -p $(dir $@)
	$(CPP) $(CC_FLAGS) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.d: %.cpp
	@echo "Generate dependency of $<"
	@mkdir -p $(dir $@)
	$(CPP) -MM $(CC_FLAGS) $(INCLUDE_PATHS) $< -MF $@ -MT $(@:.d=.o)

libmaple/libmaple.a: $(CORE_OBJECTS)
	$(AR) -r $@ $^

$(OBJDIR)/$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS) libmaple/libmaple.a
	@echo Link
	$(LD) $(LD_FLAGS) $(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LIBRARIES)
	$(SIZE) $@

$(OBJDIR)/$(PROJECT).bin: $(OBJDIR)/$(PROJECT).elf
	@echo Copy
	$(OBJCOPY) -v -Obinary $< $@
