#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32]; // FIXED (I THINK) Allocated string space for the book name do I know what this means? Sort of
    int chapters;
} Book;

int main() {
    Book bible_books[] = {
        {"Genesis", 50}, {"Exodus", 40}, {"Leviticus", 27},
        {"Numbers", 36}, {"Deuteronomy", 34}, {"Joshua", 24}, {"Judges", 21},
        {"Ruth", 4}, {"1 Samuel", 31}, {"2 Samuel", 24}, {"1 Kings", 22}, {"2 Kings", 25},
        {"1 Chronicles", 29}, {"2 Chronicles", 36}, {"Ezra", 10}, {"Nehemiah", 13}, {"Esther", 10},
        {"Job", 42}, {"Psalms", 150}, {"Proverbs", 31}, {"Ecclesiastes", 12}, {"Song of Solomon", 8},
        {"Isaiah", 66}, {"Jeremiah", 52},{"Lamentations", 5}, {"Ezekiel", 48}, {"Daniel", 12}, {"Hosea", 14},
        {"Joel", 3}, {"Amos", 9}, {"Obadiah", 1}, {"Jonah", 4}, {"Micah", 7}, {"Nahum", 3}, {"Habakkuk", 3},
        {"Zephaniah", 3}, {"Haggai", 2}, {"Zechariah", 14},  {"Malachi", 4}, {"Matthew", 28}, {"Mark", 16},
        {"Luke", 24}, {"John", 21}, {"Acts", 28}, {"Romans", 16}, {"1 Corinthians", 16}, {"2 Corinthians", 13},
        {"Galatians", 6}, {"Ephesians", 6}, {"Philippians", 4}, {"Colossians", 4}, {"1 Thessalonians", 5},
        {"2 Thessalonians", 3}, {"1 Timothy", 6}, {"2 Timothy", 4}, {"Titus", 3}, {"Philemon", 1},
        {"Hebrews", 13}, {"James", 5}, {"1 Peter", 5}, {"2 Peter", 3}, {"1 John", 5}, {"2 John", 1}, {"3 John", 1},
        {"Jude", 1}, {"Revelation", 22}
    };
    // FIXED: Properly divide total size by a single element size I don't know what the fuck I'm doing though pls work
    int num_books = sizeof(bible_books) / sizeof(bible_books[0]);
    unsigned int user_seed;

    printf("Enter any number to use as a random seed: ");
    if (scanf("%u", &user_seed) != 1) {
        printf("Invalid numeric input.\n");
        printf("\n=========================================\n");
        system("pause");
        return 1;
    }

    // Clear the leftover 'Enter' key from the input buffer
    while (getchar() != '\n');

    // Seed the fake rng chaos matrix engine
    srand(user_seed);
    printf("\n--- PRNG ENGINE INITIALIZED WITH SEED: %u ---\n", user_seed);

    // 1. Math for picking the Book
    int raw_book_rand = rand();
    int random_book_index = raw_book_rand % num_books;

    printf("\n[STEP 1: SELECTING A BOOK]");
    printf("\n  -> Raw rand() value generated : %d", raw_book_rand);
    printf("\n  -> Total books in your array  : %d", num_books);
    printf("\n  -> Math operation             : %d %% %d", raw_book_rand, num_books);
    printf("\n  -> Remainder (Array Index)    : %d (Maps to: %s)", random_book_index, bible_books[random_book_index].name);
    printf("\n-----------------------------------------\n");

    // 2. Math for picking the Chapter
    int raw_chap_rand = rand();
    int max_chapters = bible_books[random_book_index].chapters;
    int remainder_chap = raw_chap_rand % max_chapters;
    int random_chapter = remainder_chap + 1;

    printf("\n[STEP 2: SELECTING A CHAPTER]");
    printf("\n  -> Raw rand() value generated : %d", raw_chap_rand);
    printf("\n  -> Max chapters in %s     : %d", bible_books[random_book_index].name, max_chapters);
    printf("\n  -> Math operation             : %d %% %d", raw_chap_rand, max_chapters);
    printf("\n  -> Remainder result (0 to %d) : %d", max_chapters - 1, remainder_chap);
    printf("\n  -> Shifted result (+1 adjustment): %d", random_chapter);
    printf("\n-----------------------------------------\n");

    char target_book[32]; // FIXED: Allocated string space for target storage
    strcpy(target_book, bible_books[random_book_index].name);

    printf("\n=========================================\n");
    printf("FINAL RESULT: %s Chapter %d\n", target_book, random_chapter);
    printf("=========================================\n\n");

    // 3. Open the Bible text file and display verses I really need to find a proper bible text or fix my own this could take a long fucking time
    FILE *file = fopen("bible-kjv.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open 'bible-kjv.txt'.\n");
        printf("Please ensure the text file is in the same directory as this program.\n");

        printf("\n=========================================\n");
        system("pause");
        return 1;
    }

    char line[1024]; // FIXED: Array bounds set properly (I vibed this 100%)
    char search_prefix[64]; // FIXED: Array bounds set properly (This was vibed too pls forgive my sins)
    sprintf(search_prefix, "%s %d:", target_book, random_chapter);
    int target_len = strlen(search_prefix);
    int verse_found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, search_prefix, target_len) == 0) {
            printf("%s", line);
            verse_found = 1;
        }
    }

    if (!verse_found) {
        printf("Could not find text entries matching %s.\n", search_prefix);
    }

    fclose(file);

    // FORCE WINDOWS PAUSE
    printf("\n=========================================\n");
    system("pause");

    return 0;
}
