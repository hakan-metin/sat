
THIRD_PARTY = third_party/

GTEST_DIR  = $(THIRD_PARTY)gtest/googletest/build/
GLOG_DIR   = $(THIRD_PARTY)glog/
GFLAGS_DIR = $(THIRD_PARTY)gflags/build/

exec  := sat_runner

sources := $(wildcard $(SRC)core/*.cc \
		      $(SRC)util/*.cc)
headers := $(wildcard $(SRC)core/*.h \
		      $(SRC)util/*.h)

objects         := $(patsubst %.cc, $(OBJ)%.o, $(sources))
release_objects := $(patsubst %.cc, $(OBJ)release/%.o, $(sources))
debug_objects   := $(patsubst %.cc, $(OBJ)debug/%.o, $(sources))

tests := $(wildcard tests/units/*.test.cc)
tests_objects += $(patsubst %.cc, $(OBJ)%.o, $(tests))
tests_objects += $(patsubst %.cc, $(OBJ)tests/%.o, $(sources))
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

CFLAGS += -I$(SRC) -I$(GLOG_DIR)include -I$(GFLAGS_DIR)include
LDFLAGS += -L$(GLOG_DIR)lib/ -L$(GFLAGS_DIR)lib -lglog -lgflags

default: CFLAGS += -O3 -fPIC -Wall -Wextra
default: $(BIN)$(exec)

release: CFLAGS += -O3 -fPIC -Wall -Wextra -D NDEBUG
release: $(BIN)$(exec)_release

debug: CFLAGS += -O0 -fPIC -Wall -Wextra -g  -D DEBUG
debug: $(BIN)$(exec)_debug

third_party: gflags glog gtest
glog:   $(GLOG_DIR)lib/libglog.a
gtest:  $(GTEST_DIR)libgtest.a
gflags: $(GFLAGS_DIR)libgflags.a

.PHONY: glog gtest gflags


################################################################################
# TESTS

CFLAGS_TEST = $(CFLAGS) -I third_party/gtest/googletest/include/
LDFLAGS_TEST = $(LDFLAGS) -L $(GTEST_DIR) -lgtest -lgtest_main -lpthread -lgcov

test: CFLAGS += -O0 --coverage -fprofile-arcs -ftest-coverage -fPIC
test: gtest $(BIN)test
run-test: test
	./$(BIN)test
run-test-valgrind: test FORCE
	$(call cmd-valgrind, ./$(BIN)test)
run-test-gdb: test FORCE
	$(call cmd-gdb, ./$(BIN)test)
run-test-coverage: run-test
	$(call cmd-gcovr, $(OBJ)tests/$(SRC))
FORCE:

################################################################################


check-style: $(sources) $(headers)
	python ./scripts/cpplint.py $^

# Special build
$(GTEST_DIR)libgtest.a:
	$(call cmd-call, scripts/build_gtest.sh)

$(GLOG_DIR)lib/libglog.a:
	$(call cmd-call, scripts/build_glog.sh)

$(GFLAGS_DIR)libgflags.a:
	$(call cmd-call, scripts/build_gflags)

# Generic rules

$(BIN)$(exec): $(objects)
	$(call cmd-ld, $@, $^)

$(BIN)$(exec)_release: $(release_objects)
	$(call cmd-ld, $@, $^)

$(BIN)$(exec)_debug: $(debug_objects)
	$(call cmd-ld, $@, $^)

$(BIN)test: $(tests_objects)
	echo $(tests_objects)
	$(call cmd-ld, $@, $^, $(LDFLAGS_TEST))

$(OBJ)tests/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS_TEST))

$(OBJ)release/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))

$(OBJ)debug/%.o: %.cc
	$(call cmd-cxx, $@, $<, $(CFLAGS))
