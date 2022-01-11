#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


void show_help()
{
    printf("Syntax: cleaner <folder_path>");
    printf("\n\n");
}

void clean_filename(char *path, char *filename)
{

    for(int k=0;k<strlen(filename);++k) {
        printf("(%.2x)", (unsigned char)filename[k]);
    }

}

void process_dir(char *path)
{
    char d_path[PATH_MAX]; // here I am using sprintf which is safer than strcat

    struct dirent * dir;

    printf("Processing: %s\n",path);
    DIR * d = opendir(path); // open the path

    if(d==NULL) {
        printf(" aborting, cannot open directory : %s\n",path);
        return;
    }
    while ((dir = readdir(d)) != NULL) {
        if(dir-> d_type != DT_DIR) {
            printf("- Filename : {[%s]} %li\n  Hex      :",dir->d_name,strlen(dir->d_name));
            clean_filename(path,dir->d_name);
            printf("\n");
        }
        else{
            if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) {
                sprintf(d_path, "%s/%s", path, dir->d_name);
                process_dir(d_path);
            }
        }
    }
    closedir(d);
}


int main(int argc, char *argv[])
{
    int status=0;
    int k;
    printf("Cleaner v0.0\n\n");

    if (argc<2)
    {
        show_help();
        status++;
    }
    else
    {

        printf("Processing ARGC: %d\n",argc);
        for (k=1;k<argc;++k)
        {
            printf("- ARGUMENT: %s\n",argv[k]);
            process_dir(argv[k]);
        }
    }
    printf("\n\n");
    return status;
}