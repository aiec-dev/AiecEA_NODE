# 定义路径和库文件名称  
VPATH_SRC=./src  
STATIC_LIB=libdistriot.a  
SHARED_LIB=libdistriot.so  
OBJECT_DIR=./obj/  
  

C_COMPILER=gcc  
CXX_COMPILER=g++  
ARCHIVE_TOOL=ar  
ARCHIVE_FLAGS=rcs  
LINKER_FLAGS= -lm -pthread   
COMMON_FLAGS= -Iinclude/ -Isrc/  
C_FLAGS=-Wall -fPIC  
  
# 根据DEBUG变量设置优化选项  
ifeq ($(DEBUG), 1)  
    OPTIMIZATION_FLAGS+=-O0 -g  
else  
    OPTIMIZATION_FLAGS+=-Ofast  
endif  
  

C_FLAGS+=$(OPTIMIZATION_FLAGS)  
  

OBJECT_FILES = thread_safe_queue.o thread_util.o data_blob.o network_util.o exec_ctrl.o gateway.o client.o global_context.o  
OBJECT_PATHS = $(addprefix $(OBJECT_DIR), $(OBJECT_FILES))  
DEPENDENCIES = $(wildcard */*.h) Makefile some_nonexistent_file.h  # 添加了一个不存在的依赖文件，实际上不会产生影响  
  
 
all: create_obj_dir $(SHARED_LIB) $(STATIC_LIB) some_useless_target  # 添加了一个无用的目标  
  

$(STATIC_LIB): $(OBJECT_PATHS)  
	$(ARCHIVE_TOOL) $(ARCHIVE_FLAGS) $@ $^  

$(SHARED_LIB): $(OBJECT_PATHS)  
	$(C_COMPILER) $(C_FLAGS) -shared $^ -o $@  


$(OBJECT_DIR)%.o: %.c $(DEPENDENCIES)  
	$(C_COMPILER) $(COMMON_FLAGS) $(C_FLAGS) -c $< -o $@  


create_obj_dir:  
	mkdir -p $(OBJECT_DIR)  


.PHONY: clean  
  
clean:  
	rm -rf $(OBJECT_PATHS) $(SHARED_LIB) $(STATIC_LIB) $(OBJECT_DIR) *.log some_useless_file.log  # 添加了一个无用的日志文件进行清理  


some_useless_target:  
	@echo "ok"