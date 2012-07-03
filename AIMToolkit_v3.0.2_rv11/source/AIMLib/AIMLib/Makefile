###############################################################################
# This is non-recursive Makefile. It uses Makefile.include files in the 
# sub-directories to get the list of files to compile.
###############################################################################
include ../Makefile.rules

NAME = AIMLib
LIBDIR = ../$(OBJDIR)
LIB = $(LIBDIR)/lib$(NAME).a
SHAREDLIB = $(LIBDIR)/lib$(NAME).so
SHAREDLIB_VER = $(SHAREDLIB).$(VERSION)

HDRS =  AIMCodes.h
HDRS += AIMCommon.h
HDRS += AimEnum.h
HDRS += AIMLib.h
HDRS += AimResultValidator.h
HDRS += AIMUtil.h

SRCS =  AIMCodes.cpp
SRCS += AimEnum.cpp
SRCS += AIMLib.cpp
SRCS += AimResultValidator.cpp
SRCS += AIMUtil.cpp

SUBDIR = util
SUBDIR += model
SUBDIR += operations

# Include Makefile.include from each sub-directory
SUBDIR_INCLUDES := $(addsuffix /Makefile.include,$(SUBDIR))
include $(SUBDIR_INCLUDES)

# Dynamically generates directoy-dependent variable names that contain list 
# of .h and .cpp files and reads those files for each directory.
SUBDIR_HDRS = $(foreach subdir,$(SUBDIR),$(addprefix $(subdir)/,$($(addprefix $(shell echo $(subdir) | tr "[:lower:]" "[:upper:]"),_HDRS))))
SUBDIR_SRCS = $(foreach subdir,$(SUBDIR),$(addprefix $(subdir)/,$($(addprefix $(shell echo $(subdir) | tr "[:lower:]" "[:upper:]"),_SRCS))))
# SUBDIR_SRCS_NO_DIR = $(foreach subdir,$(SUBDIR),$($(addprefix $(shell echo $(subdir) | tr "[:lower:]" "[:upper:]"),_SRCS)))
SUBDIR_SRCS_BOTH = $(SRCS) + $(SUBDIR_SRCS)

ALTOVA_PROJ = Altova
ALTOVA_PROJ += AltovaXML
ALTOVA_PROJ += AIMXML

# Ex: ../Altova/libAltova.a
DEPLIBS = $(addprefix ../,$(join $(ALTOVA_PROJ),$(addprefix /lib,$(addsuffix .a,$(ALTOVA_PROJ)))))
# Ex: ../Altova/libAltova.so
SHAREDDEPLIBS = $(addprefix ../,$(join $(ALTOVA_PROJ),$(addprefix /lib,$(addsuffix .so,$(ALTOVA_PROJ)))))
# All libraries that we are linking against
LINKLIBS = $(addprefix -l,$(ALTOVA_PROJ)) -lxerces-c -loflog -lofstd -ldcmdata -ldcmsr 
# All libraries search directories
LINKDIRS = $(addprefix -L../,$(ALTOVA_PROJ)) -L$(LIB_DCMTK_FOLDER)

# Xerces-C non-shared installation support
ifneq ($(strip $(LIB_XERCESC_FOLDER)),)
LINKDIRS += -L$(strip $(LIB_XERCESC_FOLDER))
endif

OBJDIR = $(OUT_FOLDER)
#OBJS = $(addprefix $(OBJDIR)/,$(filter %.o, $(SRCS:.cpp=.o)))
OBJS = $(addprefix $(OBJDIR)/,$(filter %.o, $(SUBDIR_SRCS_BOTH:.cpp=.o)))
OBJS_SUBDIR = $(addprefix $(OBJDIR)/,$(filter %.o, $(SUBDIR_SRCS:.cpp=.o)))
Q ?= @

.PHONY: all clean $(OBJDIR) $(SUBDIR) $(LIBDIR)


#all: $(LIB)
all: $(SHAREDLIB)


$(SHAREDLIB): $(ALTOVA_PROJ) $(OBJS)
	@echo '===> Linking shared $(SHAREDLIB)'
#	$(Q)$(CXX) -shared -fPIC -Wl,-soname,$(SHAREDLIB),-Bstatic,-whole-archive,--no-undefined $(LINKDIRS) $(LINKLIBS) $(OBJS) -o $(SHAREDLIB_VER) -Wl,-Bdynamic,-no-whole-archive -lpthread
	$(Q)$(CXX) -shared -fPIC -Wall -Wl,-Bstatic,-whole-archive,--no-undefined $(LINKDIRS) $(LINKLIBS) $(OBJS) -o $(SHAREDLIB_VER) -Wl,-Bdynamic,-no-whole-archive -lpthread
	$(Q)cp -f $(SHAREDLIB_VER) $(SHAREDLIB)

# DOES NOT WORK ON MOUNTED SHARED FOLDERS:
#	$(Q)ln -s $(SHAREDLIB_VER) $(SHAREDLIB)

$(LIB): $(ALTOVA_PROJ) $(OBJS)
	@echo '===> Linking $(LIB)'
	$(Q)ar cr $(LIB) $(OBJS)
	$(Q)ranlib $(LIB)

#$(OBJDIR)/%.o: $(HDRS) $(SRCS)
$(OBJS): | $(OBJDIR) $(SUBDIR) $(LIBDIR)
	@echo 'Compiling $(@:$(OBJDIR)/%.o=%.cpp)'
	$(CXX) -static -c -fPIC $(CFLAGS) $(CXXFLAGS) $(@:$(OBJDIR)/%.o=%.cpp) -o $@

# NOTE: both clean and compilation can depend on this!!!
# Call make <goal> on our subdirectories
#$(SUBDIR):
#	$(MAKE) $(MAKECMDGOALS) -C $@

# NOTE: This is used during both clean and compilation!!!
# Run Altova makefiles
$(ALTOVA_PROJ):
	$(MAKE) $(MAKECMDGOALS) -C ../$@

# Create Output dirs, if missing
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(SUBDIR):
	mkdir -p $(OBJDIR)/$@

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean: $(ALTOVA_PROJ)
	rm -Rf $(OBJS) $(addprefix $(OBJDIR)/,$(SUBDIR)) $(LIB) $(SHAREDLIB) $(SHAREDLIB_VER)

#	@for dir in $(SUBDIR); do \
#		$(MAKE) clean -C $$dir; \
#	done
#		cd $$dir && $(MAKE) clean && cd ..; \
#cd $(SUBDIR) && $(MAKE) clean

#	cd operations && $(MAKE) clean
#	cd util && $(MAKE) clean
