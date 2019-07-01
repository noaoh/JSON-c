/* main.c */

/*
    This program demonstrates a simple application of JSON_checker. It reads
    a JSON text from STDIN, producing an error message if the text is rejected.

        % JSON_checker <test/pass1.json
*/

#include <stdlib.h>
#include <stdio.h>
#include "JSON_checker.h"

int main(int argc, char* argv[]) {
/*
    Read STDIN. Exit with a message if the input is not well-formed JSON text.

    jc will contain a JSON_checker with a maximum depth of 20.
*/
    JSON_checker jc = new_JSON_checker(20);
    for (;;) {
        int next_char = getchar();
        if (next_char <= 0) {
            break;
        }
        JSON_checker_result r = JSON_checker_char(jc, next_char);
        if (!r.returncode) {
            fprintf(stderr, "JSON_checker_char: syntax error: '%c' at pos %i\n", r.badchar, r.pos);
            exit(1);
        }
    }
    
    JSON_checker_result r = JSON_checker_done(jc);
    if (!r.returncode) {
        fprintf(stderr, "JSON_checker_end: syntax error at pos %i\n", r.pos);
        exit(1);
    }
}
