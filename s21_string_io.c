#include "s21_string.h"
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

#ifdef __APPLE__
#define int8 long int
#else
#define int8 long long
#endif
typedef struct format_type {
    char left;
    char sign;
    char pfx;
    char xpfx;
    char zero;
    char up;
    char e;
    char g;
    int ns;
    int w;
    int pc;
} format_type;
char specs[] = "diuoxXcsnpfFeEgG%";

const char* get_flags(const char* s, format_type* flags) {
    while (s) {
        if (*s == '+')
            flags->sign = 1;
        else if (*s == '-')
            flags->left = 1;
        else if (*s == '#')
            flags->xpfx = 1;
        else if (*s == ' ')
            flags->pfx = 1;
        else if (*s == '0')
            flags->zero = 1;
        else
            break;
        s++;
    }
    flags->pfx = flags->pfx && !flags->sign;
    flags->zero = flags->zero && !flags->left;
    return s;
}
const char* get_wp(const char* s, int *w, va_list *args) {
    *w = 0;
    if (*s == '*') {
        *w = va_arg(*args, int);
        s++;
    }
    while (s) {
        if ('0' <= *s && *s <= '9' && *w < (INT_MAX - *s + 48)/10)
            *w = (*w)*10 + *s - 48;
        else
            break;
        s++;
    }
    return s;
}
// --------------------sprintf-region-----------------------------------
s21_size_t get_buf_size_dec(s21_size_t w, s21_size_t p, long int n, int sign) {
    s21_size_t i = 0;
    while (n != 0) {
        n /= 10;
        i++;
    }
    i += sign;
    p += sign;
    s21_size_t result = i;
    if (w > result)
        result = w;
    if (p > result)
        result = p;
    return result;
}
s21_size_t get_buf_size_udec(s21_size_t w, s21_size_t p, unsigned int8 n, s21_size_t ns, int sign) {
    s21_size_t i = 0;
    while (n != 0) {
        n /= ns;
        i++;
    }
    i += sign;
    p += sign;
    s21_size_t result = i;
    if (w > result)
        result = w;
    if (p > result)
        result = p;
    return result;
}
s21_size_t get_buf_size_flt(s21_size_t w, s21_size_t p, long double n, int sign) {
    s21_size_t i = 1 + (p > 0);
    while (fabsl(n) - 1.0 >= 0 && isfinite(n)) {
        n /= 10.0;
        i++;
    }
    i += p + sign;
    if (!isfinite(n))
        i = 5;
    if (w > i)
        return w;
    else
        return i;
}

char get_num_char(int num, int up) {
    if (0 <= num && num <= 9)
        return num + 48;
    switch (num) {
    case 10:
        return 'a' - up*32;
    case 11:
        return 'b' - up*32;
    case 12:
        return 'c' - up*32;
    case 13:
        return 'd' - up*32;
    case 14:
        return 'e' - up*32;
    case 15:
        return 'f' - up*32;
    default:
        return '?';
    }
}
s21_size_t spec_fltp(char* dest, long double d, int upper) {
    if (isnan(d)) {
        if (upper) {
            s21_strcpy(dest, "NAN");
        } else {
            s21_strcpy(dest, "nan");
        }
        return 3;
    } else if (d == INFINITY) {
        if (upper) {
            s21_strcpy(dest, "FNI");
        } else {
            s21_strcpy(dest, "fni");
        }
        return 3;
    } else if (d == -INFINITY) {
        if (upper) {
            s21_strcpy(dest, "FNI-");
        } else {
            s21_strcpy(dest, "fni-");
        }
        return 4;
    }
    return 0;
}

