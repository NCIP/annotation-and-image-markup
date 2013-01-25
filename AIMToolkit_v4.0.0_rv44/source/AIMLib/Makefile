.PHONY: all altova altovaxml dAIMXML aimlib clean

BASEPATH := $(dir $(lastword $(MAKEFILE_LIST)))

all: aimlib
	
altova:
	cd $(BASEPATH)Altova && $(MAKE)
	
altovaxml:
	cd $(BASEPATH)AltovaXML && $(MAKE)
	
dAIMXML: altova altovaxml
	cd $(BASEPATH)AIMXML && $(MAKE)

aimlib: dAIMXML
	cd $(BASEPATH)AIMLib && $(MAKE)
	
clean:
	cd $(BASEPATH)Altova && $(MAKE) clean
	cd $(BASEPATH)AltovaXML && $(MAKE) clean
	cd $(BASEPATH)AIMXML && $(MAKE) clean
	cd $(BASEPATH)AIMLib && $(MAKE) clean
