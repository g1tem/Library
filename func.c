#include "func.h"



//Инициализация библиотеки
void initLibrary(Library* lib) {
    lib->head = NULL;
    lib->count = 0;
}

//Функция для создания новой книги
Book* createBook(const char* title, const char* author, int year, int pages) {  //  Возвращает указатель на структуру
    Book* newBook = (Book*)malloc(sizeof(Book));    //  Указатель на выделенную память под структуру Book
    if (!newBook) {
        printf("Ошибка выделения памяти для книги\n");
        return NULL;
    }
    //  Выделяем память под строки и копируем данные
    newBook->title = (char*)malloc(strlen(title) + 1);
    newBook->author = (char*)malloc(strlen(author) + 1);

    if (!newBook -> title || !newBook -> author) {
        printf("Ошибка выделения памяти для строк\n");
        free(newBook->title);
        free(newBook->author);
        free(newBook);
        return NULL;
    }

    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->pages = pages;
    newBook->next = NULL;
    return newBook;
}

//  Добавление книги в начало библиотеки
void addBook(Library* lib, const char* title, const char* author, int year, int pages) {
    Book* newBook = createBook(title, author, year, pages);
    if (!newBook) return;

    newBook->next = lib->head;
    lib->head = newBook;
    lib->count++;
}

//  Удаление книги по названию
int removeBook(Library* lib, const char* title) {
    Book* current = lib->head;
    Book* prev = NULL;
    int removed = 0;
    
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            if (prev == NULL) {
                //  Удаляем первый элемент
                lib->head = current->next;
            } 
            else {
                //  Удаляем из середины или конца
                prev->next = current->next;
            }
            
            // Освобождаем память
            free(current->title);
            free(current->author);
            free(current);
            lib->count--;
            removed = 1;
            break;
        }
        
        prev = current;
        current = current->next;
    }
    
    return removed;
}

//  Поиск книги по названию
void searchBook(Library* lib, const char* SearchTitle) {
    Book* current = lib->head;
    int found = 0;
    printf("Результаты поиска для '%s': \n", SearchTitle);
    printf("=============================================\n");
    
    while (current != NULL) {
        if (strstr(current->title, SearchTitle) != NULL || strstr(current->author, SearchTitle) != NULL) {
            printf("Название книги: %s\n", current->title);
            printf("Автор: %s\n", current->author);
            printf("Год: %d, Страниц: %d\n", current->year, current->pages);
            printf("=============================================\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Книга с таким названием не найдена\n");
    }
    printf("=============================================");
}

//  Вывод всех книг в библиотеке
void printLibrary(Library* lib) {
    Book* current = lib->head;
    printf("Библиотека из %d книг:\n", lib->count);
    printf("=============================================\n");
    int i = 1;
    while (current != NULL) {
        printf("%d. %s - %s (%d, %d стр.)\n", i++, current->title, current->author, current->year, current->pages);
        current = current->next;
    }
    
    printf("=============================================\n");
}

//  Сортировка пузырьком по году издания
void sortBooksByYear(Library* lib) {
    if (lib->count < 2) return;

    int swapped;
    Book** ptr;
    do {
        swapped = 0;
        ptr = &(lib->head);

        while ((*ptr)->next != NULL) {
            Book* current = *ptr;
            Book* next = current->next;

            if (current->year > next->year) {
                current->next = next->next;
                next->next = current;
                *ptr = next;
                swapped = 1;
            }
            ptr = &(*ptr)->next;
    }
    } while (swapped);
}

//  Сохранение данных в текстовый файл
void saveToFile(Library* lib, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка при открытии файла для записи\n");
        return;
    }
    Book* current = lib->head;
    while (current != NULL) {
        fprintf(file, "%s;%s;%d;%d;\n", current->title, current->author, current->year, current->pages);
        current = current->next;
    }
    fclose(file);
    printf("Данные сохранены в файл %s", filename);
}

//  Загрузка данных из файла
void loadFromFile(Library* lib, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка при открытии файла\n");
        return;
    }
//  Очистка текущей библиотеки
    Book* current = lib->head;
    while (current != NULL) {
        Book* next = current->next;
        free(current->title);
        free(current->author);
        free(current);
        current = next;
    }

    lib->head = NULL;
    lib->count = 0;
    
//  Читаем данные из файла
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char* title = strtok(line, ";");
        char* author = strtok(NULL, ";");
        char* yearStr = strtok(NULL, ";");
        char* pagesStr = strtok(NULL, ";");
        if (title && author && yearStr && pagesStr) {
            int year = atoi(yearStr);
            int pages = atoi(pagesStr);
            addBook(lib, title, author, year, pages);
        }
    }
    fclose(file);
    printf("Данные из файла загружены\n");
}