const char* set_format(format_type *fmt, const char* format, va_list *args) {
    format = get_flags(format, fmt);
    format = get_wp(format, &(fmt->w), args);
    if (*format == '.')
        format = get_wp(++format, &(fmt->pc), args);
    if (fmt->w < 0) {
        fmt->w = -fmt->w;
        fmt->left = 1;
    }
    if (fmt->pc < 0)
        fmt->pc = INT_MAX;
    return format;
}
int get_default_pc(char spec, int val) {
    if (val == INT_MAX) {
        for (int i = 0; i < 6; i++)
            if (spec == specs[i])
                return 1;
        for (int i = 10; i < 17; i++)
            if (spec == specs[i])
                return 6;
        if (spec == 'p')
            return 1;
    }
    return val;
}
int normalize(long double *d) {
    int e = 0;
    if (*d) {
        if (fabsl(*d) < 1.0) {
            for ( ; fabsl(*d) < 1.0; *d = *d*10, e--) { }
        } else if (fabsl(*d) >= 10.0) {
            for ( ; fabsl(*d) >= 10.0; *d = *d/10, e++) { }
        }
    }
    return e;
}
format_type set_numericp(format_type fmt, char spec) {
    if (spec == 'o')
        fmt.ns = 8;
    else if (spec == 'x' || spec == 'X')
        fmt.ns = 16;
    if (spec == 'X')
        fmt.up = 1;
    return fmt;
}
format_type set_scientific(format_type fmt, char spec) {
    if (spec == 'g' || spec == 'G')
        fmt.g = 1;
    else if (spec == 'e' || spec == 'E')
        fmt.e = 1;
    if (spec == 'G' || spec == 'E' || spec == 'F')
        fmt.up = 1;
    return fmt;
}
format_type shorten(format_type fmt, long double d) {
    int e = normalize(&d);
    if (!fmt.pc)
        fmt.pc = 1;
    if (-4 <= e && e < fmt.pc) {
        fmt.pc = fmt.pc - e - 1;
    } else {
        fmt.e = 1;
        fmt.pc -= 1;
    }
    return fmt;
}

s21_size_t dec_to_str(char* dest, format_type fmt, long int d, s21_size_t bsize) {
    s21_size_t i = 0;
    long double n = fabsl((long double)d);
    int sign = fmt.sign || fmt.pfx || d < 0;
    for (; i < bsize && n >= 1.0; i++, n /= 10)
        dest[i] = fmodl(n, 10.0l) + 48;
    for (; (i + sign < (s21_size_t)fmt.w  && fmt.zero) || i < (s21_size_t)fmt.pc; i++)
        dest[i] = '0';

    if (fmt.pfx && d >= 0)
        dest[i++] = ' ';
    if (d < 0)
        dest[i++] = '-';
    if (fmt.sign && d > 0)
        dest[i++] = '+';

    for (; i < (s21_size_t)fmt.w && !fmt.left; i++)
        dest[i] = ' ';
    return i;
}
s21_size_t udec_to_str(char* dest, format_type fmt, unsigned int8 d, s21_size_t bsize) {
    s21_size_t i = 0;
    unsigned int8 n = d;
    int sign = (((fmt.pfx && fmt.ns == 10) || (fmt.xpfx && fmt.ns == 8)) + 2*(fmt.xpfx && fmt.ns == 16));
    for (sign *= (d != 0); i < bsize && n > 0; i++, n /= fmt.ns)
        dest[i] = get_num_char(n%fmt.ns, fmt.up);
    for (; (i + sign < (s21_size_t)fmt.w && fmt.zero) ||\
            i + fmt.xpfx*(fmt.ns == 8) < (s21_size_t)fmt.pc; i++)
        dest[i] = '0';

    if (d || fmt.g) {
        if (fmt.xpfx && fmt.ns == 16 && fmt.up)
            dest[i++] = 'X';
        else if (fmt.xpfx && fmt.ns == 16 && !fmt.up)
            dest[i++] = 'x';
        if (fmt.xpfx && fmt.ns != 10)
            dest[i++] = '0';
    }

    for (; i < (s21_size_t)fmt.w && !fmt.left; i++)
        dest[i] = ' ';
    return i;
}
s21_size_t flt_to_str(char* dest, format_type fmt, long double d, s21_size_t bsize) {
    s21_size_t i = spec_fltp(dest, d, fmt.up);
    if (i)
        return i;
    long double whol, frac;
    frac = modfl(d, &whol);
    frac = roundl(fabsl(frac)*powl(10.0l, fmt.pc));
    if (fmt.g && !fmt.xpfx) {
        for ( ; (int)frac%10 == 0 && frac > 0; frac /= 10.0l, fmt.pc--) { }
    }
    if (fmt.g && !frac)
        fmt.pc = 0;
    if (fmt.pc) {
        for ( ; i < bsize && i < (s21_size_t)fmt.pc; i++, frac /= 10.0l)
            dest[i] = (int)(frac - floorl(frac/10.0l)*10.0l) + 48;
        dest[i++] = '.';
    }
    for (whol = roundl(fabsl(whol) + frac*(fmt.pc == 0)); i < bsize && whol >= 10.0l; i++, whol /= 10.0l)
        dest[i] = (int)(whol - floorl(whol/10.0l)*10.0l) + 48;
    dest[i++] = (int)whol + 48;
    for (; i + (fmt.sign || fmt.pfx || d < 0) + 4*fmt.e  < (s21_size_t)fmt.w && fmt.zero; i++)
        dest[i] = '0';
    if (fmt.pfx && d >= 0)
        dest[i++] = ' ';
    if (d < 0)
        dest[i++] = '-';
    if (fmt.sign && d > 0)
        dest[i++] = '+';
    for (; i + 4*fmt.e < (s21_size_t)fmt.w && !fmt.left; i++)
        dest[i] = ' ';
    return i;
}

