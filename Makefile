.POSIX:

.PHONY: clean

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
COMPILER_STATIC_ANALYZER = -fanalyzer

COMPILER_OPTIMIZATION_LEVEL_DEBUG = -Og -g3
COMPILER_OPTIMIZATION_LEVEL_SPEED = -O3
COMPILER_OPTIMIZATION_LEVEL_SPACE = -Os

OPTIMIZATION_LVL ?= $(COMPILER_OPTIMIZATION_LEVEL_DEBUG)
OPTIMIZATION_LVL ?= $(COMPILER_OPTIMIZATION_LEVEL_SPACE)

COMPILER_STANDARD = -std=c++11

INCLUDE_PATHS = -I.

COMMON_DEFINES ?=

DIAGNOSTIC_FLAGS =

CXXFLAGS = $(COMPILER_WARNINGS) $(SANITIZERS) $(COMPILER_STATIC_ANALYZER) \
				$(COMPILER_STANDARD) $(OPTIMIZATION_LVL) \
				$(COMMON_DEFINES) $(INCLUDE_PATHS) -fdiagnostics-color
CXXFLAGS ?= $(COMPILER_WARNINGS) $(COMPILER_STATIC_ANALYZER) \
				$(COMPILER_STANDARD) $(OPTIMIZATION_LVL) \
				$(COMMON_DEFINES) $(INCLUDE_PATHS) -fdiagnostics-color

LDFLAGS += $(DIAGNOSTIC_FLAGS)

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

%.lst: %.o
	@echo
	@echo "----------------------------------------"
	@echo -e "\033[36mDisassembly\033[0m of $< into $@..."
	@echo
	$(CROSS)objdump -D $< > $@

clean:
	rm ./*.exe
	rm ./*.lst
	rm ./*.o

.PRECIOUS: %.o