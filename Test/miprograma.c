#include <stdio.h>
int main(int argc, char* argv[]){
    if(argc != 4){
        printf("./miprograma <arg1> <arg2> <arg3>\n");
    }
    else{
        printf("Has introducido los siguientes argumentos: %s %s %s", argv[1], argv[2], argv[3]);
    }
    return 0;
}
