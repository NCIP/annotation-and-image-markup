include ../Makefile.rules

NAME = AltovaXML
LIB = lib$(NAME).a
SHAREDLIB = lib$(NAME).so

HDRS =  AltovaXMLAPI.h
HDRS += XmlException.h
HDRS += Node.h
HDRS += XercesString.h

SRCS = XmlException.cpp Node.cpp

OBJS = $(filter %.o, $(SRCS:.cpp=.o))
Q ?= @

# Xerces-C non-shared installation support
ifneq ($(strip $(LIB_XERCESC_FOLDER)),)
DEPLIBS += $(strip $(LIB_XERCESC_FOLDER))/libxerces-c.a
SHAREDDEPLIBS += $(strip $(LIB_XERCESC_FOLDER))/libxerces-c.so
endif

.PHONY: all clean


all: $(LIB)


$(SHAREDLIB): $(OBJS) $(SHAREDDEPLIBS)
	@echo '===> Linking shared $(SHAREDLIB)'
	$(Q)gcc -shared -Wl,-soname,$(SHAREDLIB) -o $(SHAREDLIB)$(VERSION) $(OBJS)
	$(Q)ln -s $(SHAREDLIB)$(VERSION) $(SHAREDLIB)

$(LIB): $(OBJS) $(DEPLIBS)
	@echo '===> Linking $(LIB)'
	$(Q)ar cr $(LIB) $(OBJS)
	$(Q)ranlib $(LIB)

$(OBJS): $(HDRS) $(SRCS)

clean:
	rm -Rf $(OBJS) $(LIB) $(SHAREDLIB)
