# Copyright (C) 2023 Advanced Micro Devices, Inc
#
# SPDX-License-Identifier: MIT

PLATFORM := xilinx_vck5000_gen4x8_qdma_2_202220_1
TARGET := hw
FREQ := 250

XSA = $(strip $(patsubst %.xpfm, % , $(shell basename $(PLATFORM))))

BUILD_DIR = build.$(TARGET)
VPP_FLAGS = -t $(TARGET) --platform $(PLATFORM)# --save-temps
VPP_FLAGS += --kernel_frequency $(FREQ)

TARGETS = sticker_s2mm tile_mm2s
all: $(addprefix $(BUILD_DIR)/, $(addsuffix .xo,$(TARGETS)))

$(BUILD_DIR)/%.xo: src/%.cpp
	v++ $(VPP_FLAGS) -k $* -c -g -o $@ $^

clean:
	rm -rf $(BUILD_DIR) *.log *.jou .Xil/ _x/
