include $(ROOTDIR)/src/common.mk

.PHONY: all clean distclean install uninstall

HEADERS = $(ROOTDIR)/src/detail/detail.hh

all:

clean:

distclean: clean

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
ifneq "$(MAKECMDGOALS)" "uninstall"
  -include $(DEPS)
endif
endif
endif

install: all
	install --mode=644 -D --target-directory $(PREFIX)/include/shell_word_split/detail $(HEADERS)

uninstall:
	rm $(foreach H,$(foreach H,$(HEADERS),$(notdir $(H))),$(PREFIX)/include/shell_word_split/detail/$(H))
