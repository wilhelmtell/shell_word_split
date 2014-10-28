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
	rm -f $(foreach HEADER,$(patsubst $(ROOTDIR)/include/shell_word_split/%,$(PREFIX)/include/shell_word_split/%, $(HEADERS)),$(HEADER))
	${MAKE} --directory $(CURDIR)/detail uninstall
