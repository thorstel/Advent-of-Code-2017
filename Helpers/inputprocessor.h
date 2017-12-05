#ifndef INPUTPROCESSOR_H_
#define INPUTPROCESSOR_H_

#include <stdbool.h>
#include <stdio.h>

/**
 * Reads from the specified file stream and calls the given process
 * function for each 'word' (whitespace-terminated token).
 *
 * @param[in] input Pointer to the file stream from which is being read.
 * @param[in] process function which will be called with the current
 * 'word', the length of the word (excluding the zero-byte) and an
 * indicator whether a newline was processed. The string argument will
 * never be NULL and is always '\0' terminated. However it may be a
 * single zero byte (i.e. an empty string).
 *
 * @return Returns true if the input stream could be processed
 * successfully.
 */
bool process_input(FILE* input, bool (*process)(char*, size_t, bool));

#endif  /* INPUTPROCESSOR_H_ */

