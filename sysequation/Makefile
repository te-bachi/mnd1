LIBRARIES_STATIC            = 
PROGRAMS                    = projekt1 forward backward gauss lu scale \
                              swap matmath hilbert

GLOBAL_CFLAGS               = -DSCALE=1 -DPIVOT=1 \
                              -O0 -pthread -pipe -Wall -ggdb -std=gnu99 \
                              -fms-extensions -Iinclude -Wmissing-prototypes \
                              -Wno-uninitialized -Wstrict-prototypes
GLOBAL_LDFLAGS              = -lm

### LIBRARIES #################################################################


### PROJEKT1 ##################################################################

projekt1_CFLAGS          = 
projekt1_LDFLAGS         = 
projekt1_LIBRARIES       = 
projekt1_SOURCE          = projekt1.c \
                           print.c \
                           scale.c \
                           forward.c \
                           backward.c \
                           lu.c \
                           gauss.c \
                           swap.c \
                           matmath.c

### FORWARD ###################################################################

forward_CFLAGS           = -D__FORWARD_MAIN__
forward_LDFLAGS          = 
forward_LIBRARIES        = 
forward_SOURCE           = forward.c \
                           print.c \
                           matmath.c

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

lu_CFLAGS                = -D__LU_MAIN__
lu_LDFLAGS               = 
lu_LIBRARIES             = 
lu_SOURCE                = lu.c \
                           scale.c \
                           forward.c \
                           backward.c \
                           print.c \
                           swap.c

### SCALE #####################################################################

scale_CFLAGS             = -D__SCALE_MAIN__
scale_LDFLAGS            = 
scale_LIBRARIES          = 
scale_SOURCE             = scale.c \
                           print.c

### SWAP ######################################################################

swap_CFLAGS              = -D__SWAP_MAIN__
swap_LDFLAGS             = 
swap_LIBRARIES           = 
swap_SOURCE              = swap.c \
                           print.c

### MATMATH ###################################################################

matmath_CFLAGS           = -D__MATMATH_MAIN__
matmath_LDFLAGS          = 
matmath_LIBRARIES        = 
matmath_SOURCE           = matmath.c \
                           print.c

### HILBERT ###################################################################

hilbert_CFLAGS           = -D__HILBERT_MAIN__
hilbert_LDFLAGS          = 
hilbert_LIBRARIES        = 
hilbert_SOURCE           = hilbert.c \
                           print.c \
                           lu.c \
                           matmath.c \
                           scale.c \
                           swap.c

include autogen.mk
