OBJS := imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o \
imgui.o imgui_impl_opengl3.o imgui_impl_glfw.o

libimgui.lib : $(OBJS)
	ar cr libimgui.a $(OBJS)

imgui_demo.o :
	g++ -std=c++11 -c imgui_demo.cpp -o $@

imgui_draw.o :
	g++ -std=c++11 -c imgui_draw.cpp -o $@

imgui_tables.o :
	g++ -std=c++11 -c imgui_tables.cpp -o $@

imgui_widgets.o :
	g++ -std=c++11 -c imgui_widgets.cpp -o $@

imgui.o :
	g++ -std=c++11 -c imgui.cpp -o $@

#注意../是指makefile所在的文件夹的上一层文件夹，不是原文件的位置
imgui_impl_opengl3.o :
	g++ -I./ -std=c++11 -c backends/imgui_impl_opengl3.cpp -o $@

imgui_impl_glfw.o :
	g++ -I../glfw/include -std=c++11  -I./ -c backends/imgui_impl_glfw.cpp -o $@

.PHONY : clean
clean : 
	-rm -rf $(OBJS)