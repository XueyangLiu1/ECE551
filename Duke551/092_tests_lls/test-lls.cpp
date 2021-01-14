#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.h"
void testList(void) {
  IntList lst = IntList();
  assert(lst.getSize() == 0 && lst.size == 0 && lst.head == NULL && lst.tail == NULL);
  //[]
  lst.addFront(1);
  assert(lst.getSize() == 1 && lst.size == 1 && lst.head == lst.tail &&
         lst.head != NULL && lst.head->data == 1 && lst.head->next == NULL &&
         lst.head->prev == NULL);
  //[1]
  lst.addBack(2);
  assert(lst.getSize() == 2 && lst.size == 2 && lst.head->data == 1 &&
         lst.head->next->data == 2 && lst.tail->data == 2 && lst.head->prev == NULL &&
         lst.tail->next == NULL && lst.head->next->prev == lst.head);
  //[1,2]
  lst.remove(2);
  assert(lst.getSize() == 1 && lst.size == 1 && lst.head == lst.tail &&
         lst.head != NULL && lst.head->data == 1);
  //[1]
  lst.addFront(2);
  assert(lst.getSize() == 2 && lst.size == 2 && lst.head->data == 2 &&
         lst.head->next->data == 1 && lst.tail->data == 1 && lst.find(2) == 0 &&
         lst[1] == 1 && lst.remove(3) == false);
  //[2,1]
  bool success = lst.remove(2);
  assert(success == true && lst.getSize() == 1 && lst.size == 1 && lst.head == lst.tail &&
         lst.head != NULL && lst.head->data == 1);
  //[1]
  IntList lst2 = IntList(lst);
  //[1]
  assert(lst2.getSize() == 1 && lst2.size == 1 && lst2.head == lst2.tail &&
         lst2.head != NULL && lst2.head->data == 1);
  //[1]
  lst2.addBack(2);
  assert(lst2.getSize() == 2 && lst2.size == 2 && lst2.head->data == 1 &&
         lst2.head->next->data == 2 && lst2.tail->data == 2);
  //[1,2]
  lst2.remove(2);
  assert(lst2.getSize() == 1 && lst2.size == 1 && lst2.head == lst2.tail &&
         lst2.head != NULL && lst2.head->data == 1);
  //[1]
  lst2.addFront(2);
  assert(lst2.getSize() == 2 && lst2.size == 2 && lst2.head->data == 2 &&
         lst2.head->next->data == 1 && lst2.tail->data == 1 && lst2.find(2) == 0 &&
         lst2[1] == 1 && lst2.remove(3) == false);
  //[2,1]
  success = lst2.remove(2);
  assert(success == true && lst2.getSize() == 1 && lst2.size == 1 &&
         lst2.head == lst2.tail && lst2.head != NULL && lst2.head->data == 1);
  lst2.addFront(3);
  //[3,1]
  lst2.addFront(2);
  assert(lst2.find(2) == 0 && lst2.find(3) == 1 && lst2.find(1) == 2);
  //[2,3,1]
  success = lst2.remove(3);
  assert(success == true && lst2.head->data == 2 && lst2.tail->data == 1 &&
         lst2.getSize() == 2 && lst2.size == 2 && lst2.head->next->next == NULL &&
         lst2.tail->prev->prev == NULL && lst2.head->next->prev == lst2.head &&
         lst2.tail->prev->next == lst2.tail);
  //[2,1]
  lst2.remove(2);
  //[1]
  lst2.addBack(1);
  //[1,1]
  assert(lst2.getSize() == 2 && lst2.size == 2 && lst2.head->data == 1 &&
         lst2.head->next->data == 1 && lst2.tail->data == 1 && lst2[1] == 1 &&
         lst2.remove(3) == false);
  lst = lst2;
  //[1,1]
  assert(lst.getSize() == 2 && lst.size == 2 && lst.head->data == 1 &&
         lst.head->next->data == 1 && lst.tail->data == 1 && lst[1] == 1 &&
         lst.remove(3) == false);
  lst.remove(1);
  //[1]
  assert(lst.getSize() == 1 && lst.size == 1 && lst.head == lst.tail &&
         lst.head != NULL && lst.head->data == 1 && lst.find(2) == -1);
  lst.remove(1);
  //[]
  assert(lst.getSize() == 0 && lst.size == 0 && lst.head == NULL && lst.tail == NULL);
  for (int i = 0; i < 5; i++) {
    lst.addBack(i);
  }
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
