#include <check.h>
#include "s21_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

START_TEST(memchr_test) {
    printf("Testing s21_memchar: ");
    char *test_strings[] = {
     "This ",  //  26
     "This string",
     "This string con",
     "This string contai",
     "This string contains",
     "This string contains of ",
     "This string contains of some",
     "This string contains of some nu",
     "This string contains of some numbe",
     "This string contains of some numbers",
     "This string contains of some numbers: 1",
     "This string contains of some numbers: 111 ",
     "This string contains of some numbers: 111 222_",
     "This string contains of some numbers: 111 2222 333",
     "This string contains of some numbers: 111 2222 3333 4",
     "This string contains of some numbers: 111 2222 3333 444 555 ",
     "This string contains of some numbers: 111 2222 3333 444 555 and ",
     "This string contains of some numbers: 111 2222 3333 444 555 and some s",
     "This string contains of some numbers: 111 2222 3333 444 555 and some specia",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbol",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols:",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^&*(",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^&*()_",
     "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^&*()_!"
     "@#$^&*()_"
     };


    s21_size_t butes[] = {
        1, 2, 3, 4, 5, 6, 7, 11, 13, 14, 14, 0, 0, 14, 17, 30, 53, 59, 35, 0, 20, 34, 25, 34, 50, 25
    };

    char test_case[] = {
        'T', 's', 'i', 'c', 'o', 'f', 'n', '1', '3', 63, 'a', 'l',
        '!', '@', '#', '(', 123, 105, 'z', '8', 'd', 's', '_', '@', '&', ')'
    };

    for (int i = 0; i < 26; i++)
        ck_assert_ptr_eq(memchr(test_strings[i], test_case[i], butes[i]), \
        s21_memchr(test_strings[i], test_case[i], butes[i]));
    printf("[PASS]\n");
}
END_TEST
START_TEST(memcmp_test) {
    printf("Testing s21_memcmp: ");
    char *buff_string[] = {
        "abrakadabra", "!!!", "!@@!@@!", "!@@!@!!", "abakbab\0",
        "12345", "12345", "\0abrak", "D", "Z", "Ad", "AD", "AZ", "ZA"
    };
    char *s21_string[] = {
        "abrakadabra", "!!!@", "!@@!@@!", "!@@!@!!", "abakab\0", "123456",
        "12345", "\0abrak", "d", "z", "ad", "aD", "Az", "za"
    };

    s21_size_t byte_c[] = {
        3, 2, 4, 5, 1, 5, 3, 2, 0, 1, 1, 1, 1, 1
    };

    for (int i = 0; i < 14; i++) {
        int std_res = memcmp(buff_string[i], s21_string[i], byte_c[i]);
        int our_res = s21_memcmp(buff_string[i], s21_string[i], byte_c[i]);
        ck_assert_int_eq(std_res/abs(std_res), our_res/abs(our_res));
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(memcpy_test) {
    printf("Testing memcpy: ");
    char our_buff[64];
    char buff[64];
    char *test_string[] = {
        "ww", "www", "wwww", "wwwww", "\0wwwwww", "wwwwwww", "wwwwwwww", "wwwwwwwww", "wwwwwwwwww",
        "wwwwwwwwwww", "wwwwwwwwwwww", "wwwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwww", "wwwwwwwwwwwwww", "wwwwwwwwwwwwww", "wwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\0",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwww\0wwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
    };
    s21_size_t byte_c[] = {
        2, 3, 4, 5, 7, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 17, 18, 16, 14, 13, 23, 31, 37, 47, 5, 6,
    };
    for (int i = 0; i < 26; i++) {
        memcpy(buff, test_string[i], byte_c[i]);
        s21_memcpy(our_buff, test_string[i], byte_c[i]);
        for (s21_size_t j = 0; j < byte_c[i]; j++)
            ck_assert_int_eq(buff[j], our_buff[j]);
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(memmove_test) {
    printf("Testing s21_memove: ");
    char our_buff[64];
    char buff[64];
    char *test_string[] = {
        "ww", "www", "wwww", "wwwww", "\0wwwwww", "wwwwwww", "wwwwwwww", "wwwwwwwww", "wwwwwwwwww",
        "wwwwwwwwwww", "wwwwwwwwwwww", "wwwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwww", "wwwwwwwwwwwwww", "wwwwwwwwwwwwww", "wwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\0",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwww\0wwwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
    };
    s21_size_t byte_c[] = {
        2, 3, 4, 5, 7, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 17, 18, 16, 14, 13, 23, 31, 37, 47, 5, 6,
    };
    for (int i = 0; i < 26; i++) {
        memcpy(buff, test_string[i], byte_c[i]);
        s21_memcpy(our_buff, test_string[i], byte_c[i]);
        for (s21_size_t j = 0; j < byte_c[i]; j++)
            ck_assert_int_eq(buff[j], our_buff[j]);
    }
    s21_strcpy(buff, "this is a byte sequence");
    s21_strcpy(our_buff, "this is a byte sequence");
    ck_assert_str_eq(s21_memmove(buff, buff + 10, 4), memmove(buff, buff + 10, 4));
    ck_assert_str_eq(s21_memmove(buff + 6, buff + 12, 1), memmove(buff + 6, buff + 12, 1));
    ck_assert_str_eq(s21_memmove(buff, buff + 5, 12), memmove(buff, buff + 5, 12));
    printf("[PASS]\n");
}
END_TEST
START_TEST(memset_test) {
    printf("Testing s21_memset: ");
    char our_buff[16], buff[16];
    for (int i = 128; i < 255; i++) {
        memset(buff, i, 16);
        s21_memset(our_buff, i, 16);
        for (int j = 0; j < 16; j++)
            ck_assert_int_eq(buff[j], our_buff[j]);
    }
    printf("[PASS]\n");
}
END_TEST

START_TEST(strcat_test) {
    printf("Testing s21_strcat: ");
    char* cat[] = {
        "string",
        "string",
        "str\0ing",
        "string",
        "not string",
        "string",
        "str\0\0\0\0\0\0ing",
        "0",
        "string",
        "string",
        "\0",
        "string",
        "\0\0\0\0\0\0string",
        "string",
        "           ",
        "\0string",
        "string",
        "0987654321",
        "string",
    };
    char dest[][64] = {
        "xyz",
        "@",
        "nothing",
        "ckdmsipgargou;qewhig",
        "           ",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "1234567890",
        "nothingx2",
        "empty",
        "rty",
        "emp\0ty",
        "\0emp\0ty",
        "zxcvbn",
        "asd",
        "%"
    };
    char dest21[][64] = {
        "xyz",
        "@",
        "nothing",
        "ckdmsipgargou;qewhig",
        "           ",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "1234567890",
        "nothingx2",
        "empty",
        "rty",
        "emp\0ty",
        "\0emp\0ty",
        "zxcvbn",
        "asd",
        "%"
    };
    for (int i = 0; i < 19; i++) {
        ck_assert_str_eq(s21_strcat(dest21[i], cat[i]), \
                         strcat(dest[i], cat[i]));
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(strncat_test) {
     printf("Testing s21_strncat: ");
    s21_size_t byte_c[] = {
        3, 8, 1, 2, 3, 3, 1, 1, 4, 8, 7, 6, 5, 1
    };
    const char* test_strings[] = {
        "abcde",
        "@@@@@@@",
        "",
        "1234",
        "\t\b\n",
        "\n\n\n",
        "\b",
        "\0",
        "\0\0\0",
        "\0qwerty",
        "qwe\0rty",
        "qwe\nrty",
        "qwe\brty",
        "%%",
    };
    char dest[][64] = {
        "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%"
    };
    char dest21[][64] = {
        "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%"
    };
    for (int i = 0; i < 14; i++) {
        ck_assert_str_eq(s21_strncat(dest21[i], test_strings[i], byte_c[i]), \
                         strncat(dest[i], test_strings[i], byte_c[i]));
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(strchr_test) {
      printf("Testing strchr: ");
    char *our_buff[] = {
        "This ",  // 26
        "This string",
        "This string con",
        "This string contai",
        "This string contains",
        "This string contains of ",
        "This string contains of some",
        "This string contains of some nu",
        "This string contains of some numbe",
        "This string contains of some numbers",
        "This string contains of some numbers: 1",
        "This string contains of some numbers: 111 ",
        "This string contains of some numbers: 111 222_",
        "This string contains of some numbers: 111 2222 333",
        "This string contains of some numbers: 111 2222 3333 4",
        "This string contains of some numbers: 111 2222 3333 444 555 ",
        "This string contains of some numbers: 111 2222 3333 444 555 and ",
        "This string contains of some numbers: 111 2222 3333 444 555 and some s",
        "This string contains of some numbers: 111 2222 3333 444 555 and some specia",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbol",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols:",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^&*(",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^&*()_",
        "This string contains of some numbers: 111 2222 3333 444 555 and some special symbols: !!@#$^&*()_!"
        "@#$^&*()_"
     };
     char test_case[] = {
         'T', 's', 'i', 'c', 'o', 'f', 'n', '1', '3', 63, 'a',
         'l', '!', '@', '#', '(', 123, 105, 'z', '8', 'd', 's', '_', '@', '&', ')'
         };

     for (int i = 0; i < 26; i++) {
        ck_assert_ptr_eq(s21_strchr(our_buff[i], test_case[i]), strchr(our_buff[i], test_case[i]));
     }
     printf("[PASS]\n");
}
END_TEST
START_TEST(strcmp_test) {
    printf("Testing strcmp: ");
    char *buff_string[] = {
        "abrakadabra", "!!!", "!@@!@@!", "!@@!@!!", "abakbab\0",
        "12345", "12345", "\0abrak", "D", "Z", "Ad", "AD", "AZ", "ZA"
    };
    char *s21_string[] = {
        "abrakadabra", "!!!@", "!@@!@@!", "!@@!@!!",
        "abakab\0", "123456", "12345", "\0abrak", "d", "z", "ad", "aD", "Az", "za"
    };

    for (int i = 0; i < 14; i++) {
        int our = s21_strcmp(buff_string[i], s21_string[i]);
        int std_lib = strcmp(buff_string[i], s21_string[i]);
        ck_assert_int_eq(our/abs(our), std_lib/abs(std_lib));
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(strncmp_test) {
    printf("Testing strncmp:");
    char *buff_string[] = {
        "abrakadabra", "!!!", "!@@!@@!", "!@@!@!!", "abakbab\0", "12345",
        "12345", "\0abrak", "D", "Z", "Ad", "AD", "AZ", "ZA"
    };
    char *s21_string[] = {
        "abrakadabra", "!!!@", "!@@!@@!", "!@@!@!!", "abakab\0",
        "123456", "12345", "\0abrak", "d", "z", "ad", "aD", "Az", "za"
    };

    s21_size_t byte_c[] = {
        3, 2, 4, 5, 1, 5, 3, 2, 0, 1, 1, 1, 1, 1
    };

    for (int i = 0; i < 14; i++) {
        int std_res = strncmp(buff_string[i], s21_string[i], byte_c[i]);
        int our_res = s21_strncmp(buff_string[i], s21_string[i], byte_c[i]);
        ck_assert_int_eq(our_res/abs(our_res), std_res/abs(std_res));
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(strcpy_test) {
    printf("Testing s_21_strcpy: ");
    int BUFF_SIZE  = 21;
    char dest21[4096];
    char dest[4096];
    char *test_strings[]= {
         "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%",
        "\t\t",
        "\0",
        "b",
        "\0abcd",
        "\nabd",
        "\b",
        "\v",
        "ab\v\0"
    };
    for (int i = 0; i < BUFF_SIZE; i++)
        ck_assert_str_eq(s21_strcpy(dest21, test_strings[i]), \
                         strcpy(dest, test_strings[i]));
    printf("[PASS]\n");
}
END_TEST
START_TEST(strncpy_test) {
    printf("Testing s21_strncpy: ");
    const char* test_strings[] = {
    "abcdert",
    "@@@@@@@",
    "",
    "1234",
    "\t\b\n",
    "\n\n\n",
    "\b",
    "\0",
    "\0\0\0",
    "\0qwerty",
    "qwe\0rty",
    "qwe\nrty",
    "qwe\brty",
    "%%",
    "\0tempass",
    "abd\t\t",
    "brbrbr\b\b\b",
};

    char dest[4096] ="br br br";
    char dest21[4096] = "br br br";
    s21_size_t byte_c[] = {
        3, 8, 1, 2, 3, 3, 1, 1, 4, 8, 7, 6, 5, 3, 5, 6, 1
    };
    for (int i = 0; i < 17; i++)
        ck_assert_str_eq(s21_strncpy(dest21, test_strings[i], byte_c[i]), \
                         strncpy(dest, test_strings[i], byte_c[i]));
    printf("[PASS]\n");
}
END_TEST
START_TEST(strcspn_test) {
    printf("Testing s21_strcspn: ");
    char dest[4096] ="abcdefght\t\t\n\n001!!";
    char src[4096] = "abcdefght\t\t\n\n001!!";
    char *test[] = {
        "abc", "frg", "\0", "\n", "\001", "abcdefght\t\t\n\n001!!",
        "z", "brbr", "afk", "\0abrakadabra", "\t001", "a"
    };
    for (int i = 0; i < 12; i++)
        ck_assert_int_eq(s21_strcspn(dest, test[i]), strcspn(src, test[i]));
    printf("[PASS]\n");
     printf("\n");
}
END_TEST
START_TEST(strerror_test) {
    printf("\nTesting s21_strerror: ");
    for (int i = -400; i < 400; i++)
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    printf("[PASS]\n");
}
END_TEST
START_TEST(strlen_test) {
    printf("Testing size_t_s21_strlen: ");
    char *test_strings[]= {
         "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%",
        "\t\t",
        "\0",
        "b",
        "\0abcd",
        "\nabd",
        "\b",
        "\v",
        "ab\v\0"
    };
    for (int i = 0; i < 22; i++)
        ck_assert_int_eq(s21_strlen(test_strings[i]), strlen(test_strings[i]));
    printf("[PASS]\n");
}
END_TEST
START_TEST(strpbrk_test) {
    printf("Testing s_21_strpbrk: ");
    char *test_strings[]= {
         "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%",
        "\t\t",
        "\0",
        "b",
        "\0abcd",
        "\nabd",
        "\b",
        "\v",
        "ab\v\0",
        "br",
        "21",
        "4221",
        "42\0",
        "brbr"
    };
    char *buffer[] = {
         "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%",
        "\t\t",
        "\0",
        "b",
        "\0abcd",
        "\nabd",
        "\b",
        "\v",
        "ab\v\0",
        "mpty",
        "\0abcde",
        "dba",
        "NOTHIng",
        "x2"
    };
    for (int i = 0; i < 27; i++)
        ck_assert_ptr_eq(s21_strpbrk(buffer[i], test_strings[i]), s21_strpbrk(buffer[i], test_strings[i]));
    printf("[PASS]\n");
}
END_TEST
START_TEST(strrchr_test) {
    printf("Testing s21_strrchr: ");
    char *buffer[] = {
        "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%",
        "\t\t",
        "\0",
        "b",
        "\0abcd",
        "\nabd",
        "\b",
        "\v",
        "ab\v\0",
        "mpty",
        "\0abcde",
        "dba",
        "NOTHIng",
        "x2",
        "brbbbbbbbr",
        "rbbrbb",
        "111111111121",
        " ",
        "",
        "AaaaaaaaA",
        "euwhfjioewjioe",
        "euyiueiuyuie",
    };
    char test_char[] = {
        'c', '\0', 'N', '\b', 'b', '@', 'a', '\t', '\r', 'q', '1', 'e', '2',
        'k', 'l', 'd', 'D', '$', '%', 'O', ' ', 'a', 'a', 'a',
        'N', '2', '1', 'A', 'Q', 'e', 'i', 'f', 'r', 'k', 'j'
    };

    for (int i = 0 ; i < 35; i++)
        ck_assert_ptr_eq(s21_strrchr(buffer[i], test_char[i]), strrchr(buffer[i], test_char[i]));
     printf("[PASS]\n");
}
END_TEST
START_TEST(strspn_test) {
    printf("Testing s_21_strspn: ");
    char *buffer[] = {
        "abcde",
        "aaaaaa",
        "abrbr",
        "B",
        "A",
        "BBBB",
        "BBBBb",
        "\0abr",
        "\t\t",
        "\n\nabr",
        "\t\0\b",
        "\0\0Akba",
        "W\tf",
        "\tre",
        "ABCDEfgt"
    };
    char *test_string[] = {
        "a", "abcd", "aa", "B", "A", "b",
        "B", "\0", "\t", "\n", "r", "\0a",
        "fW", "re", "ABCDEfgt"
    };

    for (int i = 0; i < 15; i++)
        ck_assert_int_eq(s21_strspn(buffer[i], test_string[i]), strspn(buffer[i], test_string[i]));
     printf("[PASS]\n");
}
END_TEST
START_TEST(strstr_test) {
    printf("Testing s21_strstr: ");
    char *buffer[] = {
        "We are", "We are", "\t\t", "brrb", "BrBR", "\0abc", "br",
        "PointerPointer", "PointerPointer", "\n\n", "\b\0br\t", "\b\t\0"
    };

    char *testing_string[] = {
        "We are", "Weare", "\t", "brrb", "BrbR", "\0abc", "br",
        "PointerPointer", "Pointer", "\n\n", "\b\0br\t", "\b\t\0"
    };

    for (int i = 0; i < 12; i ++)
        ck_assert_ptr_eq(s21_strstr(buffer[i], testing_string[i]), strstr(buffer[i], testing_string[i]));
    printf("[PASS]\n");
}
END_TEST
START_TEST(strtok_test) {
    const char *test_strings[] = {
        "The quick,brown|fox-jumps_over.the#lazy$dog",
        "REQ^DSET^999^999^atda^d73a2681b97b4503^2.61^",
        "Thequick,brown|fox-jumps_over.the#lazy$dog",
        "^^999^999^^",
        "...###0aasdas",
        "...###0aasdas",
        "###1111\\",
        "The quick,brown|fox-jumps_over.the#lazy$dog",
        "REQ^DSET^999^999^atda^d73a2681b97b4503^2.61^",
        "=1+456",
        "1321322131456",
        "00000/.../,/\0/",
        "12344*-+-*1221",
        "%%",
        "qwe\brty",
        "ttttttttttttttttttttt",
        "token",
        "tokentokentokentokentokentokentokentoken"
    };
    const char *test_strings_upper[] = {
        " #,$-_.|",
        "999",
        "",
        "^",
        "a",
        ".",
        "1",
        "_o",
        "^",
        "=",
        "1",
        "/",
        "+",
        "%%",
        "QWE\bRTY",
        "t",
        "token",
        "token"
    };
    printf("Testing s21_strtok: ");
    char test_seq[128], test_seq21[128];
    for (int i = 0; i < 18; i++) {
        s21_strcpy(test_seq, test_strings[i]);
        s21_strcpy(test_seq21, test_strings[i]);
        char *ptr = strtok(test_seq, test_strings_upper[i]);
        char *ptr21 = s21_strtok(test_seq21, test_strings_upper[i]);
        while (ptr && ptr21) {
            ck_assert_str_eq(ptr, ptr21);
            ptr = strtok(NULL, test_strings_upper[i]);
            ptr21 = s21_strtok(NULL, test_strings_upper[i]);
        }
    }
    printf("[PASS]\n\n");
}
END_TEST

START_TEST(s21_sprintf_d) {
    printf("s21_printf tests: \n");
    printf("    d spec: ");
    char s21_buff[256];
    char buff[256];

    ck_assert_int_eq(s21_sprintf(s21_buff, "%d", 420), sprintf(buff, "%d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%hd", 420), sprintf(buff, "%hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%ld", 420l), sprintf(buff, "%ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "% d", 420), sprintf(buff, "% d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% hd", 420), sprintf(buff, "% hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% ld", 420l), sprintf(buff, "% ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "% 010d", 420), sprintf(buff, "% 010d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% .5d", 420), sprintf(buff, "% .5d", 420));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "my%d", 420), sprintf(buff, "my%d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "my%hd", 420), sprintf(buff, "my%hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "my%ld", 420l), sprintf(buff, "my%ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%5d", 420), sprintf(buff, "%5d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5hd", 420), sprintf(buff, "%5hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5ld", 420l), sprintf(buff, "%5ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "KEK%5d", 420), sprintf(buff, "KEK%5d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "KEK%5hd", 420), sprintf(buff, "KEK%5hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "KEK%5ld", 420l), sprintf(buff, "KEK%5ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%+d", 420), sprintf(buff, "%+d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+hd", 420), sprintf(buff, "%+hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+ld", 420l), sprintf(buff, "%+ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%+dMEK", 420), sprintf(buff, "%+dMEK", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+hdMEK", 420), sprintf(buff, "%+hdMEK", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+ldMEK", 420l), sprintf(buff, "%+ldMEK", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%-d", 420), sprintf(buff, "%-d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-hd", 420), sprintf(buff, "%-hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-ld", 420l), sprintf(buff, "%-ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5d", 420), sprintf(buff, "%-5d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5hd", 420), sprintf(buff, "%-5hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5ld", 420l), sprintf(buff, "%-5ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5d", 420), sprintf(buff, "%+5d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5hd", 420), sprintf(buff, "%+5hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5ld", 420l), sprintf(buff, "%+5ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%*d", 10, 420), sprintf(buff, "%*d", 10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*hd", 0, 420), sprintf(buff, "%*hd", 0, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*ld", 10, 420l), sprintf(buff, "%*ld", 10, 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*d", -10, 420), sprintf(buff, "%.*d", -10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*hd", 10, 420), sprintf(buff,  "%.*hd", 10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*ld", -10, 420l), sprintf(buff, "%.*ld", -10, 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%0d",  420), sprintf(buff, "%0d",  420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0hd", 420), sprintf(buff, "%0hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0ld",  420l), sprintf(buff, "%0ld",  420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5d",  1458), sprintf(buff, "%.5d",  1458));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5d", 1458), sprintf(buff, "%.5d", 1458));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5ld",  1458l), sprintf(buff, "%.5ld",  1458l));

    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2d", 420), sprintf(buff, "%+5.2d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2hd", 420), sprintf(buff,  "%+5.2hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2ld", 420l), sprintf(buff, "%+5.2ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2d", 420), sprintf(buff, "%-5.2d", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.3hd", 420), sprintf(buff, "%-5.3hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.3ld", 420l), sprintf(buff, "%-5.3ld", 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2d",  420), sprintf(buff, "%.2d",  420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2hd", 420), sprintf(buff, "%.2hd", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2ld",  420l), sprintf(buff, "%.2ld",  420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.*d", -10, 420), sprintf(buff, "%5.*d", -10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.*hd", 10, 420), sprintf(buff, "%5.*hd", 10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.*ld", -10, 420l), sprintf(buff, "%5.*ld", -10, 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.*d", -10, 420), sprintf(buff, "%-5.*d", -10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.*hd", 10, 420), sprintf(buff, "%-5.*hd", 10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.*ld", -10, 420l), sprintf(buff, "%-5.*ld", -10, 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.*d", -10, 420), sprintf(buff, "%+5.*d", -10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.*hd", 10, 420), sprintf(buff, "%+5.*hd", 10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.*ld", -10, 420l), sprintf(buff, "%+5.*ld", -10, 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.*d", -10, 420), sprintf(buff, "%5.*d", -10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.*hd", 10, 420), sprintf(buff, "%5.*hd", 10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.*ld", -10, 420l), sprintf(buff, "%5.*ld", -10, 420l));
    ck_assert_str_eq(s21_buff, buff);

    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.*d", -10, 420), sprintf(buff, "%+5.*d", -10, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.*hd", 10, 420), \
                     sprintf(buff, "%+5.*hd", 10, 420));  // size + width
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.*ld", -10, 420l), sprintf(buff, "%+5.*ld", -10, 420l));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_i) {
    printf("    i spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%i", -150), sprintf(buff, "%i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+i", -150), sprintf(buff, "%+i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% i", 420), sprintf(buff, "% i", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-i", -150), sprintf(buff, "%-i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5i", -150), sprintf(buff, "%5i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%i", -150), sprintf(buff, "kek%i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*i", 8, 420), sprintf(buff, "%*i", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*i", 8, 420), sprintf(buff, "%.*i", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*i", -8, 420), sprintf(buff, "%*i", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*i", -8, 420), sprintf(buff, "%.*i", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0i", -150), sprintf(buff, "%0i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5i", -150), sprintf(buff, "%.5i", -150));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2i", 100), sprintf(buff, "%5.2i", 100));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2i", 100), sprintf(buff, "%.2i", 100));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2i", 100), sprintf(buff, "%-5.2i", 100));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2i", 100), sprintf(buff, "%+5.2i", 100));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%hi", 950), sprintf(buff, "%hi", 950));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5li", 420l), sprintf(buff, "%5li", 420l));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%i %i %+i", 420, 380, 470), \
                     sprintf(buff, "%i %i %+i", 420, 380, 470));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_u) {
    printf("    u spec: ");
    char s21_buff[256];
    char buff[256];
     ck_assert_int_eq(s21_sprintf(s21_buff, "%u", 128), sprintf(buff, "%u", 128));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%-u", 128), sprintf(buff, "%-u", 128));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%5u", 128), sprintf(buff, "%5u", 128));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%05u", 128), sprintf(buff, "%05u", 128));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "kek%u", 128), sprintf(buff, "kek%u", 128));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%*u", 8, 420), sprintf(buff, "%*u", 8, 420));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%.*u", 8, 420), sprintf(buff, "%.*u", 8, 420));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%*u", -8, 420), sprintf(buff, "%*u", -8, 420));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%.*u", -8, 420), sprintf(buff, "%.*u", -8, 420));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%0u", 560), sprintf(buff, "%0u", 560));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%.5u", 560), sprintf(buff, "%.5u", 560));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%.2u", 560), sprintf(buff, "%.2u", 560));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2u", 560), sprintf(buff, "%5.2u", 560));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2u", 890), sprintf(buff, "%-5.2u", 890));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%hu", 890), sprintf(buff, "%hu", 890));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%5lu", 980lu), sprintf(buff, "%5lu", 980lu));
     ck_assert_str_eq(s21_buff, buff);
     ck_assert_int_eq(s21_sprintf(s21_buff, "%u %u %-u %5u", 420, 0u - 1u, 300, 600), \
                      sprintf(buff, "%u %u %-u %5u", 420, 0u - 1u, 300, 600));
     ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_o) {
    printf("    o spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%o", 148), sprintf(buff, "%o", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-o", 148), sprintf(buff, "%-o", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5o", 148), sprintf(buff, "%5o", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%o", 148), sprintf(buff, "kek%o", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*o", 8, 420), sprintf(buff,  "%*o", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*o", 8, 420), sprintf(buff, "%.*o", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*o", -8, 420), sprintf(buff, "%*o", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*o", -8, 420), sprintf(buff, "%.*o", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0o", 420), sprintf(buff, "%0o", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5o", 420), sprintf(buff, "%.5o", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2o", 420), sprintf(buff, "%.2o", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2o", 420), sprintf(buff, "%5.2o", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2o", 420), sprintf(buff, "%-5.2o", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%ho", 420), sprintf(buff, "%ho", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5lo", 420lu), sprintf(buff, "%5lo", 420lu));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*o", 10, 250), sprintf(buff, "%#.*o", 10, 250));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*ho", -10, 1050), sprintf(buff, "%#.*ho", -10, 1050));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*o", 100, 1050), sprintf(buff, "%#.*o", 100, 1050));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%o %#o %-o %5o", 420, 1420, 300, 600), \
                     sprintf(buff, "%o %#o %-o %5o", 420, 1420, 300, 600));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_x) {
    printf("    x spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%x", 148), sprintf(buff, "%x", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-x", 148), sprintf(buff, "%-x", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5x", 148), sprintf(buff, "%5x", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%x", 148), sprintf(buff, "kek%x", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*x", 8, 420), sprintf(buff,  "%*x", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*x", 8, 420), sprintf(buff, "%.*x", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*x", -8, 420), sprintf(buff, "%*x", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*x", -8, 420), sprintf(buff, "%.*x", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0x", 420), sprintf(buff, "%0x", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5x", 420), sprintf(buff, "%.5x", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2x", 420), sprintf(buff, "%.2x", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2x", 420), sprintf(buff, "%5.2x", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2x", 721082), sprintf(buff, "%5.2x", 721082));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2x", 420), sprintf(buff, "%-5.2x", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%hx", 420), sprintf(buff, "%hx", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5lx", 420lu), sprintf(buff, "%5lx", 420lu));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*x", 10, 250), sprintf(buff, "%#.*x", 10, 250));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*hx", -10, 1050), sprintf(buff, "%#.*hx", -10, 1050));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*x", 100, 1050), sprintf(buff, "%#.*x", 100, 1050));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%x %#x %-x %5x", 420, 1420, 300, 600), \
                     sprintf(buff, "%x %#x %-x %5x", 420, 1420, 300, 600));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_X) {
    printf("    X spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%X", 148), sprintf(buff, "%X", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-X", 148), sprintf(buff, "%-X", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5X", 148), sprintf(buff, "%5X", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%x", 148), sprintf(buff, "kek%X", 148));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*X", 8, 420), sprintf(buff, "%*X", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*X", 8, 420), sprintf(buff, "%.*X", 8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*X", -8, 420), sprintf(buff, "%*X", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*X", -8, 420), sprintf(buff, "%.*X", -8, 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0X", 420), sprintf(buff, "%0X", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2X", 912145), sprintf(buff, "%5.2X", 912145));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5X", 420), sprintf(buff, "%.5X", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.2X", 420), sprintf(buff, "%.2X", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2X", 420), sprintf(buff, "%5.2X", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2X", 420), sprintf(buff, "%-5.2X", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%hX", 420), sprintf(buff, "%hX", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5lX", 420), sprintf(buff, "%5X", 420));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*X", 10, 250), sprintf(buff, "%#.*X", 10, 250));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*hX", -10, 1050), sprintf(buff, "%#.*hX", -10, 1050));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*X", 100, 1050), sprintf(buff, "%#.*X", 100, 1050));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%X %#X %-X %5X", 420, 1420, 300, 600), \
                     sprintf(buff, "%X %#X %-X %5X", 420, 1420, 300, 600));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_c) {
    printf("    c spec: ");
    char s21_buff[256];
    char buff[256];
    sprintf(buff, "qwe");
    for (int i = 33; i < 127; i++) {
        ck_assert_int_eq(s21_sprintf(s21_buff, "%c", i), sprintf(buff, "%c", i));
        ck_assert_str_eq(s21_buff, buff);
    }
    ck_assert_int_eq(s21_sprintf(s21_buff, "%%"), sprintf(buff, "%%"));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%10c", 'g'), sprintf(buff, "%10c", 'g'));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%c", -1), sprintf(buff, "%c", -1));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-10c", 'c'), sprintf(buff, "%-10c", 'c'));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%lc", 'o'), sprintf(buff, "%lc", 'o'));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%lc", 130), sprintf(buff, "%lc", 130));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%lc", 255), sprintf(buff, "%lc", 255));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%lc", 420), sprintf(buff, "%lc", 420));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_g) {
    printf("    g spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%g", 148.228), sprintf(buff, "%g", 148.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%g", 148.0), sprintf(buff, "%g", 148.0));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+g", 14.228), sprintf(buff, "%+g", 14.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-g", 148.228), sprintf(buff, "%-g", 148.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5g", 148.228), sprintf(buff, "%5g", 148.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%g", 148.228), sprintf(buff, "kek%g", 148.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*g", 8, 420.228), sprintf(buff,  "%*g", 8, 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*g", 8, 420.228), sprintf(buff, "%.*g", 8, 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*g", -8, 420.228), sprintf(buff, "%*g", -8, 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.0g", 0.00089), sprintf(buff, "%.0g", 0.00089));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*g", -8, 420.228), sprintf(buff, "%.*g", -8, 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0g", 420.228), sprintf(buff, "%0g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5g", 420.228), sprintf(buff, "%.5g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2g", 420.228), sprintf(buff, "%0.2g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2g", 420.228), sprintf(buff, "%5.2g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2g", 420.228), sprintf(buff, "%0.2g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2g", 420.228), sprintf(buff, "%-5.2g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2g", 420.228), sprintf(buff, "%+5.2g", 420.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*g", 10, 250.228), sprintf(buff, "%#.*g", 10, 250.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*Lg", -10, 1050.228l), \
                     sprintf(buff, "%#.*Lg", -10, 1050.228l));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*g", 19, 1050.228), sprintf(buff, "%#.*g", 19, 1050.228));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%g %+g %-g %5g", 420.1450, 1420.1450, 300.1450, 600.1450), \
                     sprintf(buff,  "%g %+g %-g %5g", 420.1450, 1420.1450, 300.1450, 600.1450));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_G) {
    printf("    G spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%G", 148.25612), sprintf(buff, "%G", 148.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+G", 148.25612), sprintf(buff, "%+G", 148.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-G", 148.25612), sprintf(buff, "%-G", 148.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5G", 148.25612), sprintf(buff, "%5G", 148.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%G", 148.25612), sprintf(buff, "kek%G", 148.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*G", 8, 420.25612), sprintf(buff, "%*G", 8, 420.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*G", 8, 420.25612), sprintf(buff, "%.*G", 8, 420.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*G", -8, 420.25612), sprintf(buff,  "%*G", -8, 420.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*G", -8, 420.25612), sprintf(buff, "%.*G", -8, 420.25612));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0G", 420.1214), sprintf(buff, "%0G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5G", 420.1214), sprintf(buff, "%.5G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.0G", 0.00089), sprintf(buff, "%.0G", 0.00089));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2G", 420.1214), sprintf(buff, "%0.2G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2G", 420.1214), sprintf(buff, "%5.2G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2G", 420.1214), sprintf(buff, "%0.2G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2G", 420.1214), sprintf(buff, "%-5.2G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2G", 420.1214), sprintf(buff, "%+5.2G", 420.1214));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+G", 50.1470), sprintf(buff, "%+G", 50.1470));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-G", 20.1470), sprintf(buff, "%-G", 20.1470));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*G", 10, 250.1470), sprintf(buff,  "%#.*G", 10, 250.1470));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*LG", -10, 1050.1470l), \
                     sprintf(buff, "%#.*LG", -10, 1050.1470l));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*G", 19, 1050.1470), sprintf(buff, "%#.*G", 19, 1050.1470));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%G %+G %-G %5G", 420.12, 1420.12, 300.12, 600.12), \
                     sprintf(buff, "%G %+G %-G %5G", 420.12, 1420.12, 300.12, 600.12));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_s) {
    printf("    s spec: ");
    char s21_buff[256];
    char buff[256];
    char *test_strings[]= {
         "xyz",
        "@",
        "nothing",
        "-2-10",
        "\n\b\t",
        "\n\n\n",
        "s",
        "n0thing",
        "nothingx2",
        "empty",
        "rty",
        "zxcvbn",
        "asd",
        "%",
        "\t\t",
        "\0",
        "b",
        "\0abcd",
        "\nabd",
        "\b",
        "\v",
        "ab\v\0",
        NULL
    };

    for (int i = 0; i < 23; i++) {
        ck_assert_int_eq(sprintf(buff, "%s", test_strings[i]), s21_sprintf(s21_buff, "%s", test_strings[i]));
        ck_assert_str_eq(buff, s21_buff);
    }
    ck_assert_int_eq(sprintf(buff, "%20s", "string"), s21_sprintf(s21_buff, "%20s", "string"));
    ck_assert_str_eq(buff, s21_buff);
    ck_assert_int_eq(sprintf(buff, "%-20s", "string"), s21_sprintf(s21_buff, "%-20s", "string"));
    ck_assert_str_eq(buff, s21_buff);
    ck_assert_int_eq(sprintf(buff, "%20.3s", "string"), s21_sprintf(s21_buff, "%20.3s", "string"));
    ck_assert_str_eq(buff, s21_buff);
    ck_assert_int_eq(sprintf(buff, "%ls", L"string"), s21_sprintf(s21_buff, "%ls", L"string"));
    ck_assert_str_eq(buff, s21_buff);
    wchar_t inv_wstr[] = {'s', 't', 'r', 130, 255, 4400, 'n', 'o', 'r', 'm', 0};
    ck_assert_int_eq(sprintf(buff, "%ls", inv_wstr), s21_sprintf(s21_buff, "%ls", inv_wstr));
    ck_assert_str_eq(buff, s21_buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_f) {
    printf("    f spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%f", 14.4), sprintf(buff,  "%f", 14.4));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%f", 14.0), sprintf(buff,  "%f", 14.0));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% f", 45.47), sprintf(buff,  "% f", 45.47));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% .f", 45.47), sprintf(buff,  "% .f", 45.47));
    ck_assert_str_eq(s21_buff, buff);
    /*ck_assert_int_eq(s21_sprintf(s21_buff, "%f", NAN), sprintf(buff,  "%f", NAN));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%f", INFINITY), sprintf(buff,  "%f", INFINITY));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%f", -INFINITY), sprintf(buff,  "%f", -INFINITY));
    ck_assert_str_eq(s21_buff, buff);*/
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+f", 148.64), sprintf(buff,  "%+f", 148.64));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-f", 148.765), sprintf(buff,  "%-f", 148.765));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5f", 148.871), sprintf(buff,  "%5f", 148.871));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%f", -3.27651), sprintf(buff,  "kek%f", -3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*f", 8, 3.27651), sprintf(buff,  "%*f", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*f", 8, 3.27651), sprintf(buff,  "%.*f", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*f", -8, 176435.213), sprintf(buff,  "%*f", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%015f", 0.69089), sprintf(buff, "%015f", 0.69089));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% f", 148.871), sprintf(buff, "% f", 148.871));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%f", 0.00089), sprintf(buff, "%f", 0.00089));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*f", -8,  176435.213), sprintf(buff,  "%.*f", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0f", 420.89), sprintf(buff,  "%0f", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5f", 420.89), sprintf(buff, "%.5f", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2f", 420.89), sprintf(buff, "%0.2f", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2f", 420.89), sprintf(buff,  "%5.2f", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2f", 420.89), sprintf(buff,  "%0.2f", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2f", 420.89), sprintf(buff,  "%-5.2f", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2f", 4420.89), sprintf(buff, "%+5.2f", 4420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*f", 10, 2420.89), sprintf(buff,  "%#.*f", 10, 2420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*Lf", -10, 10420.89l), \
                     sprintf(buff, "%#.*Lf", -10, 10420.89l));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*f", 19, 1050.25), sprintf(buff,  "%#.*f", 19, 1050.25));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%f %+f %-f %5f", 420.0, 3.1415, 300.25, 600.25), \
                     sprintf(buff, "%f %+f %-f %5f", 420.0, 3.1415, 300.25, 600.25));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_F) {
    printf("    F spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%F", 14.4), sprintf(buff, "%F", 14.4));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+F", 148.64), sprintf(buff, "%+F", 148.64));
    ck_assert_str_eq(s21_buff, buff);
    /*ck_assert_int_eq(s21_sprintf(s21_buff, "%F", NAN), sprintf(buff,  "%F", NAN));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%F", INFINITY), sprintf(buff,  "%F", INFINITY));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%F", -INFINITY), sprintf(buff,  "%F", -INFINITY));
    ck_assert_str_eq(s21_buff, buff);*/
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-F", 148.765), sprintf(buff, "%-F", 148.765));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5F", 148.871), sprintf(buff, "%5F", 148.871));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% F", 148.871), sprintf(buff, "% F", 148.871));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%F", -3.27651), sprintf(buff, "kek%F", -3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*F", 8, 3.27651), sprintf(buff, "%*F", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*F", 8, 3.27651), sprintf(buff, "%.*F", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*F", -8, 176435.213), sprintf(buff, "%*F", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*F", -8,  176435.213), sprintf(buff, "%.*F", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%010F", 420.89), sprintf(buff, "%010F", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%015F", 0.69089), sprintf(buff, "%015F", 0.69089));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%F", 0.00089), sprintf(buff, "%F", 0.00089));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5F", 420.89), sprintf(buff, "%.5F", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2F", 420.89), sprintf(buff, "%0.2F", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2F", 420.89), sprintf(buff, "%5.2F", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2F", 420.89), sprintf(buff, "%0.2F", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2F", 420.89), sprintf(buff, "%-5.2F", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2F", 4420.89), sprintf(buff, "%+5.2F", 4420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*F", 10, 2420.89), \
                     sprintf(buff, "%#.*F", 10, 2420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*LF", -10, 10420.89l), \
                     sprintf(buff, "%#.*LF", -10, 10420.89l));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*F", 16, 1050.256), \
                     sprintf(buff, "%#.*F", 16, 1050.256));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%F %+F %-F %5F", 420.0, 3.1415, 300.0, 600.256), \
                     sprintf(buff, "%F %+F %-F %5F", 420.0, 3.1415, 300.0, 600.256));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_n) {
    printf("    n spec: ");
    char s_21[256];
    char buff[256];
    char *test[] = {"ret%n", "b\b%nr", "%nreti", "rreiriotieri%n", "rreiri%notieri"};
    int s_21_num = 0;
    int buff_num = 0;
    for (int i =0 ; i < 5; i++) {
        ck_assert_int_eq(sprintf(buff, test[i], &buff_num), \
                         s21_sprintf(s_21, test[i], &s_21_num));
        ck_assert_int_eq(buff_num, s_21_num);
    }
    ck_assert_int_eq(sprintf(buff, "%d%n", -2147483647, &buff_num), \
                     s21_sprintf(s_21, "%d%n", -2147483647, &s_21_num));
    ck_assert_int_eq(buff_num, s_21_num);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_p) {
    printf("    p spec: ");
    char buff[256];
    char s_21[256];

    int n[16];
    int adr_c = 16;
    for (int i = 0; i < adr_c; i++) {
        ck_assert_int_eq(sprintf(buff, "%p",  &n[i]), s21_sprintf(s_21, "%p",  &n[i]));
        ck_assert_str_eq(buff, s_21);
    }
    for (int i = 0; i < adr_c; i++) {
        ck_assert_int_eq(sprintf(buff, "%32p",  &n[i]), s21_sprintf(s_21, "%32p",  &n[i]));
        ck_assert_str_eq(buff, s_21);
    }
    for (int i = 0; i < adr_c; i++) {
        ck_assert_int_eq(sprintf(buff, "%-32p",  &n[i]), s21_sprintf(s_21, "%-32p",  &n[i]));
        ck_assert_str_eq(buff, s_21);
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_e) {
    printf("    e spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%e", 14.4), sprintf(buff, "%e", 14.4));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%e", 14.0), sprintf(buff, "%e", 14.0));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "% e", 14.4), sprintf(buff, "% e", 14.4));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+e", 148.64), sprintf(buff, "%+e", 148.64));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-e", 148.765), sprintf(buff, "%-e", 148.765));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5e", 148.871), sprintf(buff, "%5e", 148.871));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%e", 3.27651), sprintf(buff, "kek%e", 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*e", 8, 3.27651), sprintf(buff, "%*e", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*e", 8, 3.27651), sprintf(buff, "%.*e", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*e", -8, 176435.213), sprintf(buff,  "%*e", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*e", -8,  176435.213), sprintf(buff, "%.*e", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0e", 420.89), sprintf(buff, "%0e", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5e", 420.89), sprintf(buff, "%.5e", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2e", 420.89), sprintf(buff, "%0.2e", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2e", 420.89), sprintf(buff, "%5.2e", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2e", 420.89), sprintf(buff, "%0.2e", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2e", 420.89), sprintf(buff, "%-5.2e", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2e", 4420.89), sprintf(buff, "%+5.2e", 4420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*e", 10, 2420.89), sprintf(buff, "%#.*e", 10, 2420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*e", -10, 10420.89), sprintf(buff, "%#.*e", -10, 10420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*e", 10, 1050.255), sprintf(buff, "%#.*e", 10, 1050.255));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%e %+e %-e %5e", 420.255, 3.1415, 300.255, 600.255), \
                                 sprintf(buff, "%e %+e %-e %5e", 420.255, 3.1415, 300.255, 600.255));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%12.15e", 2.731), sprintf(buff, "%12.15e", 2.731));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sprintf_E) {
    printf("    E spec: ");
    char s21_buff[256];
    char buff[256];
    ck_assert_int_eq(s21_sprintf(s21_buff, "%E", 14.4), sprintf(buff, "%E", 14.4));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+E", 148.64), sprintf(buff, "%+E", 148.64));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-E", 148.765), sprintf(buff, "%-E", 148.765));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5E", 148.871), sprintf(buff, "%5E", 148.871));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "kek%E", 3.27651), sprintf(buff, "kek%E", 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*E", 8, 3.27651), sprintf(buff,  "%*E", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*E", 8, 3.27651), sprintf(buff, "%.*E", 8, 3.27651));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%*E", -8, 176435.213), sprintf(buff,  "%*E", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.*E", -8,  176435.213), sprintf(buff, "%.*E", -8,  176435.213));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0E", 420.89), sprintf(buff, "%0E", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%.5E", 420.89), sprintf(buff, "%.5E", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2E", 420.89), sprintf(buff, "%0.2E", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%5.2E", 420.89), sprintf(buff, "%5.2E", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%0.2E", 420.89), sprintf(buff, "%0.2E", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%-5.2E", 420.89), sprintf(buff, "%-5.2E", 420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%+5.2E", 4420.89), sprintf(buff, "%+5.2E", 4420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*E", 10, 2420.89), sprintf(buff, "%#.*E", 10, 2420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*E", -10, 10420.89), sprintf(buff, "%#.*E", -10, 10420.89));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%#.*E", 10, 1050.12), sprintf(buff, "%#.*E", 10, 1050.12));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%E %+E %-E %5E", 420.12, 3.1415, 300.12, 600.12), \
                     sprintf(buff, "%E %+E %-E %5E", 420.12, 3.1415, 300.12, 600.12));
    ck_assert_str_eq(s21_buff, buff);
    ck_assert_int_eq(s21_sprintf(s21_buff, "%12.15lE", 2.731), sprintf(buff, "%12.15lE", 2.731));
    ck_assert_str_eq(s21_buff, buff);
    printf("[PASS]\n");
}
END_TEST

