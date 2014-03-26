LIBS=-l356

surfaces_lights.o : surfaces_lights.c surfaces_lights.h
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -c surfaces_lights.c

scene.o : scene.c surfaces_lights.h
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -c scene.c

hw2bp1.o : hw2bp1.c surfaces_lights.h scene.h 
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -c hw2bp1.c

hw2bp1 : hw2bp1.o surfaces_lights.o scene.o
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) $^ $(LDFLAGS) $(LIBS)

clean :
	rm -f *.o hw2bp1

