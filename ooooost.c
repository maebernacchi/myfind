#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  char * directory_path = "/Users/meganbernacchi/C projects";
    char cwd[50];
    getcwd(cwd , sizeof(cwd));
    getenv("HOME");
        DIR* d = opendir(directory_path);
        struct dirent* dir;
        if (d) {
            while ((dir = readdir(d)) != NULL) {
            printf("%s", cwd);
            printf("/%s\n", dir->d_name);
            }                            
        }
        closedir(d); 
  return(0);
}