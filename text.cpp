#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>
#include <ctype.h>
#include "flog.cpp"


enum TextErrorCodes {

    OK = 0

};

unsigned int TextErrCode = 0;

/// @brief Struct to store lines of Text in format [begin, end)
struct Line {

    char* begin = NULL; ///< Ptr to the beginning
    char* end   = NULL; ///< Ptr to the end
};

/// @brief Stores Text in format of string and array of Line structures
struct Text {

    char* textString = NULL; ///< char* that points to the beginning of a Text
    size_t textSize = 0;     ///< size_t that declares sizeof Text in chars
    Line* lines = NULL;      ///< ptr to a Line array that stores Text in a format of lines
    size_t stringCnt = 0;    ///< size_t that indicates amount of lines in Text
};

void initLine(Line* target) {

    target->begin = NULL;
    target->end = NULL;
}

void killLine(Line* target) {

    target->begin = NULL;
    target->end   = NULL;
}

void initText(Text* target) {

    target->textString  = NULL;
    target->textSize    = 0;
    target->stringCnt   = 0;
    target->lines       = NULL;
}

void killText (Text* target) {

    free (target->textString);
    free (target->lines);
    target->textSize  = 0;
    target->stringCnt = 0;
    return;
}

void cntLines (Text* src) {

    assert (src != NULL);

    for (size_t i = 0; i < src->textSize; i++) {

        if (src->textString[i] == '\n') src->stringCnt++;
    }
    src->stringCnt++;
}

size_t get_size (const char* filename) {

    assert (filename != NULL);

    struct stat temp = {};

    stat (filename, &temp);

    return temp.st_size;
}

void separateLines (Text* writeTo) {

    assert (writeTo != NULL);
    assert (writeTo->lines != NULL);

    size_t line_iter = 0;

    for (size_t i = 0; i < writeTo->textSize; i++) {

        if (writeTo->lines[line_iter].begin == NULL) writeTo->lines[line_iter].begin = writeTo->textString + i;

        if (writeTo->textString[i] == '\n') {

            writeTo->lines[line_iter].end = writeTo->textString + i + 1;
            line_iter++;
        }
    }

    writeTo->lines[line_iter].end = writeTo->textString + writeTo->textSize;
}

void bufferize (const char* filename, Text* writeTo) {

    writeTo->textSize = get_size (filename);

    writeTo->textString = (char*) calloc (writeTo->textSize + 2, sizeof (char));

    writeTo->textString++;

    FILE* fIn = fopen (filename, "r");

    fread (writeTo->textString, sizeof (char), writeTo->textSize, fIn);

    writeTo->textString[writeTo->textSize] = '\0';

    fclose (fIn);

}


Text read_text (const char* filename) {

    assert (filename != NULL);

    Text retVal = {};
    initText (&retVal);

    bufferize (filename, &retVal);

    cntLines (&retVal);

    retVal.lines = (Line*) calloc (retVal.stringCnt + 1, sizeof (Line));

    separateLines (&retVal);

    return retVal;
}

