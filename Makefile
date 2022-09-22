make:
	gcc src/*.c -lSDL2main -lSDL2 -lSDL2_image

test:
	gcc test.c -lSDL2main -lSDL2 -lSDL2_image
