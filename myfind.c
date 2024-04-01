#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Function prototypes
*/
void print_cur();
void print_other(char* directory_path);
void printFile(const char * fileName);

int isFile (char * str){
    char * check = strstr(str, "/");
    //In the case it is a file
    if(check == NULL)
        return 1;
    //In the case it is a path
    else
        return 0;
}

int main(int argc, char** argv) {
  // Process arguments
  if (argc == 1) {
    print_cur();
  } 
  if (argc == 2) {
    int output = isFile(argv[1]);
    if(output == 1)
        printFile(argv[1]);
    else if(output == 0)
        print_other(argv[1]);
    else 
        printf("Not a valid input\n");
  }

  return 0;
}

/**
 * Preconditions: Called within main.
 * Postconditions: Prints path and filename of all files in current directory.
*/
void print_cur(){
    char cwd[50];
    getcwd(cwd , sizeof(cwd));

    //The following three lines are required to make the actual dir stuff work
    DIR* d;
    d = opendir(cwd);
    struct dirent* dir;
    if (d) {
      while ((dir = readdir(d)) != NULL) {
      printf("%s", cwd);
      printf("/%s\n", dir->d_name);
    }
      closedir(d);
    }
}

void print_other(char* directory_path){
    getenv("HOME");
    chdir(directory_path);
    char cwd[50];
    getcwd(cwd , sizeof(cwd));
        DIR* d = opendir(cwd);
        struct dirent* dir;
        printf("%s", cwd);
        if (d) {
            while ((dir = readdir(d)) != NULL) {
            printf("%s", cwd);
            printf("/%s\n", dir->d_name);
            }                            
        }
        closedir(d); 
}

int isItFile(const char* string, const char** strings, int stringNum){
  for(int i = 0; i < stringNum; i++){
    if(!strcmp(string, strings[i])){
      return 1;
    }
  }
  return 0;
}


void printFile(const char * fileName){
    char cwd[50];
    getcwd(cwd , sizeof(cwd));
    const char ** filenames = malloc(sizeof(char*) * 20);
    //The following three lines are required to make the actual dir stuff work
    DIR* d;
    d = opendir(cwd);
    struct dirent* dir;
    int i = 0;
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        filenames[i] = dir->d_name;
        i++;
      }
      closedir(d);
    }  
    int truth = isItFile(fileName, filenames, i);
    if(truth == 1)
        printf("%s\n", fileName);
    else
        printf("File not found in current directory.\n");
}

