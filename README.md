# Color printer
A very simple (and scuffed) program that I wrote to facilitate my colorscheme tweaking process.
Currently it can only deal with RGBA images, keep that in mind.

# Dependencies

- SDL2: Definitions
- SDL2_image: Image handling

# Usage
Run the program, passing the desired file as an argument and the desired color format. If no option is provided, HEX will be used.

## Options
    -r  Use RGB color format.
    -x  Use HEX color format.

# Quick start
```console
$ make
$ ./a.out 'file' 'options'
```

# Disclaimer
You might encounter bugs, as I'm not a very experienced programmer (you can probably tell). If you do, please open an issue or make a pull request.
