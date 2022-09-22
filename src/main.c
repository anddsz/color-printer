#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Program {
    SDL_Surface *input;
    char *file_path;
    char *exec_name;
    char color_format;
} program;

void destroy();
void printColors();
unsigned int reverseByteOrder(unsigned int byte);

int main(int argc, char *argv[]){
    program.exec_name = argv[0];

    if(argc > 1){
        for(int i = 0; i < argc; i++){
            if(argv[i][0] == '-'){
                for(int j = 1; j < strlen(argv[i]); j++){
                    switch(argv[i][j]){
                        case 'x':
                            program.color_format = 'x';
                            break;
                        case 'r':
                            program.color_format = 'r';
                            break;
                        default:
                            printf("%s: flag '%s' not recognized\n", program.exec_name, argv[i]);
                            destroy();
                            return 1;
                    }
                }
            } else {
                program.file_path = argv[i];
            }
        }
        if(access(program.file_path, F_OK) == 0){
            program.input = IMG_Load(program.file_path);

            if(program.input != NULL){
                printColors();
            } else {
                printf("%s: loaded file '%s' not an image or unreadable\n", program.exec_name, program.file_path);
                return 1;
            }
        } else {
            printf("%s: specified file '%s' could not be loaded: make sure the file exists and is on the correct path\n", program.exec_name, program.file_path);
            destroy();
            return 1;
        }
    } else {
        printf("%s: no arguments were provided\n", program.exec_name);
        printf("usage: %s 'file'\n", program.exec_name);
        destroy();
        return 1;
    }

    destroy();
    return 0;
}

void destroy(){
    SDL_FreeSurface(program.input);
}

void printColors(){
    int color_count = 0;
    unsigned int pixel;

    switch(program.color_format){
        case 'x':
            for(int i = 0; i < program.input->h * program.input->w; i++){
                pixel = *((unsigned int *)program.input->pixels + i);
                printf("%8X\n", reverseByteOrder(pixel));
            }
            break;
        case 'r':
            for(int i = 0; i < program.input->h * program.input->w; i++){
                pixel = *((unsigned int *)program.input->pixels + i);
                printf("(%i, %i, %i)\n", (unsigned char)(pixel >> 0), (unsigned char)(pixel >> 8), (unsigned char)(pixel >> 16));
            }
            break;
        default:
            for(int i = 0; i < program.input->h * program.input->w; i++){
                pixel = *((unsigned int *)program.input->pixels + i);
                printf("%6X\n", reverseByteOrder(pixel));
            }
            break;
    }
}

unsigned int reverseByteOrder(unsigned int byte){
    return ((byte & 0x000000ff) << 24u) | ((byte & 0x0000ff00) << 8u) | ((byte & 0x00ff0000) >> 8u) | ((byte & 0xff000000) >> 24u);
}
