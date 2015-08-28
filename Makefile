LIBS := -lGLESv2 -lEGL

engine.so: source/code/*.cpp source/code/*.h
	$(CC) -I source/code -c source/code/*.cpp -L $(LIBS) -std=c++11 -o engine.so