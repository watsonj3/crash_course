//
// Created by jwats on 4/2/2021.
//

// Structured Binding
// Structured binding allows you to unpack objects into their constituent elements.
// Any type whose non-static data members are public can be unpacked this way --
// For example, the POD (plain-old-data class) types.


#include<cstdio>

// Consider a read_text_file function that takes a string argument corresponding to the file path.
// Such a function might fail if a file is locked or doesn't exist.
// Let's return a success status code from the function.

struct TextFile
{
    // a flag communicates to the caller whether the function call was a success.
    bool success;
    // the contents of the file
    const char* contents;
    // the size of the file
    size_t n_bytes;
};

// prototype of read_text_file
TextFile read_text_file(const char* path);

int main()
{
    // use a structured binding declaration to unpack the results into three distinct variables.
    const auto [success, contents, length] = read_text_file("README.txt");
    // You can then use those three variables as though you had declared them individually.
    if (success)
    {
        printf("Read %zu bytes: %s\n", length, contents);
    } else {
        printf("Failed to open README.txt.");
    }
}

TextFile read_text_file(const char* path)
{
    // Doesn't actually read a file. Just a dummy definition for read_text_file.
    const static char contents[] {"Sometimes the goat is you."};
    return TextFile{
        true,
        contents,
        sizeof(contents)
    };
}