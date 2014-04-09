#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void get_content_tag(char* source, char* tag, char* result) {

    char end_tag[1000];
    strcpy(end_tag, tag);
    insert(end_tag, "/", 1);
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

int insert(char* source, char* value, int pos) {
    int i;
    int len_source = strlen(source);
    int len_value = strlen(value);
    for(i = len_source - 1; i >= pos; i--) {
        source[i + len_value] = source[i];
    }
    for(i = 0; i < len_value; i++) {
        source[i + pos] = value[i];
    }
    source[len_source + len_value] = '\0';
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