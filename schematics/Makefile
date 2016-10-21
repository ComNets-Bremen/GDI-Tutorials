SCHEMATIC_DIRS = $(dir $(wildcard */schematic.fzz))
SCHEMATIC_SVG = $(addprefix ../target/schematic/, $(patsubst %/, %.svg, $(SCHEMATIC_DIRS)))

.PHONY: all
all: $(SCHEMATIC_SVG)

../target/schematic/%.svg: %/schematic.fzz
	Fritzing -svg $*
	cp $*/schematic_breadboard.svg $@
