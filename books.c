// Программа для библиотеки

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"


int main(void)
{
    //  Инициализация библиотеки
    Library lib;
    initLibrary(&lib);

    int choice;
    char title[256];
    char author[256];
    int year;
    int pages;
    char filename[256];
    do {
        printf("\nЧто будем делать?\n");
        printf("1 - Добавить книгу в библиотеку\n2 - Удалить книгу из библиотеки по названию\n3 - Найти книгу по автору или названию\n4 - Показать все книги\n");
        printf("5 - Отсортировать весь список\n6 - Сохраниние библиотеки в файл\n7 - Загрузка библиотеки из файла\n0 - Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            // Очистка буфера в случае ошибки
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Ошибка! Введите целое число.\n");
            continue;
        }
        // Очистка буфера после чтения числа
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        //Действие с библиотекой
        switch(choice) {
            case 1:
                printf("Введите название книги: ");
                if (fgets(title, sizeof(title), stdin) == NULL) {
                    printf("Ошибка ввода названия\n");
                    break;
                }
                title[strcspn(title, "\n")] = 0; // Удаляем символ новой строки
                
                printf("Введите автора книги: ");
                if (fgets(author, sizeof(author), stdin) == NULL) {
                    printf("Ошибка ввода автора\n");
                    break;
                }
                author[strcspn(author, "\n")] = 0; // Удаляем символ новой строки
                
                printf("Введите год издания: ");
                if (scanf("%d", &year) != 1) {
                    printf("Ошибка ввода года\n");
                    while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера
                    break;
                }
                while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера
                
                printf("Введите количество страниц: ");
                if (scanf("%d", &pages) != 1) {
                    printf("Ошибка ввода количества страниц\n");
                    while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера
                    break;
                }
                while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера
                
                addBook(&lib, title, author, year, pages);
                printf("Книга '%s' добавлена в библиотеку!\n", title);
                break;
                
            case 2:
                printf("Введите название книги для удаления: ");
                if (fgets(title, sizeof(title), stdin) == NULL) {
                    printf("Ошибка ввода\n");
                    break;
                }
                title[strcspn(title, "\n")] = 0;
                
                if (removeBook(&lib, title)) {
                    printf("Книга '%s' удалена!\n", title);
                } else {
                    printf("Книга '%s' не найдена!\n", title);
                }
                break;
                
            case 3:
                printf("Введите название или автора для поиска: ");
                if (fgets(title, sizeof(title), stdin) == NULL) {
                    printf("Ошибка ввода\n");
                    break;
                }
                title[strcspn(title, "\n")] = 0;
                searchBook(&lib, title);
                break;
                
            case 4:
                printLibrary(&lib);
                break;
                
            case 5:
                sortBooksByYear(&lib);
                printf("Библиотека отсортирована по году издания!\n");
                break;
                
            case 6:
                printf("Введите имя файла для сохранения: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) {
                    printf("Ошибка ввода\n");
                    break;
                }
                filename[strcspn(filename, "\n")] = 0;
                saveToFile(&lib, filename);
                break;
                
            case 7:
                printf("Введите имя файла для загрузки: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) {
                    printf("Ошибка ввода\n");
                    break;
                }
                filename[strcspn(filename, "\n")] = 0;
                loadFromFile(&lib, filename);
                break;
                
            case 0:
                printf("Выход из программы\n");
                break;
                
            default:
                printf("Неправильный выбор, попробуйте снова\n");
                break;
        }
    } while (choice != 0);

    // Очистка памяти перед выходом
    Book* current = lib.head;
    while (current != NULL) {
        Book* next = current->next;
        free(current->title);
        free(current->author);
        free(current);
        current = next;
    }


    return 0;
}