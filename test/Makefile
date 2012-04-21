include $(ROOTDIR)/test/common.mk

OBJ = $(CURDIR)/main.o
DEPS = $(OBJ:.o=.dep)

.PHONY: check clean distclean tests

check:
	./test_shell_word_split

clean:
	rm -f $(OBJ) $(DEPS)

distclean: clean
	rm -f test_shell_word_split

test_shell_word_split: $(OBJ)
	$(LINK.cc) $(OUTPUT_OPTION) $^

%.dep: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cc=.o)" "$<"

ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "distclean"
  -include $(DEPS)
endif
endif

tests: test_shell_word_split
