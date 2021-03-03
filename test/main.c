#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned int count = 1; //Last line does not have \n
    unsigned int total = 0;
    char c;
    char buf[1024];

    if (argc >= 2){
        for (int i=1; i < argc; i++){
            count = 0;
            fp = fopen(argv[i], "r");
            while (!feof(fp)){
                fscanf(fp, "%c", buf);

                if (buf[0] == '\n'){
                    count++;
                }
            }
            fclose(fp);
            printf("%s Total Lines: %d\n", argv[i], count);
            total += count;
        }
    }
    
    printf("Total Count: %d", total);

    return 0;
}