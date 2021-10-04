#include <stdio.h>

int main() {
    char filename[50];
    FILE *fp;
    char ch;
    int letter = 0, digit = 0;
    printf("FILENAME TO READ:\t");
    scanf("%[^\n]", filename); while ((ch=getchar()) != '\n'); 
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("None pointer\n");
    } else {
        ch = fgetc(fp); 
        while (ch != EOF) {
            if (ch >= '0' && ch <= '9') {
                digit ++;
            }
            letter ++;
            ch = fgetc(fp);
        }
    }
    printf("LETTER: %d, DIGIT: %d\n", letter, digit);
    return 0;
}
