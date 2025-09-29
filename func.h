#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// Определение структур
typedef struct Book {
    char* title;
    char* author;
    int year;
    int pages;
    struct Book* next;
} Book;

typedef struct {
    Book* head;
    int count;
} Library;

// Объявления функций
void initLibrary(Library* lib);
Book* createBook(const char* title, const char* author, int year, int pages);
void addBook(Library* lib, const char* title, const char* author, int year, int pages);
int removeBook(Library* lib, const char* title);
void searchBook(Library* lib, const char* SearchTitle);
void printLibrary(Library* lib);
void sortBooksByYear(Library* lib);
void saveToFile(Library* lib, const char* filename);
void loadFromFile(Library* lib, const char* filename);

#endif