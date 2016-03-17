CC?=gcc
EXEC=raytracing
INCLUDE = -lm
CFLAGS=  -std=gnu99 -g 
OBJS := \
    Camera.o \
    Color.o \
    Light.o \
    Object.o \
    Plane.o \
    Ray.o \
    Source.o \
    Sphere.o \
    Vect.o \
    Vector.o \
    main.o

%.o: %.c Bool.h
	@$(CC) $(CFLAGS) $(INCLUDE) -o  $@ -c  $<

$(EXEC): $(OBJS)
	@$(CC) -o $@ $^ $(INCLUDE) $(CFLAGE)
	@echo "Done!"
	@rm *.o

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o *.bmp
	      	
