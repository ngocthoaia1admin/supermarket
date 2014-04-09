#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void get_content_tag(char* source, char* tag, char* result) {

    char end_tag[1000];
    strcpy(end_tag, "</");
    strcat(end_tag, tag + 1);
    int len_tag = strlen(tag);

    int re_begin = find(source, tag);
    int re_end = find(source, end_tag);

    int i;
    if(re_begin != -1) {
        int j = 0;
        for(i = re_begin + len_tag; i < re_end; i++) {
            result[j++] = source[i];
        }
        result[j] = '\0';
    } else {
        result[0] = '\0';
    }
}

int find(char* source, char* tag) {
    int i, j;
    int len_source = strlen(source);
    int len_tag = strlen(tag);
    for(i = 0; i <= len_source - len_tag; i++) {
        for(j = 0; j < len_tag; j++) {
            if(source[i + j] != tag[j]) {
                break;
            }
        }
        if(j == len_tag) {
            return i;
        }
    }
    return -1;
}

void get_first_tag(char* source, char* result) {
    int i;
    for(i = 0; i < strlen(source); i++) {
        result[i] = source[i];
        if(source[i] == '>') {
            result[i+1] = '\0';
            break;
        }
    }
}

char* create_tag(char* value, char* tag) {
    char result[1000];
    strcpy(result, tag);
    strcat(result, value);
    strcat(result, "</");
    strcat(result, tag + 1);
    return strdup(result);
}