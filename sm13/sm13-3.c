#define _BSD_SOURCE
#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <stdlib.h>


int cmp(const void *a, const void *b) {
    return strcasecmp(*(char* const*)a, *(char* const*)b);
}

void dfs_by_folder(char *path, size_t len_path, char *filename, size_t len_file) {
    struct dirent *dd;

    char ** filenames = malloc(2 * sizeof(*filenames));
    size_t capacity = 2;
    size_t count_filenames = 0;

    DIR *dp = opendir(path);

    if (dp == NULL) {
        return;
    }
    
    if (len_file != 0)
        printf("cd %s\n", filename);

    while ((dd = readdir(dp))) {
        if (strcmp(dd->d_name, "..") == 0 || strcmp(dd->d_name, ".") == 0)
            continue;
        
        size_t len_file = strlen(dd->d_name);
        if (len_file >= PATH_MAX)
            continue;
        
        if (dd->d_type != DT_DIR)
            continue;
        
        if (count_filenames == capacity) {
            capacity *= 2;
            filenames = realloc(filenames, capacity * sizeof(*filenames));
        }

        filenames[count_filenames] = malloc(len_file+1);
        strcpy(filenames[count_filenames], dd->d_name);
        filenames[count_filenames][len_file] = 0;

        count_filenames++;
    }
    closedir(dp);

    qsort(filenames, count_filenames, sizeof(char *), cmp);

    char *fullpath = malloc(PATH_MAX + 1);
    strncpy(fullpath, path, len_path);
    if (fullpath[len_path - 1] != '/')
        fullpath[len_path++] = '/';

    for (size_t i = 0; i < count_filenames; ++i) {
        strcpy(fullpath + len_path, filenames[i]);
        size_t len_file = strlen(filenames[i]);
        fullpath[len_path + len_file] = 0;
        if (len_file + len_path + 1 >= PATH_MAX)
            continue;
        dfs_by_folder(fullpath, len_path + len_file, filenames[i], len_file);
        free(filenames[i]);
    }
    free(filenames);
    free(fullpath);
    if (len_file != 0)
        printf("cd ..\n");
    return;
}

int main(int args, char *argv[]) {
    size_t len_path = strlen(argv[1]);
    dfs_by_folder(argv[1], len_path, "", 0);
    return 0;
}
