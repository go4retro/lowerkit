TOPTARGETS := default all clean create

SUBDIRS := basic simpleparse parseroms mkroms drawsvg

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
