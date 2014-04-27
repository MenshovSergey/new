#include <iostream>
#include <cstdio>
#include <string.h>

extern "C" void _print(char*, const char*, const char*)__attribute__((__cdecl__));

int main() {
    char f[6];
    char s[8];
    char y[4];
    y[0] = ' ';
    y[1] = '-';
    y[2] = '+';
    y[3] = '0';
    f[5] = 0;
    s[0] = '%';
    s[6] = 'i';
    s[7] = 0;
    char a[16];
    char b[16];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                for(int  l = 0; l < 4; l++) {
                    for(int m = 0; m < 10; m++) {
                        f[0] = y[i];
                        f[1] = y[j];
                        f[2] = y[k];
                        f[3] = y[l];
                        f[4] = '0' + m;
                        s[1] = f[0];
                        s[2] = f[1];
                        s[3] = f[2];
                        s[4] = f[3];
                        s[5] = f[4];
                        _print(a, f, "0");
                        sprintf(b, s, 0);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "-0");
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "1");
                        sprintf(b, s, 1);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "-1");
                        sprintf(b, s, -1);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "a");
                        sprintf(b, s, 10);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "-a");
                        sprintf(b, s, -10);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "f1");
                        sprintf(b, s, 241);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                        _print(a, f, "-f1");
                        sprintf(b, s, -241);
                        if(strcmp(a, b)) std::cout << "Fail: " << a << " " << b << "\n";
                    }
                }
            }
        }
    }
    std::cout << "End\n";
}
