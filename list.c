#include <stdlib.h>
#include "list.h"
#include <stdio.h>

int
list_init(struct list **list) {
    *list = NULL;

    /* Allocate the space for the list. */
    *list = malloc(sizeof(**list));

    /* Check if everything went right. */
    if(*list == NULL) {
        return 1;
    }

    /* Fill the list with the starting values. */
    (*list)->first_element = NULL;
    (*list)->last_element = NULL;
    (*list)->size = 0;

    return 0;
}

void
list_destroy(struct list **list) {
    struct list_element *e = (*list)->first_element;
    struct list_element *next;

    /* If the beginning is empty the list is empty return. */
    if(e == NULL) {
        return;
    }

    /* Else go through all the list elements and free them. */
    while(e != NULL) {
        /* Remember the next element. */
        next = e->next;

        /* Free the current element. */
        free(e);

        /* Go to the next element. */
        e = next;
    }

    /* Free the list. */
    free(*list);
}

int
list_remove_element(struct list *list, struct list_element *element) {
    struct list_element *e = list->first_element;

    /* If the list is empty return 1. */
    if(e == NULL || list->size == 0) {
        return 1;
    }

    if(list->first_element == element) {
        /* If it is the first element then remove it and set everything up. */
        list->first_element = element->next;
        free(element);
        return 0;
    } else {
        /* If it's an element from the middle find the previous one and set everything up. */
        while(e->next != element) {
            e = e->next;
        }
        e->next = element->next;

        /* If it is the lase element then set the lase_element pointer. */
        if(element == list->last_element) {
            list->last_element = e;
        }

        free(element);
    }

    list->size--;
    return 0;
}

size_t
list_size(struct list *list) {
    return list->size;
}


int
list_add(struct list *list, void *data) {

    /* Create the element. */
    struct list_element *e = NULL;

    e = malloc(sizeof(*e));

    /* Check if memory allocated properly. */
    if(e == NULL) {
        return 1;
    }

    /* Fill the element's data. */
    e->data = data;
    e->next = NULL;

    /* Put it in the list as the first element if it is the first element. */
    if(list->first_element == NULL) {
        list->first_element = e;
        list->last_element = e;
    } else {
        /* Or as the last element otherwise. */
        list->last_element->next = e;
        list->last_element = e;
    }

    /* Increase the number of elements in the list. */
    list->size++;

    return 0;
}

struct list_element*
list_get(struct list *list, size_t n) {
    size_t i = 0;
    struct list_element *e = list->first_element;

    for(i = 0; i < n; i++) {
        e = e->next;
    }

    return e;
}


void*
list_remove_position(struct list *list, size_t n) {
    size_t i = 0;
    struct list_element *previous_element = NULL;
    struct list_element *next_element = NULL;
    struct list_element *e = list->first_element;
    void *data = NULL;

    if(e == NULL || n > list->size) {
        return NULL;
    }

    next_element = e->next;

    for(i = 0; i < n; i++) {
        previous_element = e;
        e = e->next;
        next_element = e->next;
    }

    /* It's the first element on the list. */
    if(previous_element == NULL) {
        list->first_element = next_element;
        data = e->data;
        free(e);
    } else {
        /* It's not the first element. */

        /* If it's the last element. */
        if(e == list->last_element) {
            list->last_element = previous_element;
        }

        previous_element->next = next_element;
        data = e->data;
        free(e);
    }

    list->size--;

    return data;
}

int
list_remove_data(struct list *list, void *data) {
    struct list_element *e = list->first_element;
    struct list_element *temp = list->first_element;

    /* If the list is empty return 1. */
    if(e == NULL || list->size == 0) {
        return 1;
    }

    if(list->first_element->data == data) {
        /* If it is the first element then remove it and set everything up. */
        list->first_element = list->first_element->next;
        free(e);
        return 0;
    } else {
        /* If it's an element from the middle find the previous one and set everything up. */
        while(e->next->data != data) {
            e = e->next;
        }
        temp = e->next;
        e->next = temp->next;

        /* If it is the lase element then set the lase_element pointer. */
        if(list->last_element->data == data) {
            list->last_element = e;
        }

        free(temp);
    }

    list->size--;
    return 0;
}

void
list_foreach_data(struct list *list, void(*func)(void *)) {
    struct list_element *e = list->first_element;

    while(e != NULL) {
        func(e->data);
        e = e->next;
    }

    return;
}


void
list_foreach_element(struct list *list, void(*func)(struct list_element *)) {
    struct list_element *e = list->first_element;

    while(e != NULL) {
        func(e);
        e = e->next;
    }

    return;
}


struct list_element*
list_search_element(struct list *list, int(*compare)(struct list_element *)) {
    struct list_element *e = list->first_element;

    while(e != NULL) {
        if(compare(e) == 1) {
            return e;
        }
        e = e->next;
    }

    return NULL;
}


void*
list_search_data(struct list *list, int(*compare)(void *)) {
    struct list_element *e = list->first_element;

    while(e != NULL) {
        if(compare(e->data) == 1) {
            return e->data;
        }
        e = e->next;
    }

    return NULL;
}
