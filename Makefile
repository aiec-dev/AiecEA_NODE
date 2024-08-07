 
OPENMP_FLAG=0
NNPACK_ENABLE=1
ARM_NEON_SUPPORT=1
DEBUG_MODE=0

 
SRC_DIR=./src_folder
DIST_DIR=./distribution
DARKNET_DIR=./darknet_nnpack_dir
OBJ_DIR=./objects/
TARGET_EXEC=AiecEA_obfuscated
DARKNET_LIB=libdarknet_obfuscated.a
DIST_LIB=libdistribution_obfuscated.a

 
COMPILER=gcc
LINKER_FLAGS= -lm -pthread
COMPILE_FLAGS=-Wall -fPIC -I$(SRC_DIR) -I$(DIST_DIR)/include -I$(DIST_DIR)/src -I$(DARKNET_DIR)/include -I$(DARKNET_DIR)/src -Iinclude -Isrc
COMMON_FLAGS=-I$(SRC_DIR) -I$(DIST_DIR)/include -I$(DIST_DIR)/src -I$(DARKNET_DIR)/include -I$(DARKNET_DIR)/src -Iinclude -Isrc
LIBRARY_LINKS=-L$(DIST_DIR) -l:$(DIST_LIB) -L$(DARKNET_DIR) -l:$(DARKNET_LIB)
 
ifeq ($(OPENMP_FLAG), 1)
    COMPILE_FLAGS+= -fopenmp
endif

ifeq ($(DEBUG_MODE), 1)
    OPTIMIZATION_FLAGS=-O0 -g
else
    OPTIMIZATION_FLAGS=-Ofast
endif

 
ifeq ($(NNPACK_ENABLE), 1)
    COMMON_FLAGS+= -DNNPACK_ENABLED
    COMPILE_FLAGS+= -DNNPACK_ENABLED
    LINKER_FLAGS+= -lnnpack -lpthreadpool
endif

ifeq ($(ARM_NEON_SUPPORT), 1)
    COMMON_FLAGS+= -DARM_NEON_SUPPORTED
    COMPILE_FLAGS+= -DARM_NEON_SUPPORTED -mfpu=neon-vfpv4 -funsafe-math-optimizations -ftree-vectorize
endif

 
COMPILE_FLAGS+=$(OPTIMIZATION_FLAGS)

 
OBJECTS=top_obj.o ftp_obj.o helper_obj.o partitioner_obj.o adj_reuse_obj.o self_reuse_obj.o edge_obj.o gateway_obj.o parser_obj.o
TARGET_OBJECTS=$(addprefix $(OBJ_DIR), $(OBJECTS))
DEPENDENCIES=$(wildcard $(SRC_DIR)/*.h) Makefile

 
all: create_objects $(TARGET_EXEC)

$(TARGET_EXEC): $(TARGET_OBJECTS) $(DARKNET_LIB) $(DIST_LIB)
	$(COMPILER) $(COMMON_FLAGS) $(COMPILE_FLAGS) $(TARGET_OBJECTS) -o $@ $(LIBRARY_LINKS) $(LINKER_FLAGS)

 
$(DARKNET_LIB):
	$(MAKE) -C $(DARKNET_DIR) NNPACK=$(NNPACK_ENABLE) ARM_NEON=$(ARM_NEON_SUPPORT) DEBUG=$(DEBUG_MODE) OPENMP=$(OPENMP_FLAG) all

$(DIST_LIB):
	$(MAKE) -C $(DIST_DIR) DEBUG=$(DEBUG_MODE) all

 
$(OBJ_DIR)%.o: %.c $(DEPENDENCIES)
	$(COMPILER) $(COMMON_FLAGS) $(COMPILE_FLAGS) -c $< -o $@

 
create_objects:
	mkdir -p $(OBJ_DIR)

 
test_obfuscated:
	./$(TARGET_EXEC) ${ARGS}

 
.PHONY: clean_everything clean

clean_everything:
	make -C $(DIST_DIR) clean
	make -C $(DARKNET_DIR) clean
	rm -rf $(TARGET_EXEC) $(TARGET_OBJECTS) *.log $(OBJ_DIR) *.png

clean:
	rm -rf $(TARGET_EXEC) $(TARGET_OBJECTS) *.log $(OBJ_DIR) *.png


USELESS_VAR=v1.0
useless_target:
	