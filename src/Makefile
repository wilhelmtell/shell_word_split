include $(ROOTDIR)/src/common.mk

.PHONY: all clean distclean install uninstall

HEADERS = $(ROOTDIR)/src/shell_word_split.hh \
          $(ROOTDIR)/src/error.hh

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
	${MAKE} --directory $(CURDIR)/detail install
	install --mode=644 -D --target-directory $(PREFIX)/include/shell_word_split $(HEADERS)

uninstall:
	rm -f $(foreach H,$(foreach H,$(HEADERS),$(notdir $(H))),$(PREFIX)/include/shell_word_split/$(H))
	${MAKE} --directory $(CURDIR)/detail uninstall
	rmdir -p $(PREFIX)/include/shell_word_split/detail 2>/dev/null || true
