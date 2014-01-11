#ifndef LIST_H

#define LIST_H

#include <string.h>

struct list_element {
    void *data;
    struct list_element *next;
};

struct list {
    struct list_element *first_element;
    struct list_element *last_element;
    size_t size;
};

/**
 * Initialize the list, make it ready to receive elements.
 *
 * @param list - the list struct which shall be initialized
 * @return 0 if initialization was successful, 1 otherwise
 */
int list_init(struct list **list);

/**
 * Free the list and all its elements from memory.
 *
 * @param list - the list struct which shall be freed
 */
void list_destroy(struct list **list);

/**
 * Return the number of elements in the given list.
 *
 * @param list - the list
 * @return number of elements on the list
 */
size_t list_size(struct list *list);

/**
 * Add the given pointer as data to the given list.
 *
 * @param list - the list to which the data will be added
 * @param data - the data which will be added
 * @return 1 in case of error, 0 otherwise
 */
int list_add(struct list *list, void *data);

/**
 * Remove the first occurence of the given element in the list.
 *
 * @param list - the list from which the data shall be removed
 * @param element - the element which shall be removed
 * @return 1 in case of error 0 otherwise
 */
int list_remove_element(struct list *list, struct list_element *element);

/**
 * Remove the nth element on the list.
 *
 * @param list - the list from which the data shall be removed
 * @param n - the position of the element which shall be removed
 * @return the pointer to the data if the element was successfuly removed, NULL otherwise
 */
void* list_remove_position(struct list *list, size_t n);

/**
 * Remove the first occurence of the element with the given data pointer from the list.
 *
 * @param list - the list from which the data shall be removed
 * @param data - the pointer to the data
 * @return 0 if the element was successfuly removed, 1 otherwise
 */
int list_remove_data(struct list *list, void *data);

/**
 * Returns the pointer to the nth element of the given list.
 *
 * @param list - the list
 * @param n - the position of the element from the beginning
 * @return the pointer to the element or NULL in case of errors
 */
struct list_element* list_get(struct list *list, size_t n);


/**
 * Perform the function func for each data on the list.
 *
 * @param list - the list
 * @param func - the function
 */
void list_foreach_data(struct list *list, void(*func)(void *));

/**
 * Perform the function func for each element on the list.
 *
 * @param list - the list
 * @param func - the function
 */
void list_foreach_element(struct list *list, void(*func)(struct list_element *));

/**
 * Return a pointer to the first element for which the compare function returned 1.
 *
 * @param list - the list
 * @param compare - the comparation function
 * @return the first element for which the function returned 1, NULL otherwise
 */
struct list_element* list_search_element(struct list *list, int(*compare)(struct list_element *));

/**
 * Return a pointer to the first data for which the compare function returned 1.
 *
 * @param list - the list
 * @param compare - the comparation function
 * @return the pointer to the first data for which the function returned 1, NULL otherwise
 */
void* list_search_data(struct list *list, int(*compare)(void *));


#endif /* end of include guard: LIST_H */
