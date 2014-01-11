list
====

A simple list implementation in C.

Usage example
-------------

    struct list *aList = NULL;
    int a = 12;

    if(list_init(&aList) != 0) {
      perror("Error on list initialization");
      exit(EXIT_FAILURE);
    }

    list_add(aList, &a);
