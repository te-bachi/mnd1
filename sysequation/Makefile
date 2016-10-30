LIBRARIES_STATIC            = 
PROGRAMS                    = backward gauss lu

GLOBAL_CFLAGS               = -O0 -pthread -pipe -Wall -ggdb -std=gnu99 -fms-extensions -Iinclude -Wmissing-prototypes -Wno-uninitialized -Wstrict-prototypes
GLOBAL_LDFLAGS              = -lm

### LIBRARIES #################################################################


### MAIN ######################################################################

main_CFLAGS              = 
main_LDFLAGS             = 
main_LIBRARIES           = 
main_SOURCE              = main.c \
                           print.c \
                           backward.c \
                           gauss.c

### BACKWARD ##################################################################

backward_CFLAGS          = -D__BACKWARD_MAIN__
backward_LDFLAGS         = 
backward_LIBRARIES       = 
backward_SOURCE          = backward.c \
                           print.c

### GAUSS #####################################################################

gauss_CFLAGS             =  -D__GAUSS_MAIN__
gauss_LDFLAGS            = 
gauss_LIBRARIES          = 
gauss_SOURCE             = gauss.c \
                           print.c \
                           backward.c
                           
### LU ########################################################################

lu_CFLAGS                = -D__LU_MAIN__ -DSCALE=0 -DPIVOT=1
lu_LDFLAGS               = 
lu_LIBRARIES             = 
lu_SOURCE                = lu.c \
                           print.c

include autogen.mk
