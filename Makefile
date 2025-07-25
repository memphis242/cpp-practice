.POSIX:

.PHONY: clean
.PHONY: benchmark

STATIC_LIB_EXTENSION ?= lib
TARGET_EXTENSION ?= exe

CROSS ?=
GXX = $(CROSS)g++

# COMPILER_WARNINGS = \
#     -Wall -Wextra -Wpedantic -pedantic-errors \
#     -Wconversion -Wdouble-promotion -Wnull-dereference \
#     -Wwrite-strings -Wformat=2 -Wformat-overflow=2 \
#     -Wformat-signedness -Wuseless-cast \
#     -Wcast-align=strict -Wimplicit-fallthrough=3 -Wswitch-default \
#     -Wswitch-enum -Wfloat-equal -Wuse-after-free=2 \
#     -Wdeprecated-declarations -Wparentheses \
#     -Wreturn-type -Wlogical-op -Wstrict-aliasing \
#     -Wuninitialized -Wmaybe-uninitialized -Wshadow \
#     -Wduplicated-cond -Wduplicated-branches \
#     -Walloc-zero -Walloc-size -Wpacked

COMPILER_WARNINGS = \
    -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wdouble-promotion

SANITIZERS = -fsanitize=bool -fsanitize=undefined -fsanitize-trap
# -fanalyzer is not suitable for C++ code!
COMPILER_STATIC_ANALYZER =

COMPILER_OPTIMIZATION_LEVEL_DEBUG = -Og -g3
COMPILER_OPTIMIZATION_LEVEL_SPEED = -O3
COMPILER_OPTIMIZATION_LEVEL_SPACE = -Os

OPTIMIZATION_LVL ?= $(COMPILER_OPTIMIZATION_LEVEL_DEBUG)
OPTIMIZATION_LVL ?= $(COMPILER_OPTIMIZATION_LEVEL_SPACE)

COMPILER_STANDARD = -std=c++17

INCLUDE_PATHS =

COMMON_DEFINES ?=

BENCHMARK_DEFS = -DBENCHMARK_STATIC_DEFINE

DIAGNOSTIC_FLAGS =

CXXFLAGS = $(COMPILER_WARNINGS) $(SANITIZERS) $(COMPILER_STATIC_ANALYZER) \
				$(COMPILER_STANDARD) $(OPTIMIZATION_LVL) \
				$(COMMON_DEFINES) $(INCLUDE_PATHS) -fdiagnostics-color
CXXFLAGS ?= $(COMPILER_WARNINGS) $(COMPILER_STATIC_ANALYZER) \
				$(COMPILER_STANDARD) $(OPTIMIZATION_LVL) \
				$(COMMON_DEFINES) $(INCLUDE_PATHS) -fdiagnostics-color

BENCHMARK_LIBS = -lbenchmark -lbenchmark_main -lpthread -lshlwapi

EXTERNAL_LIBS =

LDFLAGS += $(DIAGNOSTIC_FLAGS)

OBJ_FILES = ch2-3.o CTrafficLight_E.o CppTrafficLight_E.o

benchmark:
	@echo "Benchmark Time!"
	$(GXX) $(COMPILER_STANDARD) -O2 -DNDEBUG -fstack-usage -c benchfcn1.cpp
	$(GXX) $(COMPILER_STANDARD) -O2 -DNDEBUG -fstack-usage -c benchfcn2.cpp
	$(GXX) $(COMPILER_STANDARD) -O2 -DNDEBUG $(BENCHMARK_DEFS) -o bench.$(TARGET_EXTENSION) bench.cpp benchfcn1.o benchfcn2.o $(BENCHMARK_LIBS)
	./bench.$(TARGET_EXTENSION)

ch2-3.exe: $(OBJ_FILES) ch2-3.lst
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mProducing output executable\033[0m $@..."
	@echo
	$(GXX) $(LDFLAGS) $(OBJ_FILES) -o $@

%.$(TARGET_EXTENSION): %.o %.lst
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mProducing output executable\033[0m $@..."
	@echo
	$(GXX) $(LDFLAGS) $< -o $@

%.o: %.cpp
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mCompiling\033[0m the source file: $<..."
	@echo
	$(GXX) $(CXXFLAGS) -c $< -o $@
# $(GXX) $(CXXFLAGS) -Wa,-alh=$(basename $@)_fromcomp.lst -c $< -o $@

%.o: %.c
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mCompiling\033[0m the source file: $<..."
	@echo
	$(GXX) $(CXXFLAGS) -c $< -o $@
# $(GXX) $(CXXFLAGS) -Wa,-alh=$(basename $@)_fromcomp.lst -c $< -o $@

%.lst: %.o
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mDisassembly\033[0m of $< into $@..."
	@echo
	$(CROSS)objdump -D $< > $@

clean:
	rm -f *.exe
	rm -f *.lst
	rm -f *.o

.PRECIOUS: %.o %.lst
