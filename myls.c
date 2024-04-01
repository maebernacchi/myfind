#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void list_directory(const char* directory_name);

int main(int argc, char** argv) {
  // Process arguments
  if (argc == 1) {
    list_directory(".");
  } else if (argc == 2) {
    list_directory(argv[1]);
  } else {
    fprintf(stderr, "Please specify one or zero command line arguments.\n");
  }

  return 0;
}

/*
 * Preconditions: Takes in a mode_t as the permissions and an array of characters
 * Postconditions: Returns a string of 'x', 'w', 'r', and/or '-' depending on the
 * permissions of file
 */
char* getPerms(mode_t perms, char output[10]) {
  output[0] = (S_IRUSR & perms) ? 'r' : '-';
  output[1] = (S_IWUSR & perms) ? 'w' : '-';
  output[2] = (S_IXUSR & perms) ? 'x' : '-';
  output[3] = (S_IRGRP & perms) ? 'r' : '-';
  output[4] = (S_IWGRP & perms) ? 'w' : '-';
  output[5] = (S_IXGRP & perms) ? 'x' : '-';
  output[6] = (S_IROTH & perms) ? 'r' : '-';
  output[7] = (S_IWOTH & perms) ? 'w' : '-';
  output[8] = (S_IXOTH & perms) ? 'x' : '-';
  return output;
}  // getPerms

/*
 * Preconditions: Takes in a struct stat and uses getPerms
 * Postconditions: Prints the permissions to the terminal
 */
void printProps(char* file) {
  char returnPerms[10];
  struct stat thing;
  stat(file, &thing);
  mode_t bits = thing.st_mode;
  printf("%s ", getPerms(bits, returnPerms));
}  // printProps

/*
 * Preconditions: Takes in a struct stat
 * Postconditions: Prints user and group IDs to the terminal
 */
void printID(char* file) {
  struct stat thing;
  stat(file, &thing);
  struct passwd* userID = getpwuid(thing.st_uid);
  printf("%s ", userID->pw_name);
  struct group* groupID = getgrgid(thing.st_gid);
  printf("%s ", groupID->gr_name);
}  // printUser

/*
 * Preconditions: Takes in a struct stat
 * Postconditions: Prints the size of a file to the terminal
 */
void printSize(char* file) {
  struct stat thing;
  stat(file, &thing);
  off_t size = thing.st_size;
  printf("%lld ", size);
}  // printStats

int isDir(char* file) {
  struct stat path;
  stat(file, &path);
  return S_ISREG(path.st_mode);
}  // isDir

/*
 * Preconditions: Takes the directory name in the form of char*\
 * Postconditions: Prints the permissions, userID, groupID, file size, and owner of
 * all files within the given directory
 */
void list_directory(const char* directory_name) {
  if (strcmp(directory_name, ".") == 0) {
    DIR* d;
    d = opendir(directory_name);
    struct dirent* dir;
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (isDir(dir->d_name) == 0)
          printf("d");
        else
          printf("-");
        printProps(dir->d_name);
        printID(dir->d_name);
        printSize(dir->d_name);
        printf("%s\n", dir->d_name);
      }
      closedir(d);
    }
  } else {  // If we aren't looking at our current directory
    getenv("HOME");
    DIR* d = opendir(directory_name);
    struct dirent* dir;
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (isDir(dir->d_name) != 0)
          printf("d");
        else
          printf("-");
        printProps(dir->d_name);
        printID(dir->d_name);
        printSize(dir->d_name);
        printf("%s\n", dir->d_name);  //
      }                               // while
    }
    closedir(d);  // if;
  }
}  // list_directory

