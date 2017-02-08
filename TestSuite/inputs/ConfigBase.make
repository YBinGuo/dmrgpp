# PsimagLite support is needed by DMRG++
LDFLAGS = -L../../PsimagLite/lib -lpsimaglite

# Compiler to use. If using MPI then say mpicxx here (or mpic++)
# and also say -DUSE_MPI below
CXX = g++

# We're using ansi C++
CPPFLAGS += -pedantic -ansi

# Enable MPI (you must set the proper
# compiler wrapper under CXX above)
# CPPFLAGS += -DUSE_MPI

# Enable warnings and treat warnings as errors
CPPFLAGS += -Wall -Werror

# This enables additional debugging
#CPPFLAGS += -D_GLIBCXX_DEBUG -D_GLIBCXX_PROFILE

# This makes the code use long instead of short integers
#CPPFLAGS +=-DUSE_LONG

# This makes the code use float instead of double
#CPPFLAGS += -DUSE_FLOAT

# This enables signals
#CPPFLAGS +=-DUSE_SIGNALS

# This enables gsl support
#CPPFLAGS +=-DUSE_GSL
#LDFLAGS += -lgsl -lgslcblas 

# This enables the custom allocator (use only for debugging)
#CPPFLAGS += -DUSE_CUSTOM_ALLOCATOR

#Change basis even for un-needed operators
#CPPFLAGS += -DOPERATORS_CHANGE_ALL

# Specify the strip command to use (or use true to disable) 
STRIP_COMMAND = true

