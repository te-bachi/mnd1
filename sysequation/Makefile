LIBRARIES_STATIC            = 
PROGRAMS                    = backward gauss lu projekt1

GLOBAL_CFLAGS               = -O0 -pthread -pipe -Wall -ggdb -std=gnu99 -fms-extensions -Iinclude -Wmissing-prototypes -Wno-uninitialized -Wstrict-prototypes
GLOBAL_LDFLAGS              = -lm

### LIBRARIES #################################################################


### PROJEKT1 ##################################################################

projekt1_CFLAGS          = -DSCALE=0 -DPIVOT=0
projekt1_LDFLAGS         = 
projekt1_LIBRARIES       = 
projekt1_SOURCE          = projekt1.c \
                           print.c \
                           forward.c \
                           backward.c \
                           lu.c \
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

lu_CFLAGS                = -D__LU_MAIN__ -DSCALE=0 -DPIVOT=0
lu_LDFLAGS               = 
lu_LIBRARIES             = 
lu_SOURCE                = lu.c \
                           forward.c \
                           backward.c \
                           print.c

include autogen.mk
