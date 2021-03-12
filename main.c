#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "primitives.h"
#include "Lists/simple_linked_list.h"


typedef struct SplitString {
    char **words;
    int length;
} SplitString;


char *input(char *message) {
    if (message != NULL) {
        printf("%s", message);
    }
    char *in = malloc(sizeof(char));
    int index = 0;
    int c = fgetc(stdin);
    if (c == '\n') {
        return "\0";
    }
    while (c != EOF) {
        in[index] = c;
        index++;
        c = fgetc(stdin);
        in = realloc(in, (index + 1) * sizeof(char));
        if (c == '\n') {
            break;
        }
    }
    in[index] = '\0';
    return in;
}

void print_result(SimpleLinkedList *result) {
    ListNode *current = result->start;
    for (int index = 0; index < result->length; index++) {
        printf("[%d:%d]", ((int *) current->value)[0], ((int *) current->value)[1]);
        current = current->next;
    }
    printf("\n");
}


struct SplitString *split(char *s, char *sep) {
    struct SplitString *result = malloc(sizeof(struct SplitString));
    result->words = malloc(sizeof(char *));
    result->length = 0;
    int index = 0;
    char *word = strtok(s, sep);
    if (word == NULL) {
        result->words[index] = s;
        result->length++;
        return result;
    }
    result->words[index] = word;
    result->length++;
    index++;
    result->words = realloc(result->words, (result->length + 1) * sizeof(char *));

    word = strtok(NULL, sep);
    while (word != NULL) {
        result->words[index] = word;
        result->length++;
        word = strtok(NULL, sep);
        index++;
        result->words = realloc(result->words, (result->length + 1) * sizeof(char *));
    }

    return result;
}

SimpleLinkedList *copy_list(SimpleLinkedList *original) {
    SimpleLinkedList *result = SimpleLinkedList_new();
    ListNode *current = original->start;
    for (int index = 0; index < original->length; index++) {
        SimpleLinkedList_append(result, current->value, current->value_size);
        current = current->next;
    }
    return result;
}

SimpleLinkedList *
find_path(int target[2], int start[2], SplitString **map, size_t map_length, SimpleLinkedList *current_path) {
    SimpleLinkedList *up = NULL;
    SimpleLinkedList *down = NULL;
    SimpleLinkedList *left = NULL;
    SimpleLinkedList *right = NULL;
    SimpleLinkedList *list_copy;
    int next[2];
    if (current_path == NULL) {
        current_path = SimpleLinkedList_new();
        SimpleLinkedList_append(current_path, start, sizeof(int) * 2);
    }
    if (start[0] + 1 < map_length) {
        next[0] = start[0] + 1;
        next[1] = start[1];
        if ((next[0] == target[0]) && (next[1] == target[1])) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, target, sizeof(int) * 2);
            return list_copy;
        }
        if (strcmp(map[next[0]]->words[next[1]], "0") == 0) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, next, sizeof(int) * 2);
            map[next[0]]->words[next[1]] = "2"; // Mark it as traveled
            down = find_path(target, next, map, map_length, list_copy);
        }
    }
    if (start[0] - 1 >= 0) {
        next[0] = start[0] - 1;
        next[1] = start[1];
        if ((next[0] == target[0]) && (next[1] == target[1])) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, target, sizeof(int) * 2);
            return list_copy;
        }
        if (strcmp(map[next[0]]->words[next[1]], "0") == 0) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, next, sizeof(int) * 2);
            map[next[0]]->words[next[1]] = "2"; // Mark it as traveled
            up = find_path(target, next, map, map_length, list_copy);
        }
    }
    if (start[1] + 1 < map[0]->length) {
        next[0] = start[0];
        next[1] = start[1] + 1;
        if ((next[0] == target[0]) && (next[1] == target[1])) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, target, sizeof(int) * 2);
            return list_copy;
        }
        if (strcmp(map[next[0]]->words[next[1]], "0") == 0) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, next, sizeof(int) * 2);
            map[next[0]]->words[next[1]] = "2"; // Mark it as traveled
            right = find_path(target, next, map, map_length, list_copy);
        }
    }
    if (start[1] - 1 >= 0) {
        next[0] = start[0];
        next[1] = start[1] - 1;
        if ((next[0] == target[0]) && (next[1] == target[1])) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, target, sizeof(int) * 2);
            return list_copy;
        }
        if (strcmp(map[next[0]]->words[next[1]], "0") == 0) {
            list_copy = copy_list(current_path);
            SimpleLinkedList_append(list_copy, next, sizeof(int) * 2);
            map[next[0]]->words[next[1]] = "2"; // Mark it as traveled
            left = find_path(target, next, map, map_length, list_copy);
        }
    }
    SimpleLinkedList *shorter;
    if (up != NULL) {
        shorter = up;
    } else if (down != NULL) {
        shorter = down;
    } else if (left != NULL) {
        shorter = left;
    } else if (right != NULL) {
        shorter = right;
    } else {
        return NULL;
    }
    if (up != NULL) {
        if (up->length < shorter->length) {
            shorter = up;
        }
    }
    if (down != NULL) {
        if (down->length < shorter->length) {
            shorter = down;
        }
    }
    if (left != NULL) {
        if (left->length < shorter->length) {
            shorter = left;
        }
    }
    if (right != NULL) {
        if (right->length < shorter->length) {
            shorter = right;
        }
    }
    return shorter;
}

void solve_map(SimpleLinkedList *map) {
    int row_index = 0;
    ListNode *current = map->start;
    // Find e
    // Find m
    // Find path from m to e
    int e_coordinates[2] = {-1, -1};
    int m_coordinates[2] = {-1, -1};
    while (current != NULL) {
        for (int column_index = 0; column_index < ((SplitString *) current->value)->length; column_index++) {
            if (strcmp(((SplitString *) current->value)->words[column_index], "e") == 0) {
                e_coordinates[0] = row_index;
                e_coordinates[1] = column_index;
            } else if (strcmp(((SplitString *) current->value)->words[column_index], "m") == 0) {
                m_coordinates[0] = row_index;
                m_coordinates[1] = column_index;
            }
        }
        current = current->next;
        row_index += 1;
    }
    if (m_coordinates[0] != -1 && e_coordinates[0] != -1) {
        SimpleLinkedList *result = find_path(e_coordinates, m_coordinates,
                                             (SplitString **) SimpleLinkedList_to_array(map),
                                             map->length, NULL);
        if (result != NULL) {
            print_result(result);
        }
        return;
    }
    printf("No path found\n");
}


/*
1 1 1 1 1 1
1 1 1 0 0 e
1 0 0 0 0 1
1 0 0 m 1 1
1 1 1 1 1 1

e 1 1 1 1 1
1 1 1 0 0 1
1 0 0 0 0 1
1 0 0 m 1 1
1 1 1 1 1 1

1 1 1 1 1 1
1 1 1 0 0 1
1 0 0 0 e 1
1 0 0 m 1 1
1 1 1 1 1 1
 */

int main() {
    SimpleLinkedList *map = SimpleLinkedList_new();
    char *line;
    SplitString *nodes;
    while (TRUE) {
        line = input("");
        if (strlen(line) == 0) {
            break;
        }
        nodes = split(line, " ");
        SimpleLinkedList_append(map, nodes, 0);
    }
    if (map->length > 0) {
        solve_map(map);
        return 0;
    }
    return 1;
}
