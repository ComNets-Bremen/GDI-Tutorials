SCHEMATIC_DIRS = $(dir $(wildcard */schematic.fzz))
SCHEMATIC_SVG = $(patsubst %/, %.svg, $(SCHEMATIC_DIRS))

.PHONY: all
all: $(SCHEMATIC_SVG)

%.svg: %/schematic.fzz
	Fritzing -svg $*
	cp $*/schematic_breadboard.svg $*.svg
