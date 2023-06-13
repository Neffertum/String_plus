#include "s21_string.h"
#include <stdlib.h>

void* s21_to_upper(const char *str) {
    if (!str)
        return S21_NULL;
    char* res = malloc(s21_strlen(str) + 1);
    if (res) {
        s21_size_t i = 0;
        for (; str[i]; i++)
            if ('a' <= str[i] && str[i] <= 'z')
                res[i] = str[i] - 32;
            else
                res[i] = str[i];
        res[i] = '\0';
    }
    return (void*)res;
}
void* s21_to_lower(const char *str) {
    if (!str)
        return S21_NULL;
    char* res = malloc(s21_strlen(str) + 1);
    if (res) {
        s21_size_t i = 0;
        for (; str[i]; i++)
            if ('A' <= str[i] && str[i] <= 'Z')
                res[i] = str[i] + 32;
            else
                res[i] = str[i];
        res[i] = '\0';
    }
    return (void*)res;
}
void* s21_insert(const char *src, const char *str, s21_size_t start_index) {
    if (!str || !src || start_index > s21_strlen(src))
        return S21_NULL;
    s21_size_t src_l = s21_strlen(src), j = 0;
    char* res = malloc(s21_strlen(str) + s21_strlen(src) + 1);
    if (res) {
        for (s21_size_t i = 0; i < start_index; i++, j++)
            res[j] = src[i];
        for (s21_size_t i = 0; str[i] != '\0'; i++, j++)
            res[j] = str[i];
        for (s21_size_t i = start_index; i < src_l + 1; i++, j++)
            res[j] = src[i];
    }
    return (void*)res;
}
void* s21_trim(const char *src, const char *trim_chars) {
    if (!src)
        return S21_NULL;
    if (!trim_chars || *trim_chars == '\0')
        trim_chars = " \n\b\t";
    int l = 0, r = s21_strlen(src) - 1, j = 0;
    for (; src[l] && s21_strchr(trim_chars, src[l]); l++) { }
    for (; l < r && s21_strchr(trim_chars, src[r]); r--) { }
    char* res = malloc(r - l + 2);
    if (res) {
        for (int i = l; i <= r; i++, j++)
            res[j] = src[i];
        res[j] = '\0';
    }
    return (void*)res;
}
