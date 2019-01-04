TARGET=sample_use

CC=gcc
CFLAGS=-O2 -Wall -Wextra -Wpedantic -Werror
PACKER=upx -9 -f	# pack the executable
STRIP=strip --strip-all

.PHONY: all static deploy clean

# Magic recipe to parse Makefile generating help
# https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
help:	## display this message
	@echo Available options:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

all:	clean | $(TARGET)	## clean & build ordinary(dynamic) executable

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -c $<

$(TARGET):
	$(CC) $(CFLAGS) $(addsuffix .c, $(TARGET)) $(LIBFLAGS) -o $@

	$(CC) -static $(CFLAGS) $(LIBFLAGS) $(addsuffix .c, $(TARGET)) -o $(TARGET)

deploy:	$(TARGET)		## prepare built executable for deploy
ifneq ($(STRIP), "")
	@echo Stripping unneeded symbols from executable...
	$(STRIP) $(TARGET)
endif
ifneq ($(PACKER), "")
	@echo Compressing executable...
	$(PACKER) $(TARGET)
endif

clean:				## tidy build directory
	@echo Tidying things up...
	-rm -f *.o $(TARGET)
