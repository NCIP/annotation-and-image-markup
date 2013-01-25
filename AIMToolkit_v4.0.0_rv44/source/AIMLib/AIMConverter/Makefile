include ../Makefile.rules

BINARY = AIMConverter

HDRS = AIMConverter.h
HDRS += ConverterUtil.h

SRCS = AIMConverter.cpp
SRCS += ConverterUtil.cpp

OBJDIR = $(OUT_FOLDER)
OBJS = $(addprefix $(OBJDIR)/,$(filter %.o, $(SRCS:.cpp=.o)))

LIBDIR = $(abspath ../$(OUT_FOLDER))
DEPLIBS = $(LIBDIR)/libAIMLib.a
SHAREDDEPLIBS = $(LIBDIR)/libAIMLib.so
LINKLIBS = AIMLib
LINKDIRS = $(LIBDIR)
Q ?= @

.PHONY: all clean

all: $(BINARY)

$(DEPLIBS):
	$(MAKE) -C ../AIMLib
	
$(SHAREDDEPLIBS):
	$(MAKE) -C ../AIMLib
	

$(BINARY): $(OBJS) $(DEPLIBS)

	@echo '===> LINKING $@'
	@echo '===> Binary file will be: $(LIBDIR)/$(BINARY)'
#	$(Q)$(CXX) $(OBJS) -o $(LIBDIR)/$(BINARY) $(addprefix -L,$(LINKDIRS)) $(addprefix -l,$(LINKLIBS)) -lpthread
	$(Q)$(CXX) $(OBJS) -o $(LIBDIR)/$(BINARY) $(addprefix -L,$(LINKDIRS)) $(addprefix -l,$(LINKLIBS)) -Wl,-rpath=.
	@echo 'Done.'
	
#	$(Q)chmod 755 run.sh

$(OBJS): $(SRCS) $(HDRS) | $(OBJDIR) $(LIBDIR)
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(@:$(OBJDIR)/%.o=%.cpp) -o $@

# Create Output dirs, if missing
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -Rf $(LIBDIR)/$(BINARY) $(OBJS)