char* print_dec(char* tar, format_type fmt, char bytec, va_list* args) {
    long int var;
    if (bytec == 'l')
        var = (long int)va_arg(*args, long int);
    else if (bytec == 'h')
        var = (short)va_arg(*args, int);
    else
        var = (int)va_arg(*args, int);
    s21_size_t bsize = get_buf_size_dec(fmt.w, fmt.pc, var, fmt.sign | fmt.pfx | (var < 0));
    char* buffer = malloc(bsize);
    int i = dec_to_str(buffer, fmt, var, bsize);
    for (int j = i - 1; j >= 0; j--, tar++)
        *tar = buffer[j];
    for (; i < fmt.w; i++, tar++)
        *tar = ' ';
    free(buffer);
    return tar;
}
char* print_udec(char* tar, format_type fmt, char bytec, va_list* args) {
    unsigned int8 var;
    if (bytec == 'l')
        var = (unsigned long int)va_arg(*args, unsigned long int);
    else if (bytec == 'h')
        var = (unsigned short)va_arg(*args, unsigned int);
    else
        var = (unsigned int)va_arg(*args, unsigned int);
    s21_size_t bsize = get_buf_size_udec(fmt.w, fmt.pc, var, fmt.ns, fmt.pfx + fmt.xpfx + (fmt.ns == 16));
    char* buffer = malloc(bsize);
    int i = udec_to_str(buffer, fmt, var, bsize);
    for (int j = i - 1; j >= 0; j--, tar++)
        *tar = buffer[j];
    for (; i < fmt.w; i++, tar++)
        *tar = ' ';
    free(buffer);
    return tar;
}
char* print_float(char* tar, format_type fmt, char bytec, va_list* args) {
    long double var;
    int e;
    if (bytec == 'L')
        var = va_arg(*args, long double);
    else
        var = va_arg(*args, double);
    if (fmt.g)
        fmt = shorten(fmt, var);
    if (fmt.e)
        e = normalize(&var);
    s21_size_t bsize = get_buf_size_flt(fmt.w, fmt.pc, var, fmt.sign | fmt.pfx | (var < 0));
    char* buffer = malloc(bsize);
    int i = flt_to_str(buffer, fmt, var, bsize);
    for (int j = i - 1; j >= 0; j--, tar++)
        *tar = buffer[j];
    if (fmt.e) {
        *(tar++) = 'e' - fmt.up*32;
        *(tar++) = '-'*(e < 0) + '+'*(e >= 0);
        *(tar++) = abs(e/10) + 48;
        *(tar++) = abs(e%10) + 48;
    }
    for (; i + 4*fmt.e < fmt.w; i++, tar++)
        *tar = ' ';
    free(buffer);
    return tar;
}
char* print_char(char* tar, format_type fmt, va_list* args) {
    int var = va_arg(*args, int);
    for (int i = 0; i < fmt.w - 1 && !fmt.left; i++, tar++)
        *tar = ' ';
    *tar = '\0';
    if (var <= UCHAR_MAX)
        *(tar++) = var;
    else
        return S21_NULL;
    for (int i = 0; i < fmt.w - 1 && fmt.left; i++, tar++)
        *tar = ' ';
    return tar;
}
char* print_str(char* tar, format_type fmt, char bytec, va_list* args) {
    char* var = va_arg(*args, char*);
    if (var) {
        int blank = fmt.w;
        if (s21_strlen(var) >= (s21_size_t)fmt.pc)
            blank -= fmt.pc;
        else
            blank -= s21_strlen(var);
        for (int i = 0; i < blank && !fmt.left; i++, tar++)
            *tar = ' ';
        for (int i = 0; i < fmt.pc && *var; i++, tar++) {
            if (bytec == 'l') {
                if (*((wchar_t*)var) <= UCHAR_MAX)
                    *tar = *var;
                else
                    return S21_NULL;
                var += sizeof(wchar_t);
            } else {
                *tar = *var;
                var++;
            }
        }
        for (int i = 0; i < blank && fmt.left; i++, tar++)
            *tar = ' ';
    } else {
        tar = s21_memcpy(tar, "(null)", 6);
        tar += 6;
    }
    return tar;
}
char* print_ptr(char* tar, format_type fmt, va_list* args) {
    void* var = va_arg(*args, void*);
    unsigned int8 ptr = (unsigned int8)var;
    fmt.ns = 16;
    fmt.g = 1;
    fmt.xpfx = 1;
    s21_size_t bsize = get_buf_size_udec(fmt.w, fmt.pc, ptr, fmt.ns, fmt.xpfx*2);
    char* buffer = malloc(bsize);
    int i = udec_to_str(buffer, fmt, ptr, bsize);
    for (int j = i - 1; j >= 0; j--, tar++)
        *tar = buffer[j];
    for (; i < fmt.w; i++, tar++)
        *tar = ' ';
    free(buffer);
    return tar;
}

