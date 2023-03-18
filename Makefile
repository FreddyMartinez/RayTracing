PROG=main
SRCS= \
main.cc \
ray.cc \
camera.cc \
obj.cc \
png.cc \

CXX:=g++ -O3 -march=native

# Win
LIBS:=-lpng -lglfw3 -lglew32 -lglu32 -lopengl32 -lgdi32 -lz

OBJS:=$(SRCS:.cc=.o)
DEPS:=$(SRCS:.cc=.d)

all: $(PROG)

$(PROG): $(OBJS)
	@echo LD $<
	@$(CXX) -o $@ $^ $(LIBS)

%.o: %.cc
	@echo CXX $<
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	@if [ -n "$(OBJS)" ]; then rm -f $(OBJS); fi
	@if [ -n "$(DEPS)" ]; then rm -f $(DEPS); fi
	@if [ -f core ]; then rm -f core; fi
	@rm -f tags *.linkinfo

mrproper:
	@if [ -n "$(PROG)" ]; then rm -f $(PROG); fi
	@if [ -n "$(OBJS)" ]; then rm -f $(OBJS); fi
	@if [ -n "$(DEPS)" ]; then rm -f $(DEPS); fi
	@if [ -f core ]; then rm -f core; fi
	@rm -f tags *.linkinfo

-include $(DEPS)
