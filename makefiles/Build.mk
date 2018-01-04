THIRD_PARTY = third_party/

GTEST_DIR   = $(THIRD_PARTY)gtest/googletest/
GLOG_DIR    = $(THIRD_PARTY)glog/
GFLAGS_DIR  = $(THIRD_PARTY)gflags/build/

export LIBRARY_PATH=${GTEST_DIR}:${GLOG_DIR}lib
export LD_LIBRARY_PATH=${GTEST_DIR}:${GLOG_DIR}lib

exec  := sat_runner

sources := $(wildcard $(SRC)core/*.cc)
objects         := $(patsubst %.cc, $(OBJ)%.o, $(sources))
release_objects := $(patsubst %.cc, $(OBJ)release/%.o, $(sources))
debug_objects   := $(patsubst %.cc, $(OBJ)debug/%.o, $(sources))

tests := $(wildcard tests/units/*.test.cc)
tests_objects := $(patsubst %.cc, $(OBJ)%.o, $(tests))
tests_objects += $(debug_objects)
tests_objects := $(filter-out %$(exec).o, $(tests_objects))

$(call REQUIRE-DIR, $(objects))
$(call REQUIRE-DIR, $(BIN)$(exec))

$(call REQUIRE-DIR, $(release_objects))
$(call REQUIRE-DIR, $(BIN)$(exec)_release)

$(call REQUIRE-DIR, $(debug_objects))
$(call REQUIRE-DIR, $(BIN)$(exec)_debug)

$(call REQUIRE-DIR, $(tests_objects))
$(call REQUIRE-DIR, $(BIN)test)

$(call REQUIRE-DEP, $(sources))
$(call REQUIRE-DEP, $(tests))


$(BIN)$(exec): $(objects)
$(BIN)$(exec)_release: $(release_objects)
$(BIN)$(exec)_debug: $(debug_objects)

CFLAGS += -I$(SRC) -I$(GLOG_DIR)include/ -I$(GFLAGS_DIR)include
LDFLAGS += -L$(GLOG_DIR)lib/ -L$(GFLAGS_DIR)lib/ -lglog -lgflags

third_party: glog gtest gflags

default: CFLAGS += -O3 -fPIC -Wall -Wextra
default: $(BIN)$(exec)

release: CFLAGS += -O3 -fPIC -Wall -Wextra -D NDEBUG
release: $(BIN)$(exec)_release

debug: CFLAGS += -O0 -fPIC -Wall -Wextra -g  -D DEBUG
debug: $(BIN)$(exec)_debug

glog:   $(GLOG_DIR)libglog.a
gtest:  $(GTEST_DIR)libgtest.a
gflags: $(GFLAGS_DIR)lib/libgflags.a

.PHONY: glog gtest


################################################################################
# TESTS

test: CFLAGS += -isystem ${GTEST_DIR}/include -O0 --coverage -fPIC
test: LDFLAGS += -lgtest -lgtest_main -lpthread -lgcov
test: $(BIN)test
run-test: test
	$(call 	cmd-call, ./$(BIN)test)
run-test-valgrind: test
	$(call 	cmd-call, valgrind --leak-check=full ./$(BIN)test)
run-test-gdb: test
	$(call 	cmd-call, gdb --args ./$(BIN)test)

################################################################################


check-style: $(sources) $(headers)
	python ./scripts/cpplint.py $^

# Special build
$(GTEST_DIR)libgtest.a:
	$(call cmd-call, scripts/build_gtest.sh)

$(GLOG_DIR)libglog.a:
	$(call cmd-call, scripts/build_glog.sh)

$(GFLAGS_DIR)lib/libgflags.a:
	$(call cmd-call, scripts/build_gflags.sh)

# Generic rules

$(BIN)$(exec): $(objects)
	$(call cmd-ld, $@, $^)

$(BIN)$(exec)_release: $(release_objects)
	$(call cmd-ld, $@, $^)

$(BIN)$(exec)_debug: $(debug_objects)
	$(call cmd-ld, $@, $^)


$(OBJ)%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))

$(OBJ)release/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))

$(OBJ)debug/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))

##

$(OBJ)%.test.o: %.test.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))

$(BIN)test: $(tests_objects)
	$(call cmd-ld, $@, $^, $(LDFLAGS))
