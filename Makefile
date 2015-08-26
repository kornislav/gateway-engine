engine.so: source/code/*.cpp source/code/*.h
	$(CC) -I source/code -c source/code/*.cpp -o engine.so