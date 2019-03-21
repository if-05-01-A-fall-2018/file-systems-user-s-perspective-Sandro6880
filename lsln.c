#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

struct stat attributes;
void printFileType(mode_t mode) {
  if(S_ISBLK(mode) != 0)
    printf("b");
  else if(S_ISCHR(mode) != 0)
    printf("c");
  else if(S_ISDIR(mode) != 0)
    printf("d");
  else if(S_ISFIFO(mode) != 0)
    printf("f");
  else if(S_ISLNK(mode) != 0)
    printf("Symbolic link\n");
  else if(S_ISREG(mode) != 0)
    printf("-" );
}

void printAccesPriviliges() {
    printf( (S_ISDIR(attributes.st_mode)) ? "d" : "-");
    printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
}

void printInfo(char* name) {

  lstat(name, &attributes);

  printFileType(attributes.st_mode);
  printf(" " );
  printAccesPriviliges();
  printf("%d %d %d",attributes.st_uid ,attributes.st_gid, attributes.st_size);
  struct tm *info;
  printf("%s\n",name );
}

int main(int argc, char const *argv[]) {
  DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if(dir->d_name[0] != '.'){
          // printf("%s\n", dir->d_name);
          printInfo(dir->d_name);
        }
      }
      closedir(d);
    }
    return(0);
  return 0;
}
