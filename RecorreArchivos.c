#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int RecorreArchivos(char* nombreDirectorio){
    DIR* dir = opendir(strcat("./", nombreDirectorio) );

    if (dir == NULL){
        return 1;
    }

    struct dirent* file;
    file = readdir(dir);
    while(file != NULL){
        char* found = strstr(file->d_name, nombreDirectorio);
        
        if (found != NULL){
            //Lee archivo
            break;
        }
    }

    closedir(dir);

    return 0;
}