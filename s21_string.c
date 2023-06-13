#include "s21_string.h"
#include "s21_errno.h"
#include <stdlib.h>
#include <math.h>

char emsg_str[32];

void *s21_memchr(const void *str, int c, s21_size_t n) {
    const unsigned char *p = (const unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++)
        if (p[i] == (unsigned char)c)
            return (void*)(p + i);
    return S21_NULL;
}
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;
    for ( ; n-- ; p1++, p2++)
        if (*p1 != *p2)
            return (*p1 > *p2) - (*p2  > *p1);
    return 0;
}
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *dest_p = (unsigned char *)dest;
    const unsigned char *src_p = (const unsigned char *)src;
    for (s21_size_t i = 0; i < n; i++)
        dest_p[i] = src_p[i];
    return dest_p;
}
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    unsigned char *dest_p = (unsigned char *)dest;
    const unsigned char *src_p = (const unsigned char *)src;
    unsigned char *buff = malloc(n);
    for (s21_size_t i = 0; i < n; i++)
        buff[i] = src_p[i];
    for (s21_size_t i = 0; i < n; i++)
        dest_p[i] = buff[i];
    free(buff);
    return dest_p;
}
void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char* p = (unsigned char*) str;
    for (s21_size_t i = 0; i < n; i++)
        p[i] = c;
    return p;
}

char *s21_strcat(char *dest, const char *src) {
    s21_size_t i, l = s21_strlen(dest);
    for (i = 0; src[i] != '\0'; i++)
        dest[l + i] = src[i];
    dest[i + l] = '\0';
    return dest;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t i, l = s21_strlen(dest);
    for (i = 0; src[i] != '\0' && i < n; i++)
        dest[l + i] = src[i];
    dest[i + l] = '\0';
    return dest;
}
char *s21_strchr(const char *str, int c) {
    s21_size_t i = 0;
    for (; str[i] != c && str[i] != '\0'; i++) { }
    char *flag = (char*)str + i;
    if (!str[i] && c) {
        flag = S21_NULL;
    }
    return flag;
}
char *s21_strrchr(const char *str, int c) {
    int i = s21_strlen(str);
    for (; i >= 0 && str[i] != c; i--) { }
    char *flag = (char*)str + i;
    if (i < 0) {
        flag = S21_NULL;
    }
    return flag;
}
int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i = 1;
    while (*str1 && (*str1 == *str2) && i < n) {
        str1++;
        str2++;
        i++;
    }
    return (*str1 - *str2)*(n > 0);
}
char *s21_strcpy(char *dest, const char *src) {
    s21_size_t i;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    for (i = 0; src[i] != '\0' && i < n; i++)
        dest[i] = src[i];
    for (; i < n ; dest[i] = '\0', i++) { }
    return dest;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t i = 0;
    for (; !s21_strchr(str2, str1[i]) && str1[i]; i++) { }
    return i;
}
s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t i = 0;
    for (; s21_strchr(str2, str1[i]) && str1[i]; i++) { }
    return i;
}
char *s21_strpbrk(const char *str1, const char *str2) {
    char* p = (char*)str1;
    for (; !s21_strchr(str2, *p) && *p; p++) { }
    char *flag = p;
    if (!*p) {
        flag = S21_NULL;
    }
    return flag;
}

char *s21_strerror(int errnum) {
    char *flag;
    if (!ERRLAST) {
        flag = "Unsupported OS";
    } else if (errnum > 0 && errstr[errnum - 1] && errnum - 1  < ERRLAST) {
        flag = errstr[errnum - 1];
    } else if (!errnum) {
        flag = "Undefined error: 0";
    } else {
        s21_sprintf(emsg_str, "Unknown error: %d", errnum);
        flag = emsg_str;
    }
    return flag;
}

s21_size_t s21_strlen(const char *str) {
    s21_size_t i;
    for (i = 0; str[i] != '\0'; i++) { }
    return i;
}

const char *s21_strstr(const char *haystack, const char *needle) {
    int i = 0, j = 0;
    do {
        j = 0;
        while (haystack[i] == needle[j] && needle[j] != '\0') {
            j++;
            i++;
        }
        if (needle[j] == '\0')
            return haystack + i - j;
    } while (haystack[i++] != '\0');
    return S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char* start = S21_NULL;
    if (!str)
        str = start;
    str += s21_strspn(str, delim);
    if (!*str)
        return S21_NULL;
    char *r;
    for (r = str; !s21_strchr(delim, *r) && *r != '\0'; r++) { }
    if (*r)
        *r++ ='\0';
    start = r;
    return str;
}