char* p_ssprintf(char* str, char* old, const char* format, format_type fmt, va_list* args) {
    if (*format == 'd' || *format == 'i') {
        str = print_dec(str, fmt, *(format - 1), args);
    } else if (*format == 'u' || *format == 'o' || *format == 'x' || *format == 'X') {
        fmt = set_numericp(fmt, *format);
        str = print_udec(str, fmt, *(format - 1), args);
    } else if (*format == 'c') {
        str = print_char(str, fmt, args);
    } else if (*format == 's') {
        str = print_str(str, fmt, *(format - 1), args);
    } else if (*format == 'p') {
        str = print_ptr(str, fmt, args);
    } else if (*format == 'n') {
        int *n = va_arg(*args, int *);
        *n = str - old;
    } else if (*format == 'f' || *format == 'F' ||\
                *format == 'e' || *format == 'E' ||\
                *format == 'g' || *format == 'G') {
        fmt = set_scientific(fmt, *format);
        str = print_float(str, fmt, *(format - 1), args);
    } else if (*format == '%') {
        *(str++) = *format;
    } else {
        str = S21_NULL;
    }
    if (!str)
        *old = '\0';
    return str;
}

int s21_sprintf(char *str, const char *format, ...) {
    char* old = str;
    va_list args;
    va_start(args, format);

    for ( ; *format && str; format++) {
        if (*format == '%') {
            format_type fmt = {0, 0, 0, 0, 0, 0, 0, 0, 10, 0, INT_MAX};
            format++;
            format = set_format(&fmt, format, &args);
            while (!s21_strchr(specs, *format))
                format++;
            fmt.pc = get_default_pc(*format, fmt.pc);
            str = p_ssprintf(str, old, format, fmt, &args);
        } else {
            *(str++) = *format;
        }
    }
    va_end(args);
    if (!str)
        return -1;
    *str = '\0';
    return str - old;
}
// ---------------------------------------------------------------------
// --------------------------sscanf-region------------------------------
typedef struct type_info {
    char spec;
    char bytes;
    int ns;
    int w;
    char skip;
} type_info;

int succ;

