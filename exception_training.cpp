//
// Created by jmwat on 3/22/2021.
//

#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <exception>

// throws an exception whenever you invoke the forget method with an argument equal to 0xFACE.
struct Groucho
{
    void forget(int x)
    {
        if (x == 0xFACE)
        {
            throw std::runtime_error {"I'd be glad to make an exception."};
        }
        printf("Forgot 0x%x\n", x);
    }
};

// this is for learning. This should never be used in production.
// using a copy constructor could potentially double free if copied.
struct SimpleString
{
    /* constructor takes a single max_size argument. This is the maximum length
     * of the string, which includes a null terminator.
     * member initializer saves this length into max_size member variable.
     * length is initialized to 0 and ensures enough size for a null byte
     * This pattern is called resource acquisition is initialization (RAII) or
     * constructor acquires, destructor releases (CADRe)
    */
     SimpleString(size_t max_size) : max_size{max_size}, length{}
    {
        if (max_size == 0)
        {
            throw std::runtime_error{"Max size must be at least 1."};
        }
        // a buffer to store the string
        // max_size is used to allocate buffer to store string.
        buffer = new char[max_size];
        // string is initially empty so the first byte of the buffer is initialized to zero.
        buffer[0] = 0;
    }
    /* include a move constructor instead of copy constructor to safely copy simple string object
     * Pass in the corresponding fields max_size, buffer, and length, into other.
     * Designed to not throw an exception. This is less expensive than executing copy constructor
     */
    SimpleString(SimpleString&& other) noexcept
    : max_size{other.max_size}, buffer(other.buffer), length(other.length)
    {
        other.length = 0;
        other.buffer = nullptr;
        other.max_size;
    }

    /* The SimpleString class owns a resource -- the memory pointed to by buffer -- which
     * must be released when it's not longer needed.
     * This destructor deallocates buffer, preventing a memory leak
    */
     ~SimpleString()
    {
        delete[] buffer;
    }


    // a move assignment operator. Allows the use of = sign to copy one string object into another
    // Takes an rvalue reference rather than a const lvalue reference.
    // returns a reference to the result, which is always *this
    SimpleString& operator=(SimpleString&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        // delete the old buffer
        delete[] buffer;
        // reassign buffer
        buffer = other.buffer;
        length = other.length;
        max_size = other.max_size;
        other.buffer = nullptr;
        other.length = 0;
        other.max_size = 0;
        return *this;
    }

    /*
     * prints string. Provides a tag string so you can match an invocation of print
     * with the result.
     * This method is const because it doesn't need to modify the state of a SimpleString
     */
    void print(const char* tag) const
    {
        printf("%s: %s", tag, buffer);
    }
    /*
     * append_line method takes a null-terminated string x and adds its contents --
     * plus a newline character -- to buffer. It returns true if x was successfully
     * appended and false if there wasn't enough space.
     * First, append_line must determine length of x. Use the strlen function from
     * <cstring> header, which accepts a null terminated string an returns its length.
     * This result is used to determine whether appending x (a newline character) and a null byte
     * to the current string would result in a string with length greater than max_size.
     * If this happens, then append_line returns false.
     */
    bool append_line(const char* x)
    {
        const auto x_len = strlen(x);
        if (x_len + length + 2 > max_size)
        {
            return false;
        }
        // Need to copy its bytes into the correct location in buffer. The strncpy function
        // accepts three arguments: the destination address, the source address, and the num of chars to copy.
        // this returns destination, which is then discarded
        std::strncpy(buffer + length, x, max_size - length);
        length += x_len;
        // add newline character and null byte to end of buffer
        buffer[length++] = '\n';
        buffer[length] = 0;
        // return true if you've successfully appended the input x as a line to the end of buffer
        return true;
    }
private:
    size_t max_size;
    char* buffer;
    size_t length;
};

struct SimpleStringOwner
{
    SimpleStringOwner(SimpleString&& x)
    : string{std::move(x)}
    {}
    ~SimpleStringOwner()
    {
        string.print("About to destroy");
    }

private:
    SimpleString string;
};

int main()
{
    Groucho groucho;
    try
    {
        groucho.forget(0xC0DE);
        groucho.forget(0xFACE);
        groucho.forget(0xC0FFEE);
    } catch (const std::runtime_error& e)
    {
        printf("exception caught with message: %s\n", e.what());
    }
    // string has a max length of 115
    SimpleString string{115};
    string.append_line("Starbuck, whadya hear?");
    string.append_line("Nothing' but the rain..");
    string.print("A");
    string.append_line("Grab your gun and bring the cat in.");
    string.append_line("Aye-aye sir, coming home.");
    string.print("B");
    if (!string.append_line("Galactica!"))
    {
        printf("String was not big enough to append another message.");
    }

    //SimpleStringOwner x{"x"};
    printf("x is alive\n");

    SimpleString a{50};
    a.append_line("We apologize for the");
    //SimpleString a_copy{a};
    a.append_line("inconvenience.");
    //a_copy.append_line("incontinence.");
    a.print("a");
    //a_copy.print("a_copy");
}

