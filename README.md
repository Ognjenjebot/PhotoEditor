# PhotoEditor

Simple photo editing software that was once my university project. It was written from scratch in C++ and Java, soo I didn't use any external libraries. For now, the software reads only BMP format pictures, and I plan on adding other formats.

## C++
  The C++ was once a standalone project that was using the console for it apllication (no GUI). Now I converted it to a dll, and it's being used by Java. I plan to use every function of C++ and not just for reading and writting the picture and transfering the bytes to Java (I want to use it for all the operations on the picture).
  
## Java
  The Java part of the project uses the C++ dll for reading and writting the picture into a .BMP file. For the university project I used only the awt package for GUI, and I plan on making it a lot better. Also I've written code for the operations part, which I plan on connecting with C++ so that Java latter consists only of GUI code.
  
### Operations
  The editor has operations like ADD, SUBTRACT, MULTIPLY and so on and it has some well known effects like GREY SHADES, BLACK AND WHITE, INVERSE...
  ![effectsProject](https://user-images.githubusercontent.com/68485477/126663014-4225552b-d38d-40c4-84bc-66794e125e54.png)
  Example of MULTIPLY operation
  
### It also supports transparency and multiple layers
  The transpareny of layers can be set and they can be merged into one
  ![transparentnost](https://user-images.githubusercontent.com/68485477/126663271-22a4dd25-6be6-4683-81c0-7bdd3125b1df.png)
  

### Future plans
  I plan on making the GUI nicer, adding support for more picture formats, fixing all the bugs, making C++ more usefull in the project, maybe implementing threads so everything looks smoother,adding GPU acceleration if I learn how it's used etc.
  
### If someone is planning on using this project, java native library location needs to be set to the location of the c++ dll
