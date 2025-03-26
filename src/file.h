#ifndef _FILE_H
#define _FILE_H

char* load_textfile(const char *filename);
void unload_textfile(char *content);
long get_file_size(const char *filename);
#endif