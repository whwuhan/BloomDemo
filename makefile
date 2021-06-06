# 导入目录配置
include makefile_conf.mk

#所有.o文件
OBJS := \
objs/bloom_demo_main.o \
objs/scene.o \
objs/sphere.o \
objs/camera.o \
objs/render.o \
objs/window.o

BloomDemo : $(OBJS)
	$(CC) $(FLAGS) \
	-I$(INCLUDE_DIR) \
	-I$(DEPS_INCLUDE_DIR) \
	-L$(LIBS_DIR) \
	-lglfw3 -lglad \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	$(OBJS) \
	-o $@ 
	./$@

# 程序入口目标文件bloom_demo_main.o
objs/bloom_demo_main.o : bloom_demo_main.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR) -c bloom_demo_main.cpp -o $@

# scene 场景
objs/scene.o : src/components/scene.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR) -c src/components/scene.cpp -o $@

# sphere
objs/sphere.o : src/geometry/sphere.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR) -c src/geometry/sphere.cpp -o $@

# 相机
objs/camera.o : src/utils/camera.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR) -c src/utils/camera.cpp -o $@

# 渲染工具
objs/render.o : src/utils/render.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR) -c src/utils/render.cpp -o $@

# window
objs/window.o : src/window.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR) -c src/window.cpp -o $@

# 清理文件
.PHONY : clean
clean : 
	rm -rf $(OBJS) BloomDemo