type_info set_bound(type_info data, char size) {
    if (data.spec == 'i' || data.spec == 'u' || data.spec == 'd') {
        if (size == 'l')
            data.bytes = sizeof(long long);
        else if (size == 'h')
            data.bytes = sizeof(short);
        else
            data.bytes = sizeof(int);
    } else if (data.spec == 'f') {
        if (size == 'l')
            data.bytes = sizeof(double);
        else if (size == 'L')
            data.bytes = sizeof(long double);
        else
            data.bytes = sizeof(float);
    }
    return data;
}
type_info set_numerics(type_info tinf, char spec) {
    if (spec == 'x' || spec == 'X')
        tinf.ns = 16;
    else if (spec == 'o')
        tinf.ns = 8;
    else
        tinf.ns = 10;
    return tinf;
}
const char* set_pinfo(const char* format, type_info* tinf) {
    tinf->ns = 10;
    if ((tinf->skip = (*format == '*')))
            format++;
    format = get_wp(format, &(tinf->w), S21_NULL);
    if (tinf->w == 0)
            tinf->w = INT_MAX;
    return format;
}
const char* skip_space(const char* str, const char* space) {
    for ( ; s21_strchr(space, *str) && *str; str++) { }
    return str;
}
int cmpreg(const char* str1, const char* str2, int bytes) {
    int i = 1;
    while (*str1 && ((*str1 == *str2) || abs(*str1 - *str2) == 32) && i < bytes) {
        i++;
        str1++;
        str2++;
    }
    return ((*str1 > *str2) - (*str2  > *str1))*!(abs(*str1 - *str2) == 32);
}
const char* spec_flts(const char *nan, long double *d) {
    int shift = 0;
    if (!cmpreg(nan, "nan", 3)) {
        *d = NAN;
        shift = 3;
    } else if (!cmpreg(nan, "inf", 3)) {
        *d = INFINITY;
        shift = 3;
    } else if (!cmpreg(nan, "-inf", 4)) {
        *d = -INFINITY;
        shift = 4;
    }
    return nan + shift;
}
int get_char_num(char c) {
    if ('0' <= c && c <= '9')
        return c - 48;
    if (c == 'a' || c == 'A')
        return 10;
    else if (c == 'b' || c == 'B')
        return 11;
    else if (c == 'c' || c == 'C')
        return 12;
    else if (c == 'd' || c == 'D')
        return 13;
    else if (c == 'e' || c == 'E')
        return 14;
    else if (c == 'f' || c == 'F')
        return 15;
    return '?';
}
const char* def_numeric(const char* str, int *ns) {
    str = skip_space(str, " \t\b\n\r");
    if (*str == '0')
        *ns = 8;
    if (*(str + 1) == 'x' || *(str + 1) == 'X')
        *ns = 16;
    return str;
}

const char* get_dec(const char* str, type_info type, int8* d) {
    int sign = -(*str == '-') + (*str != '-'), digit = get_char_num(*str);
    const char* s = str;
    if (*str == '-' || *str == '+') {
        str++;
        digit = get_char_num(*str);
    }
    if (digit != '?' && digit < type.ns && str - s < type.w)
        *d = 0;
    else
        return S21_NULL;
    if ((s21_strchr(str, 'x') || s21_strchr(str, 'X')) && type.ns == 16)
        str += 2;
    digit = get_char_num(*str);
    while (*str != ' ' && *str != '\n' && *str != '\t' && str - s < type.w) {
        if (digit < type.ns && digit != '?')
            *d = *d*type.ns + digit*sign;
        else
            break;
        str++;
        digit = get_char_num(*str);
    }
    return str;
}
const char* get_float(const char* str, type_info type, long double* d) {
    int sign = -(*str == '-') + (*str != '-');
    int8 ord = 0;

    const char* s = str;
    str = spec_flts(str, d);
    if (s != str)
        return str;
    if (*str == '-' || *str == '+')
        str++;
    if (('0' <= *str && *str <= '9') && str - s < type.w)
        *d = 0;
    else
        return S21_NULL;
    while (*str != ' ' && *str != '\n' && *str != '\t' && str - s < type.w) {
        if ('0' <= *str && *str <= '9') {
            if (!ord)
                *d = *d*10 + *str - '0';
            else
                *d = *d + (*str - '0')/pow(10, ord++);
        } else if (*str == '.') {
            ord++;
        } else {
            break;
        }
        str++;
    }
    if (*str == 'e' || *str == 'E') {
        str++;
        type.w = INT_MAX;
        str = get_dec(str, type, &ord);
        *d = *d * pow(10.0, ord);
    }
    *d = *d * sign;
    return str;
}

