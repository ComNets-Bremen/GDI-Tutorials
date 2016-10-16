MD_FILES := $(wildcard ../src/*.md)
HTML_FILES := $(subst ../src/, , $(patsubst %.md, %.html, $(MD_FILES)))

THEME_DIR= ../theme/boring
SLIDE_COMPILER= landslide

.PHONY: all
all: $(HTML_FILES)

%.html: ../src/%.md
	$(SLIDE_COMPILER) -c -d $(@) -r -t $(THEME_DIR) $(<)

