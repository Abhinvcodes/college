#include <stdio.h>
#include <string.h>

static char *returnTypes[] = { "void", "int", "double" };
static int rtsize = sizeof(returnTypes) / sizeof(returnTypes[0]);

int main()
{
    FILE *f = fopen("input.c", "r");
    if (!f) {
        printf("input file does not exist\n");
        return 1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), f)) {

        int funcfound = 0;
        int paraCount = 0;
        char returntype[20] = "";
        char funcName[100] = "";

        char *p = strtok(buffer, " (),");
        if (!p) continue;

        // return type
        for (int i = 0; i < rtsize; i++) {
            if (strcmp(returnTypes[i], p) == 0) {
                strcpy(returntype, p);
                funcfound = 1;
                break;
            }
        }

        if (!funcfound) continue;

        // function name
        p = strtok(NULL, " (),");
        if (!p) continue;
        strcpy(funcName, p);

        // parameter list
        while ((p = strtok(NULL, " (),")) != NULL) {
            for (int i = 0; i < rtsize; i++) {
                if (strcmp(returnTypes[i], p) == 0) {
                    paraCount++;
                }
            }
        }

        printf("%s : %s : %d vars\n", funcName, returntype, paraCount);
    }

    fclose(f);
    return 0;
}

