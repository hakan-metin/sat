
sources := $(wildcard $(SRC)core/*.cc)
headers_dir = include/
headers := $(wildcard $(headers_dir)dsb/*.h)

$(info $(sources))

objects         := $(patsubst %.cc, $(OBJ)%.o, $(sources))
release_objects := $(patsubst %.cc, $(OBJ)release/%.o, $(sources))
debug_objects   := $(patsubst %.cc, $(OBJ)debug/%.o, $(sources))

tests := $(wildcard tests/units/*.test.cc)
tests_objects := $(patsubst %.cc, $(OBJ)%.o, $(tests))
tests_objects += $(objects)
tests_objects := $(filter-out %sat_solver.o, $(tests_objects))

exec  := sat_solver

$(call REQUIRE-DIR, $(objects))
$(call REQUIRE-DIR, $(BIN)$(exec))

$(call REQUIRE-DIR, $(release_objects))
$(call REQUIRE-DIR, $(BIN)$(exec)_release)

$(call REQUIRE-DIR, $(debug_objects))
$(call REQUIRE-DIR, $(BIN)$(exec)_debug)

$(call REQUIRE-DIR, $(tests_objects))
$(call REQUIRE-DIR,  $(BIN)test)

$(call REQUIRE-DEP, $(sources))

$(BIN)$(exec): $(objects)
$(BIN)$(exec)_release: $(release_objects)
$(BIN)$(exec)_debug: $(debug_objects)


CFLAGS += -I$(SRC)

default: CFLAGS += -O3 -fPIC -Wall -Wextra
default: $(BIN)$(exec)

release: CFLAGS += -O3 -fPIC -Wall -Wextra -D NDEBUG
release: $(BIN)$(exec)_release

debug: CFLAGS += -O0 -fPIC -Wall -Wextra -g 
debug: $(BIN)$(exec)_debug


################################################################################
# TESTS

LIB_DIR = third_party/googletest/googletest/build/

CFLAGS_TEST = $(CFLAGS) -I third_party/googletest/googletest/include/
LDFLAGS_TEST = $(LDFLAGS) -L $(LIB_DIR) -lgtest -lgtest_main -lpthread

test: third_party $(BIN)test
run-test: test
	./$(BIN)test
run-test-valgrind: test
	valgrind --leak-check=full ./$(BIN)test
run-test-gdb: test
	gdb --args ./$(BIN)test


check-style: $(sources) $(headers)
	python ./scripts/cpplint.py $^

# Special build
third_party: $(LIB_DIR)libgtest.a
	$(call cmd-call, scripts/build_googletest.sh)
.PHONY: third_party

$(LIB_DIR)libgtest.a:
	./scripts/build_googletest.sh


# Generic rules

$(BIN)$(exec): $(objects)
	$(call cmd-ld, $@, $^)

$(BIN)$(exec)_release: $(release_objects)
	$(call cmd-ld, $@, $^)

$(BIN)$(exec)_debug: $(debug_objects)
	$(call cmd-ld, $@, $^)

$(BIN)test: $(tests_objects)
	$(call cmd-ld, $@, $^, $(LDFLAGS_TEST))

$(OBJ)release/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))

$(OBJ)debug/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))
