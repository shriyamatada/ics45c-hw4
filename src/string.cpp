#include "string.hpp"
#include <iostream>
#include <utility>

int String::strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

char *String::strcpy(char *dest, const char *src) {
    int i = 0;
    for ( ; src[i] != '\0'; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for ( ; src[i] != '\0' && i < n; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int i = strlen(dest);
    int j = 0;
    for ( ; src[j] != '\0'; ++j)
        dest[i + j] = src[j];
    dest[i + j] = '\0';
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int i = strlen(dest);
    int j = 0;
    for ( ; j < n && src[j] != '\0'; ++j)
        dest[i + j] = src[j];
    dest[i + j] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right) {
    int i = 0;
    for ( ; left[i] != '\0' && right[i] != '\0'; ++i) {
        if (left[i] != right[i])
            return left[i] - right[i];
    }
    return left[i] - right[i];
}

int String::strncmp(const char *left, const char *right, int n) {
    int i = 0;
    for ( ; i < n && left[i] != '\0' && right[i] != '\0'; ++i) {
        if (left[i] != right[i])
            return left[i] - right[i];
    }
    if (i == n)
        return 0;
    return left[i] - right[i];
}

void String::reverse_cpy(char *dest, const char *src) {
    int length = strlen(src);
    for (int i = 0; i < length; ++i)
        dest[i] = src[length - 1 - i];
    dest[length] = '\0';
}

const char *String::strchr(const char *str, char c) {
    int i = 0;
    for ( ; str[i] != '\0'; ++i) {
        if (str[i] == c)
            return &str[i];
    }
    if (c == '\0')
        return &str[i];
    return nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
    int len = strlen(needle);
    if (len == 0)
        return haystack;
    for (int i = 0; haystack[i] != '\0'; ++i) {
        if (strncmp(haystack + i, needle, len) == 0)
            return &haystack[i];
    }
    return nullptr;
}

char *String::strdup(const char *src) {
	char *result = new char[strlen(src) + 1];
	strcpy(result, src);
	return result;
}

String::String(const char *s) {
	buf = strdup(s);
}

String::String(const String &s) {
	buf = strdup(s.buf);
}

String::~String() {
	delete[] buf;
}

int String::size() const {
	//rmbr it's the same thing as hw3
	return strlen(buf);
}

void String::swap(String &s) {
	std::swap(buf, s.buf);
}

String &String::operator=(String s) {
	swap(s);
	return *this;
}

void String::print(std::ostream &out) const {
    out << buf;
}

std::ostream &operator<<(std::ostream &out, String s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}

char &String::operator[](int index) {
	if(!in_bounds(index)) {
		std::cout << "ERROR: Index Out Of Bounds" << std::endl;
		return buf[0];
	}
	return buf[index];
}

const char &String::operator[](int index) const {
	if(!in_bounds(index)) {
		std::cout << "ERROR: Index Out Of Bounds" << std::endl;
		return buf[0];
	}
	return buf[index];
}

//same as hw3 just no &s
bool String::operator==(String s) const {
	return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(String s) const {
	return strcmp(buf, s.buf) != 0;
}

bool String::operator<(String s) const  {
	return strcmp(buf, s.buf) < 0;
}

bool String::operator>(String s) const  {
	return strcmp(buf, s.buf) > 0;
}

bool String::operator<=(String s) const {
	return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(String s) const {
	return strcmp(buf, s.buf) >= 0;
}

int String::indexOf(char c) const {
    const char *p = strchr(buf, c);
    if (p == nullptr) {
        return -1;
	}
    return p - buf;
}

//again, same just diff parameter
int String::indexOf(String s) const {
    const char *p = strstr(buf, s.buf);
    if (p == nullptr) {
        return -1;
	}
    return p - buf;
}

String::String(int length) {
	buf = new char[length + 1];
}

String String::reverse() const {
	String result(strlen(buf));
	reverse_cpy(result.buf, buf);
	return result;
}

String String::operator+(String s) const {
	String result(size() + s.size());
	strcpy(result.buf, buf);
	strcat(result.buf, s.buf);
	return result;
}

String &String::operator+=(String s) {
    String result(size() + s.size());
    strcpy(result.buf, buf);
    strcat(result.buf, s.buf);
    swap(result);
    return *this;
}

void String::read(std::istream &in) {
    char temp[1024]; //1023 + 1 for terminator
    in >> temp;
    String result(temp);
    swap(result);
}
