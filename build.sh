# emcc main.cpp -o main.html -I ~/newgame/raylib/src -L ~/newgame/raylib/build_web/raylib     -lraylib -s USE_GLFW=3 -s ASYNCIFY=1 -s WASM=1 -lm -lpthread  

 g++ -o main main.cpp -lraylib -lm -ldl -lpthread -lGL
