include ../Makefile.rules

NAME = Altova
LIB = lib$(NAME).a
SHAREDLIB = lib$(NAME).so

HDRS =  Altova.h
HDRS += StructInfo.h
HDRS += xs-datetime.h
HDRS += xs-types.h
HDRS += AltovaException.h
HDRS += SchemaTypes.h

SRCS =  StructInfo.cpp
SRCS += xs-types.cpp
SRCS += xs-datetime.cpp
SRCS += AltovaException.cpp
SRCS += SchemaTypes.cpp

OBJS = $(filter %.o, $(SRCS:.cpp=.o))
Q ?= @

.PHONY: all clean


all: $(LIB)


$(SHAREDLIB): $(OBJS)
	@echo '===> Linking shared $(SHAREDLIB)'
	$(Q)gcc -shared -Wl,-soname,$(SHAREDLIB) -o $(SHAREDLIB)$(VERSION) $(OBJS)
	$(Q)ln -s $(SHAREDLIB)$(VERSION) $(SHAREDLIB)

$(LIB): $(OBJS)
	@echo '===> Linking $(LIB)'
	$(Q)ar cr $(LIB) $(OBJS)
	$(Q)ranlib $(LIB)

$(OBJS): $(HDRS) $(SRCS)

clean:
	rm -Rf $(OBJS) $(LIB) $(SHAREDLIB)