START_TEST(s21_sscanf_d) {
    short hd, hd21;
    int d, d21, i, i21;
    long int ld, ld21;
    printf("s21_scanf tests: \n");
    printf("    d spec: ");
    ck_assert_int_eq(s21_sscanf("47", "%d", &d21), sscanf("47", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("\b47", "%d", &d21), sscanf("\b47", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("\t47", "%d", &d21), sscanf("\t47", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("-47", "%d", &d21), sscanf("-47", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("+47", "%d", &d21), sscanf("+47", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("+-47", "%d", &d21), sscanf("+-47", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("0", "%d", &d21), sscanf("0", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("2147483647", "%d", &d21), sscanf("2147483647", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("-2147483648", "%d", &d21), sscanf("-2147483648", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("21474840009", "%d", &d21), sscanf("21474840009", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("-21474836499", "%d", &d21), sscanf("-21474836499", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("47", "%hd", &hd21), sscanf("47", "%hd", &hd));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("47000000", "%ld", &ld21), sscanf("47000000", "%ld", &ld));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("4755", "%2d", &d21), sscanf("4755", "%2d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("47 55", "%*d %d", &d21), sscanf("47 55", "%*d %d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("c418", "%d", &d21), sscanf("c418", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("47.0", "%d", &d21), sscanf("47.0", "%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("c418", "%*c%d", &d21), sscanf("c418", "%*c%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("genius 418", "%*s%d", &d21), sscanf("genius 418", "%*s%d", &d));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(s21_sscanf("47.418", "%d%*c%d", &d21, &i21), sscanf("47.418", "%d%*c%d", &d, &i));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(i, i21);
    ck_assert_int_eq(s21_sscanf("47 418", "%d%d", &d21, &i21), sscanf("47 418", "%d%d", &d, &i));
    ck_assert_int_eq(d, d21);
    ck_assert_int_eq(i, i21);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_u) {
    unsigned short hu, hu21;
    unsigned int u, u21, ui, ui21;
    unsigned long int lu, lu21;
    printf("    u spec: ");
    ck_assert_int_eq(s21_sscanf("47", "%u", &u21), sscanf("47", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-47", "%u", &u21), sscanf("-47", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+47", "%u", &u21), sscanf("+47", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+-47", "%u", &u21), sscanf("+-47", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0", "%u", &u21), sscanf("0", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4294967295", "%u", &u21), sscanf("4294967295", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4294967296", "%u", &u21), sscanf("4294967296", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-2147483648", "%u", &u21), sscanf("-2147483648", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("21474840009", "%u", &u21), sscanf("21474840009", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-21474836499", "%u", &u21), sscanf("-21474836499", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47", "%hu", &hu21), sscanf("47", "%hu", &hu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47000000", "%lu", &lu21), sscanf("47000000", "%lu", &lu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4755", "%2u", &u21), sscanf("4755", "%2u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47 55", "%*u %u", &u21), sscanf("47 55", "%*u %u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%u", &u21), sscanf("c418", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.0", "%u", &u21), sscanf("47.0", "%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%*c%u", &u21), sscanf("c418", "%*c%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("genius 418", "%*s%u", &u21), sscanf("genius 418", "%*s%u", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.418", "%u%*c%u", &u21, &ui21), sscanf("47.418", "%u%*c%u", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    ck_assert_int_eq(s21_sscanf("47 418", "%u%u", &u21, &ui21), sscanf("47 418", "%u%u", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_o) {
    unsigned short hu, hu21;
    unsigned int u, u21, ui, ui21;
    unsigned long int lu, lu21;
    printf("    o spec: ");
    ck_assert_int_eq(s21_sscanf("47", "%o", &u21), sscanf("47", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-47", "%o", &u21), sscanf("-47", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+47", "%o", &u21), sscanf("+47", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+-47", "%o", &u21), sscanf("+-47", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0", "%o", &u21), sscanf("0", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4294967295", "%o", &u21), sscanf("4294967295", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("37777777777", "%o", &u21), sscanf("37777777777", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("40000000000", "%o", &u21), sscanf("40000000000", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("088777", "%o", &u21), sscanf("088777", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-2147483648", "%o", &u21), sscanf("-2147483648", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47", "%ho", &hu21), sscanf("47", "%ho", &hu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47000000", "%lo", &lu21), sscanf("47000000", "%lo", &lu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4755", "%2o", &u21), sscanf("4755", "%2o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47 55", "%*o %o", &u21), sscanf("47 55", "%*o %o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%o", &u21), sscanf("c418", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.0", "%o", &u21), sscanf("47.0", "%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%*c%o", &u21), sscanf("c418", "%*c%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("genius 418", "%*s%o", &u21), sscanf("genius 418", "%*s%o", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.418", "%o%*c%o", &u21, &ui21), sscanf("47.418", "%o%*c%o", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    ck_assert_int_eq(s21_sscanf("47 418", "%o%o", &u21, &ui21), sscanf("47 418", "%o%o", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_x) {
    unsigned short hu, hu21;
    unsigned int u, u21, ui, ui21;
    unsigned long int lu, lu21;
    printf("    x spec: ");
    ck_assert_int_eq(s21_sscanf("47", "%x", &u21), sscanf("47", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-47", "%x", &u21), sscanf("-47", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+47", "%x", &u21), sscanf("+47", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0XFFFFFFFF", "%x", &u21), sscanf("0XFFFFFFFF", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0x100000000", "%x", &u21), sscanf("0x100000000", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+-47", "%x", &u21), sscanf("+-47", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0", "%x", &u21), sscanf("0", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("BOOBA", "%x", &u21), sscanf("BOOBA", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("AbObA", "%x", &u21), sscanf("AbObA", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0xABCDEF", "%x", &u21), sscanf("0xABCDEF", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0Xabcdef", "%x", &u21), sscanf("0Xabcdef", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("amogus", "%x", &u21), sscanf("amogus", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4294967295", "%x", &u21), sscanf("4294967295", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-21474836499", "%x", &u21), sscanf("-21474836499", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47", "%hx", &hu21), sscanf("47", "%hx", &hu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0xFFFFFFFFFFFFFFFF", "%lx", &lu21), \
                     sscanf("0xFFFFFFFFFFFFFFFF", "%lx", &lu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4755", "%2x", &u21), sscanf("4755", "%2x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47 55", "%*x %x", &u21), sscanf("47 55", "%*x %x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%x", &u21), sscanf("c418", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.0", "%x", &u21), sscanf("47.0", "%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%*c%x", &u21), sscanf("c418", "%*c%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("genius 418", "%*s%x", &u21), sscanf("genius 418", "%*s%x", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.418", "%x%*c%x", &u21, &ui21), sscanf("47.418", "%x%*c%x", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    ck_assert_int_eq(s21_sscanf("47 418", "%x%x", &u21, &ui21), sscanf("47 418", "%x%x", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_X) {
    unsigned short hu, hu21;
    unsigned int u, u21, ui, ui21;
    unsigned long int lu, lu21;
    printf("    X spec: ");
    ck_assert_int_eq(s21_sscanf("47", "%X", &u21), sscanf("47", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-47", "%X", &u21), sscanf("-47", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+47", "%X", &u21), sscanf("+47", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0XFFFFFFFF", "%X", &u21), sscanf("0XFFFFFFFF", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0x100000000", "%X", &u21), sscanf("0x100000000", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("+-47", "%X", &u21), sscanf("+-47", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0", "%X", &u21), sscanf("0", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("BOOBA", "%X", &u21), sscanf("BOOBA", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("AbObA", "%X", &u21), sscanf("AbObA", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0xABCDEF", "%X", &u21), sscanf("0xABCDEF", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0Xabcdef", "%X", &u21), sscanf("0Xabcdef", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("amogus", "%X", &u21), sscanf("amogus", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4294967295", "%X", &u21), sscanf("4294967295", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("-21474836499", "%X", &u21), sscanf("-21474836499", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47", "%hX", &hu21), sscanf("47", "%hX", &hu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("0xFFFFFFFFFFFFFFFF", "%lX", &lu21), \
                     sscanf("0xFFFFFFFFFFFFFFFF", "%lX", &lu));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("4755", "%2X", &u21), sscanf("4755", "%2X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47 55", "%*X %X", &u21), sscanf("47 55", "%*X %X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%X", &u21), sscanf("c418", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.0", "%X", &u21), sscanf("47.0", "%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("c418", "%*c%X", &u21), sscanf("c418", "%*c%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("genius 418", "%*s%X", &u21), sscanf("genius 418", "%*s%X", &u));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(s21_sscanf("47.418", "%X%*c%X", &u21, &ui21), sscanf("47.418", "%X%*c%X", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    ck_assert_int_eq(s21_sscanf("47 418", "%X%X", &u21, &ui21), sscanf("47 418", "%X%X", &u, &ui));
    ck_assert_int_eq(u, u21);
    ck_assert_int_eq(ui, ui21);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_fFgGeE) {
    float f, f21;
    double lf, lf21;
    long double Lf, Lf21;
    printf("    fFgGeE specs: ");
    ck_assert_int_eq(s21_sscanf("420.69", "%f", &f21), sscanf("420.69", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("-420.69", "%f", &f21), sscanf("-420.69", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.0", "%f", &f21), sscanf("420.0", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("42.6921", "%5f", &f21), sscanf("42.6921", "%5f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420", "%f", &f21), sscanf("420", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.69", "%*3f%*c%f", &f21), sscanf("420.69", "%*3f%*c%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("2.28e5", "%f", &f21), sscanf("2.28e5", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("2.28e+5", "%f", &f21), sscanf("2.28e+5", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("2.28e-5", "%f", &f21), sscanf("2.28e-5", "%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("2.28e-15", "%lf", &lf21), sscanf("2.28e-15", "%lf", &lf));
    ck_assert_float_eq(lf, lf21);
    ck_assert_int_eq(s21_sscanf("2.28e+15", "%lf", &lf21), sscanf("2.28e+15", "%lf", &lf));
    ck_assert_double_eq(lf, lf21);
    ck_assert_int_eq(s21_sscanf("0.000000045", "%Lf", &Lf21), sscanf("0.000000045", "%Lf", &Lf));
    ck_assert_double_eq(Lf, Lf21);
    ck_assert_int_eq(s21_sscanf("2.28e-5 3.54", "%*f%f", &f21), \
                     sscanf("2.28e-5 3.54", "%*f%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("3.54 2.28e-5", "%*f%f", &f21), \
                     sscanf("3.54 2.28e-5", "%*f%f", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.69", "%F", &f21), sscanf("420.69", "%F", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.69", "%g", &f21), sscanf("420.69", "%g", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.69", "%G", &f21), sscanf("420.69", "%G", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.69", "%e", &f21), sscanf("420.69", "%e", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("420.69", "%E", &f21), sscanf("420.69", "%E", &f));
    ck_assert_double_eq(f, f21);
    ck_assert_int_eq(s21_sscanf("nan", "%f", &f21), sscanf("nan", "%f", &f));
    ck_assert_int_eq(s21_sscanf("INF", "%f", &f21), sscanf("INF", "%f", &f));
    ck_assert_int_eq(s21_sscanf("-iNf", "%f", &f21), sscanf("-iNf", "%f", &f));
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_p) {
    printf("    p spec: ");
    int p[64];
    char p_str[64][64];
    int* in[64];
    int* in21[64];
    for (int i = 0; i < 64; i++) {
        p[i] = i;
        s21_sprintf(p_str[i], "%p", &p[i]);
        ck_assert_int_eq(s21_sscanf(p_str[i], "%p", &in21[i]), sscanf(p_str[i], "%p", &in[i]));
        ck_assert_ptr_eq(in[i], in21[i]);
        ck_assert_int_eq(*in[i], *in21[i]);
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_n) {
    printf("    n spec: ");
    int s21_num = 0, d21;
    int buff_num = 0, d;
    ck_assert_int_eq(sscanf("-2147483648", "%d%n", &d, &buff_num), \
                     s21_sscanf("-2147483648", "%d%n", &d21, &s21_num));
    ck_assert_int_eq(buff_num, s21_num);
    ck_assert_int_eq(sscanf("-2147483648", "%4d%n%4d", &d, &buff_num, &d), \
                     s21_sscanf("-2147483648", "%4d%n%4d", &d21, &s21_num, &d21));
    ck_assert_int_eq(buff_num, s21_num);
    ck_assert_int_eq(sscanf("     %n", "%n", &buff_num), \
                     s21_sscanf("     %n", "%n", &s21_num));
    ck_assert_int_eq(buff_num, s21_num);
    ck_assert_int_eq(sscanf("%n      ", "%n", &buff_num), \
                     s21_sscanf("%n      ", "%n", &s21_num));
    ck_assert_int_eq(buff_num, s21_num);
    ck_assert_int_eq(sscanf("string", "%*s%n", &buff_num), \
                     s21_sscanf("string", "%*s%n", &s21_num));
    ck_assert_int_eq(buff_num, s21_num);
    ck_assert_int_eq(sscanf("string", "%n%*s", &buff_num), \
                     s21_sscanf("string", "%n%*s", &s21_num));
    ck_assert_int_eq(buff_num, s21_num);
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_c) {
    printf("    c spec: ");
    char c = 0, c21 = 0;
    wchar_t wc = 0, wc21 = 0;
    char symbols[128], *ptr = symbols;
    symbols[0] = -2;
    for (int i = 1; i < 128; i++)
        symbols[i] = i;
    symbols[127] = 0;
    for (int i = 0; i < 128; i++, ptr++) {
        ck_assert_int_eq(sscanf(ptr, "%c", &c), s21_sscanf(ptr, "%c", &c21));
        ck_assert_int_eq(c, c21);
        ck_assert_int_eq(sscanf(ptr, "%lc", &wc), s21_sscanf(ptr, "%lc", &wc21));
        ck_assert_int_eq(wc, wc21);
    }
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_sscanf_s) {
    printf("    s spec: ");
    char str[1024], str21[1024];
    wchar_t wstr[1024], wstr21[1024];
    ck_assert_int_eq(sscanf("string", "%s", str), s21_sscanf("string", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("str str", "%s", str), s21_sscanf("str str", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("striiiiiiiiiing", "%s", str), s21_sscanf("striiiiiiiiiing", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("str0str", "%s", str), s21_sscanf("str0str", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("123456789", "%s", str), s21_sscanf("123456789", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("str str", "%3s", str), s21_sscanf("str str", "%3s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("str rts", "%3s%s", str, str), s21_sscanf("str rts", "%3s%s", str21, str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("str rts", "%*3s%s", str), s21_sscanf("str rts", "%*3s%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("str\0ing", "%s", str), s21_sscanf("str\0ing", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("\0string", "%s", str), s21_sscanf("\0string", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("long striiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", "%s", str), \
                    s21_sscanf("long striiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", "%s", str21));
    ck_assert_str_eq(str, str21);
    ck_assert_int_eq(sscanf("", "%s", str), s21_sscanf("", "%s", str21));
    ck_assert_int_eq(sscanf("long striiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", "%ls", wstr), \
                    s21_sscanf("long striiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", "%ls", wstr21));
    ck_assert_str_eq(str, str21);
    printf("[PASS]\n");
}
END_TEST

START_TEST(s21_to_upper_test) {
    printf("\nTesting s21_to_upper: ");
    char *test_string[] = {
        "abcde",
        "aaaaaa",
        "abrbr",
        "B",
        "A",
        "BBBB",
        "BBBBb",
        "abr",
        "QW",
        "abR",
        "b",
        "Akba",
        "Wf",
        "re",
        "ABCDEfgt"
    };
    char *correct[] = {
        "ABCDE", "AAAAAA", "ABRBR", "B", "A", "BBBB", "BBBBB",
        "ABR", "QW", "ABR", "B", "AKBA", "WF", "RE", "ABCDEFGT"
    };

    s21_size_t i;
    for (i = 0; i < 15; i++) {
        char *buff = s21_to_upper(test_string[i]);
        ck_assert_str_eq(buff, correct[i]);
        if (buff != NULL)
            free(buff);
    }
    ck_assert_ptr_null(s21_to_upper(NULL));
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_to_lower_test) {
    printf("Testing s21_to_lower: ");
    char *test_string[] = {
    "abcde",
    "AAAA",
    "AEE",
    "B",
    "A",
    "BBBB",
    "BBBBb",
    "abr",
    "QW",
    "abr",
    "b",
    "Akba",
    "Wf",
    "re",
    "ABCDEfgt"
    };
    s21_size_t i;
    char *correct[] = {
        "abcde", "aaaa", "aee", "b", "a", "bbbb", "bbbbb",
        "abr", "qw", "abr", "b", "akba", "wf", "re", "abcdefgt"
    };

    for (i = 0; i < 15; i++) {
        char *buff = s21_to_lower(test_string[i]);
        ck_assert_str_eq(buff, correct[i]);
        free(buff);
    }
    ck_assert_ptr_null(s21_to_lower(NULL));
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_insert_test) {
    printf("Testing s21_insert: ");
    const char* test_strings[] = {
        "abcde",
        "@@@@@@@",
        "",
        "1234",
        "\t\b\n",
        "\n\n\n",
        "\b",
        "\0",
        "\0\0\0",
        "\0qwerty",
        "qwe\0rty",
        "qwe\nrty",
        "qwe\brty",
        "%%",
    };
    char* result_strings[] = {
        "strabcde",
        "str@@@@@@@",
        "str",
        "str1234",
        "str\t\b\n",
        "str\n\n\n",
        "str\b",
        "str\0",
        "str\0\0\0",
        "str\0qwerty",
        "strqwe\0rty",
        "strqwe\nrty",
        "strqwe\brty",
        "str%%",
    };
    char* buf;
    for (int i = 0; i < 14; i++) {
        buf = s21_insert(test_strings[i], "str", 0);
        ck_assert_str_eq(buf, result_strings[i]);
        free(buf);
    }
    buf = s21_insert("str", "str", 2);
    ck_assert_str_eq(buf, "ststrr");
    free(buf);
    buf = s21_insert("str", "str", 3);
    ck_assert_str_eq(buf, "strstr");
    free(buf);
    buf = s21_insert("strstr", "\0", 3);
    ck_assert_str_eq(buf, "strstr");
    free(buf);
    ck_assert_ptr_null(s21_insert(NULL, "qwe", 0));
    ck_assert_ptr_null(s21_insert("qwe", NULL, 0));
    ck_assert_ptr_null(s21_insert("qww", "loooooooong", 100));
    printf("[PASS]\n");
}
END_TEST
START_TEST(s21_trim_test) {
    printf("Testing s21_trim: ");
    char *test_string[] = {"**Abobo**", "**Abobo**", "\0some", "so\0me"};
    char *correct_res[] = {"Abobo", "", "", "so"};
    char *trim_sym[] = {"*", "**Abobo**", "some", "l"};

    for (int i = 0; i < 4; i++) {
        char *new_string = s21_trim(test_string[i], trim_sym[i]);
        ck_assert_str_eq(new_string, correct_res[i]);
        free(new_string);
    }
    char *new_string = s21_trim("   sdgfd   ", NULL);
    ck_assert_ptr_null(s21_trim(NULL, " "));
    ck_assert_str_eq(new_string, "sdgfd");
    ck_assert_ptr_null(s21_trim(NULL, NULL));
    free(new_string);
    printf("[PASS]\n");
}
END_TEST

Suite *test_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("String test");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, memchr_test);
    tcase_add_test(tc_core, memcmp_test);
    tcase_add_test(tc_core, memcpy_test);
    tcase_add_test(tc_core, memmove_test);
    tcase_add_test(tc_core, memset_test);
    tcase_add_test(tc_core, strcat_test);
    tcase_add_test(tc_core, strncat_test);
    tcase_add_test(tc_core, strchr_test);
    tcase_add_test(tc_core, strcmp_test);
    tcase_add_test(tc_core, strncmp_test);

    tcase_add_test(tc_core, strcpy_test);
    tcase_add_test(tc_core, strncpy_test);
    tcase_add_test(tc_core, strcspn_test);
    tcase_add_test(tc_core, strerror_test);
    tcase_add_test(tc_core, strlen_test);
    tcase_add_test(tc_core, strpbrk_test);
    tcase_add_test(tc_core, strrchr_test);
    tcase_add_test(tc_core, strspn_test);
    tcase_add_test(tc_core, strstr_test);
    tcase_add_test(tc_core, strtok_test);

    tcase_add_test(tc_core, s21_sprintf_d);
    tcase_add_test(tc_core, s21_sprintf_i);
    tcase_add_test(tc_core, s21_sprintf_u);
    tcase_add_test(tc_core, s21_sprintf_o);
    tcase_add_test(tc_core, s21_sprintf_x);
    tcase_add_test(tc_core, s21_sprintf_X);
    tcase_add_test(tc_core, s21_sprintf_c);
    tcase_add_test(tc_core, s21_sprintf_s);
    tcase_add_test(tc_core, s21_sprintf_n);
    tcase_add_test(tc_core, s21_sprintf_p);
    tcase_add_test(tc_core, s21_sprintf_e);
    tcase_add_test(tc_core, s21_sprintf_E);
    tcase_add_test(tc_core, s21_sprintf_g);
    tcase_add_test(tc_core, s21_sprintf_G);
    tcase_add_test(tc_core, s21_sprintf_F);
    tcase_add_test(tc_core, s21_sprintf_f);

    tcase_add_test(tc_core, s21_sscanf_d);
    tcase_add_test(tc_core, s21_sscanf_u);
    tcase_add_test(tc_core, s21_sscanf_o);
    tcase_add_test(tc_core, s21_sscanf_x);
    tcase_add_test(tc_core, s21_sscanf_X);
    tcase_add_test(tc_core, s21_sscanf_fFgGeE);
    tcase_add_test(tc_core, s21_sscanf_p);
    tcase_add_test(tc_core, s21_sscanf_n);
    tcase_add_test(tc_core, s21_sscanf_c);
    tcase_add_test(tc_core, s21_sscanf_s);

    tcase_add_test(tc_core, s21_to_upper_test);
    tcase_add_test(tc_core, s21_to_lower_test);
    tcase_add_test(tc_core, s21_insert_test);
    tcase_add_test(tc_core, s21_trim_test);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    Suite *s = test_suite();
    SRunner *runner = srunner_create(s);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);

    int nofailed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (nofailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