const char* write_dec(const char* str, type_info inf, void* dest, char bytec) {
    inf = set_bound(inf, bytec);
    if (inf.spec == 'i')
        str = def_numeric(str, &(inf.ns));
    int8 var;
    str = get_dec(str, inf, &var);
    if (dest && str) {
        s21_memcpy(dest, &var, inf.bytes);
        succ++;
    }
    return str;
}
const char* write_udec(const char* str, type_info inf, void* dest, char bytec) {
    inf.spec = 'u';
    inf = set_bound(inf, bytec);
    unsigned int8 var;
    str = get_dec(str, inf, (int8*)&var);
    if (dest && str) {
        s21_memcpy(dest, &var, inf.bytes);
        succ++;
    }
    return str;
}
const char* write_flt(const char* str, type_info inf, void* dest, char bytec) {
    inf.spec = 'f';
    inf = set_bound(inf, bytec);
    long double var;
    str = get_float(str, inf, &var);
    if (dest && str) {
        if (bytec == 'l')
            *((double*)dest) = (double)var;
        else if (bytec == 'L')
            *((long double*)dest) = var;
        else
            *((float*)dest) = (float)var;
        succ++;
    }
    return str;
}
const char* write_char(const char* str, void* dest, char bytec) {
    if (dest) {
        if (bytec == 'l')
            *((wchar_t*)dest) = (unsigned char)*str;
        else
            *((char*)dest) = *str;
        succ++;
    }
    str++;
    return str;
}
const char* write_str(const char* str, type_info inf, void* dest, char bytec) {
    str = skip_space(str, " \t\b\n\r");
    char whitespace = *str == ' ' || *str == '\n' || *str == '\b' || *str == '\t';
    int i = 0;
    for (; i < inf.w && !whitespace && *str; i++) {
        if (bytec == 'l' && dest)
            *((wchar_t*)dest + i) = *str;
        else if (dest)
            *((char*)dest + i) = *str;
        str++;
        whitespace = *str == ' ' || *str == '\n' || *str == '\b' || *str == '\t';
    }
    if (dest) {
        if (bytec == 'l')
            *((wchar_t*)dest + i) = L'\0';
        else
            *((char*)dest + i) = '\0';
        succ++;
    }
    return str;
}
const char* write_ptr(const char* str, type_info inf, void* dest, char bytec) {
    inf.spec = 'u';
    inf = set_bound(inf, bytec);
    inf.ns = 16;
    unsigned int8 var;
    str = get_dec(str, inf, (int8*)&var);
    if (dest && str) {
        *((int8*)dest) = var;
        succ++;
    }
    return str;
}

const char* p_sscanf(const char* str, const char* s, const char* format, type_info tinf, void* arg) {
    tinf.spec = *format;
    const char* lookup = skip_space(str, " \t\n\r");
    if (!*lookup && *format != 'c' && *format != 'n')
        return S21_NULL;
    if (succ < 0)
        succ = 0;
    if (*format == 'd' || *format == 'i') {
        str = write_dec(lookup, tinf, arg, *(format - 1));
    } else if (*format == 'u' || *format == 'o' || *format == 'x' || *format == 'X') {
        tinf = set_numerics(tinf, *format);
        str = write_udec(lookup, tinf, arg, *(format - 1));
    } else if (*format == 'c') {
        str = write_char(str, arg, *(format - 1));
    } else if (*format == 's') {
        str = write_str(lookup, tinf, arg, *(format - 1));
    } else if (*format == 'n') {
        int *n = (int*)arg;
        if (n)
            *n = str - s;
    } else if (*format == 'p') {
        str = write_ptr(lookup, tinf, arg, 'l');
    } else if (*format == 'f' || *format == 'F' ||\
        *format == 'e' || *format == 'E' ||\
        *format == 'g' || *format == 'G') {
            str = write_flt(lookup, tinf, arg, *(format - 1));
    } else {
        str = S21_NULL;
    }
    return str;
}

int s21_sscanf(const char *str, const char *format, ...) {
    succ = -1;
    va_list args;
    va_start(args, format);
    const char* s = str;
    if (!*str)
        str = S21_NULL;
    for (; *format && str; format++) {
        if (*format == '%') {
            format++;
            type_info tinf;
            format = set_pinfo(format, &tinf);
            while (!s21_strchr(specs, *format))
                format++;

            void *arg = S21_NULL;
            if (!tinf.skip)
                arg = va_arg(args, void*);

            str = p_sscanf(str, s, format, tinf, arg);
        } else if (s21_strrchr(" \t\n\b\r", *format)) {
            str = skip_space(str, " \t\b\n\r");
        } else if (*str == *format) {
            str++;
        } else {
            break;
        }
    }
    va_end(args);
    return succ;
}
// ---------------------------------------------------------------------
