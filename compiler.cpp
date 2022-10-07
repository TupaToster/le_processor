#include "comp_head.h"
#include "flog.cpp"
#include "text.cpp"

void binWriteDouble (FILE* outFile, double* val) {

    assert (outFile != NULL);

    for (int i = 0; i < sizeof (double); i++) fprintf (outFile, "%c", *( ( (char*) val) + i) );
}

// @todo add errCodes for returns in compiler

const char* signature= "CP01";

int main (int argc, char* argv[]) {

    bool aFlag = 0;
    char* fileName  = NULL;
    char* outFileName = NULL;


    switch (argc) {

        case 1:

            printf ("Wrong compiler usage \n"
                "Good usage: wtfcomp \"file_name\" -o \"compiled_file_name\" -a\n"
                "-o with \"compiled_file_name\" is used to set name of compiled file, if not given then is set to \"a.wtf\" \n"
                "-a is used to compile file independent of it's modification time");
        return 0;

        case 2:

            fileName = (char*) calloc (strlen (argv[1] + 1), sizeof (char));
            strcpy (fileName, argv[1]);
            fileName[strlen (argv[1])] = '\0';
        break;

        case 3:

            fileName = (char*) calloc (strlen (argv[1] + 1), sizeof (char));
            strcpy (fileName, argv[1]);
            fileName[strlen (argv[1])] = '\0';

            if (strcmp (argv[2], "-a") == 0) {

                aFlag = 1;
            }
            else {

                printf ("Wrong compiler args");
                return 0;
            }
        break;

        case 4:

            fileName = (char*) calloc (strlen (argv[1] + 1), sizeof (char));
            strcpy (fileName, argv[1]);
            fileName[strlen (argv[1])] = '\0';

            if (strcmp (argv[2], "-a") == 0 and strcmp (argv[3], "-o")) {

                aFlag = 1;

                outFileName = (char*) calloc (strlen (argv[4]) + 1, sizeof (char));
                strcpy (outFileName, argv[4]);
                outFileName[strlen (argv[4])] = '\0';
            }
        break;

        default:

            printf ("Wrong args");
            return 0;
        break;
    }

    if (outFileName == NULL) {

        outFileName = (char*) calloc (sizeof ("a.wtf") + 1, sizeof (char));
        strcpy (outFileName, "a.wtf");
        outFileName[strlen ("a.wtf")] = '\0';
    }

    flog (outFileName);

    FILE* outFile = fopen (outFileName, "wb");
    assert (outFile != NULL);
    setvbuf (outFile, NULL, _IONBF, 0);

    Text codeInput = read_text (fileName);

    fprintf (outFile, "%s", signature);

    char* inputStr = (char*) calloc (101, sizeof (char));
    assert (inputStr != NULL);


    for (int i = 0; i < codeInput.stringCnt; i++) {

        sscanf (codeInput.lines[i].begin, "%s", inputStr);

        if      (strcmp (inputStr, "push") == 0) {

            fputc (PUSH, outFile);

            double val = 0;

            sscanf (codeInput.lines[i].begin, "%s%Lf", inputStr, &val);

            binWriteDouble (outFile, &val);
        }
        else if (strcmp (inputStr, "add" ) == 0) fputc (ADD , outFile);
        else if (strcmp (inputStr, "sub" ) == 0) fputc (SUB , outFile);
        else if (strcmp (inputStr, "mul" ) == 0) fputc (MUL , outFile);
        else if (strcmp (inputStr, "div" ) == 0) fputc (DIV , outFile);
        else if (strcmp (inputStr, "out" ) == 0) fputc (OUT , outFile);
        else if (strcmp (inputStr, "dump") == 0) fputc (DUMP, outFile);
        else if (strcmp (inputStr, "in"  ) == 0) {

            fputc (IN, outFile);

            double val = 0;

            sscanf (codeInput.textString, "%s%Lf", inputStr, &val);

            binWriteDouble (outFile, &val);
        }
        else if (strcmp (inputStr, "HLT")  == 0) fputc (HLT, outFile);
    }

    fclose (outFile);
}