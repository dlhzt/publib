OBJS = threadlog.o filelog.o filelock.o readcfg.o synchronizer.o crontab.o md5.o aes.o $(WIN32_OBJS) $(UNIX_OBJS)
OUTPUT = libzhaopub.a
TESTOBJS = testaes.o
TEST = testaes

all: $(OUTPUT) $(TEST)
$(OUTPUT):$(OBJS)
	ar -r $(OUTPUT) $(OBJS)
$(TEST): $(TESTOBJS)
	 $(LINK) $(LINKOPTION) $@ $@.o -L. -lzhaopub
clean:
	rm -f $(OBJS)
	rm -f $(OUTPUT)
.SUFFIXES:  .o .cpp

.cpp.o:
	$(CPPCOMPILE) -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cpp

