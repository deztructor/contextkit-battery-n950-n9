PLUGIN:=battery.so

CXXFLAGS:=-fPIC \
	-std=c++0x \
	$(shell pkg-config --cflags contextsubscriber-1.0) \
	$(shell pkg-config --cflags QtCore) \
	$(shell pkg-config --cflags QtDBus)

CFLAGS:=-fPIC -DBME_API=11

LDFLAGS:=-lrt \
	$(shell pkg-config --libs contextsubscriber-1.0) \
	$(shell pkg-config --libs QtCore) \
	$(shell pkg-config --libs QtDBus)

all: $(PLUGIN) battest

CSRCS:=bmeipc.c
CXXSRCS:=batteryplugin.cpp moc_batteryplugin.cpp

OBJS:=$(CSRCS:.c=.o) $(CXXSRCS:.cpp=.o)

$(PLUGIN) : $(OBJS)
	g++ -shared -o $@ $(LDFLAGS) $^

battest : battest.o moc_battest.o
	g++ -o $@ $(LDFLAGS) $^

moc_%.cpp: %.hpp
	moc $(DEFINES) $(INCPATH) $< -o $@

%.o : %.c
	$(COMPILE.c) -MD -o $@ $<
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

%.o : %.cpp
	$(COMPILE.cpp) -MD -o $@ $<;
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

-include $(CSRCS:.c=.P)
-include $(CXXSRCS:.cpp=.P)

clean :
	rm -f *.o $(PLUGIN)

.PHONY : clean
