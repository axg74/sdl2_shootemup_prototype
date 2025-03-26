#include <stdio.h>
#include <stdlib.h>

long get_file_size(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL) return -1;

    if (fseek(file, 0, SEEK_END) != 0) 
    {
        fclose(file);
        return -1;
    }

    long file_size = ftell(file);
    fclose(file);

    return file_size;
}

void unload_textfile(char *content)
{
    if (content != NULL) 
    {
        free(content);
    }
}

char* load_textfile(const char *filename)
{
    FILE *file;
    char *content = NULL;
    size_t read_length;

    long filesize = get_file_size(filename);
    
    if (filesize > 0)
    {
        content =  (char *)malloc(filesize + 1);
        if(content == NULL) return NULL;
    }

    file = fopen(filename, "rb");
    if (file == NULL) {
        unload_textfile(content);
        return NULL;
    }

    read_length = fread(content, 1, filesize, file);
    if (ferror(file)) {
        fclose(file);
        unload_textfile(content);
        return NULL;
    }

    content[read_length] = '\0';

   fclose(file);

    return content;
}
