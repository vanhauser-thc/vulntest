C=ok ok2 bof fdleak strcpy strcpy2 tricky encrypt use_after_free hardcoded_password
CPP=confuse andreas double_free
# unresolv

all:	c cpp

c:	$(C)

cpp:	$(CPP)

confuse:	confuse.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

andreas:	andreas.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

double_free:	double_free.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

encrypt:	encrypt.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lcrypto

%:	%.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(C) $(CPP)

cleanall:	clean
	-~/src_artikel/clean_all.sh all
