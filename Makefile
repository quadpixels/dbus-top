dbus-top: analyzer.o dbus_capture.o main.o menu.o sensorhelper.o views.o xmlparse.o
	g++ $^ -lsystemd -lncurses -lfmt -lpthread -I. -std=c++17 -g -O0 -o $@

%.o: %.cpp
	g++ $< -c -o $@ -std=c++17 -I.

clean:
	@for x in dbus-top analyzer.o dbus_capture.o main.o menu.o sensorhelper.o views.o xmlparse.o; do\
		if [ -f $$x ]; then   \
			rm -v $$x;  \
		fi                   \
	done	
