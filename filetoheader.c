#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 4) {
        char message[512];
        snprintf(
            message, 511,
           "Usage: %s <input file> <output file> <keyword>\n"
           "    Converts file into C header with Array Buffer Containing file\n"
           "    <input file>: Input file to Convert\n"
           "    <output file>: Output file to save output to\n"
           "    <keyword>: Keyword used in Header\n",
           argv[0]
        );
        puts(message);
        return 0;
    }

    FILE *fdst = NULL;
    char *keyword = argv[3];
    int len = 0;
    FILE *fsrc = fopen(argv[1], "rb");
    if(fsrc == NULL) {
        printf("Error Opening Input File\n");
        goto err_fsrc_open;
    }

    fdst = fopen(argv[2], "w");
    if(fdst == NULL) {
        printf("Error Opening Output File\n");
        goto err_fdst_open;
    }

    fseek(fsrc, 0L, SEEK_END);
    len = ftell(fsrc);
    rewind(fsrc);

    fprintf(
        fdst,
        "#ifndef %s_HEAD\n"
        "#define %s_HEAD\n\n"
        "int %s_LEN = %d;\n"
        "char %s_DATA[] = {",
        keyword, keyword, keyword, len, keyword
    );

    for(int i=0;i<len;i++) {
        int c = fgetc(fsrc);
        fprintf(fdst, "(char)%d,\n", c);
    }

    fprintf(
        fdst,
        "0};\n"
        "\n#endif\n"
    );

    fclose(fsrc);
    fclose(fdst);
    goto noerror;

    err_fdst_open:
    fclose(fsrc);
    err_fsrc_open:
    return -1;
    noerror:
    printf("File has been Converted Successfully!\n");

    return 0;
}
