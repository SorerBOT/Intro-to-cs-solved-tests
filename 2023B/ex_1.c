#include <stdlib.h>
#include <string.h>

#define MAXDUCKC 3
#define MAXSHELF 9
#define MAXCELL 26

typedef enum { yellow, blue, green, pink, orange, black } Color;

typedef struct Duck {
  int ID;
  char type[2];
  Color color;
  int loc[2];
} Duck;

typedef struct DuckItem {
  Duck *duck;
  DuckItem *next;
} DuckItem;

typedef struct DuckList {
  DuckItem *myDucks;
  int numducks;
  char type[3];
} DuckList;

typedef struct DuckStore {
  int numDuckTypes;
  DuckList *allDucks;
  int shelves[MAXSHELF][MAXCELL];
} DuckStore;

DuckStore *initStore() {
  return (DuckStore*)calloc(1, sizeof(DuckStore));
}

DuckItem *newDuck(int ID, char type[], Color color) {
  DuckItem *item = (DuckItem*)calloc(1, sizeof(DuckItem));
  item->next = NULL;
  item->duck = (Duck*)calloc(1, sizeof(Duck));
  item->duck->ID = ID;
  item->duck->color = color;
  strcpy(item->duck->type, type);
  return item;
}

int addType(DuckStore *store, char *duckType) {
  for (int i = 0; i < store->numDuckTypes; i++) {
    if (strcmp(store->allDucks[i], duckType) == 0) return i;
  }
  store->allDucks = (DuckList*)realloc(
    store->allDucks,
    (store->numDuckTypes + 1) * sizeof(DuckList)
  );
  for (int i = 0; i < store->numDuckTypes; i++) {
    if (strcmp(store->allDucks[i].type, duckType) > 0) {
      for (int j = store->numDuckTypes; j > i; j--) {
        store->allDucks[j].myDucks = store->allDucks[j-1].myDucks;
        store->allDucks[j].numducks = store->allDucks[j-1].numducks;
        
      }
      store->allDucks[i].numducks = 1;
      store->allDucks[i].myDucks = newDuck(0, duckType, yellow);
      store->numDuckTypes++;
      return i;
    }
  }
  store->allDucks[store->numDuckTypes].umducks = 0;
  store->allDucks[store->numDuckTypes].myDucks = NULL;
  store->numDuckTypes++;
  return store->numDuckTypes - 1;
}

int addDuckItem(DuckStore *store, DuckItem *newDuck) {
  newDuck->duck->loc[0] = -1;
  newDuck->duck->loc[1] = -1;
  int index = addType(store, newDuck->duck->type);
  DuckList list = store->allDucks[index];
  DuckItem *item = list.myDucks;
  while (item->next != NULL) {
    item = item->next;
    int itemShelf = item->duck->loc[0];
    int itemCell = item->duck->loc[1];
    if (store->shelves[itemShelf][itemCell] < 3) {
      newDuck->duck->loc[0] = itemShef;
      newDuck->duck->loc[1] = itemCell;
      store->shelves[itemShelf][itemCell]++;
    }
  }
  item->next = newDuck;
  list->numducks++;
  if (newDuck->duck->loc == -1) {
    for (int i = 0; i < MAXSHELF; i++) {
      for (int j = 0; j < MAXCELL; j++) {
        if (i == 0 && j == 0) continue;
        if (store->shelves[i][j] < 3) {
          newDuck->duck->loc[0] = i;
          newDuck->duck->loc[1] = j;
          store->shelves[i][j]++;
        }
      }
    }
  }
  if (newDuck->duck->loc == -1) return -1;

  return list->numducks;
}

int sellDuckRequest(DuckStore *store, char *type, Color color) {
  DuckList list;
  int found = 0;
  DuckItem *item = NULL;
  DuckItem *duckToSell = NULL;
  for (int i = 0; i < numDuckTypes; i++) {
    if (strcmp(store->allDucks[i].type, type) == 0) {
      list = store->allDucks[i];
      found = 1;
      break;
    }
  }
  if (!found) return -1;
  found = 0;
  item = list.myDucks;
  if (item == NULL) return -1;
  if (item->duck->color == color) {
    duckToSell = item;
    list.myDucks = item->next;
    found = 1;
  }
  else {
    while (item->next != NULL) {
      if (item->next->duck->color == color) {
        duckToSell = item->next;
        item->next = duckToSell->next;
        found = 1;
        break;
      }
    }
  }
  if (!found) return -1;
  list.numducks--;
  store->shelves[duckToSell->duck->loc[0]][duckToSell->duck->loc[1]]--;
  free(duckToSell->duck);
  free(duckToSell);
  return list.numducks;
}

typedef int(*comp)(Duck*, Duck*);
int compColor(Duck *first, Duck *second) {
  return first->color - second->color;
}
int compID(Duck *first, Duck *second) {
  return first->ID - second->ID;
}

void sortDucks(DuckItem *first, comp compduck) {
  DuckItem *temp = temp;
  DuckItem *next = temp->next;
  DuckItem *prev = temp;
  if (next == NULL) return;
  while (temp->next != NULL) {
    if (compduck(temp, next) < 0) {
      next = temp->next;
      temp->next = next->next;
      next->next = temp;
      prev = temp;
      temp = temp->next;
    }
    if (compduck(temp, temp->next) < 0) {
      next = temp->next;
      prev->next = next;
      temp->next = next->next;
      next->next = temp;
      // resetting
      temp = first;
      prev = first;
      next = temp->next;
      continue;
    }
    prev = temp;
    temp = temp->next;
  }
}

void duckSale(DuckStore *store) {
  DuckItem *temp = store->allDucks[0].myDucks;
  DuckList *list = (DuckList*)calloc(1, sizeof(DuckList));
  list->numducks = 0;
  list->myDucks = temp;
  strcpy(list->type, temp->type);
  for (int i = 1; i < store->numDuckTypes; i++) {
    while (temp->next != NULL) {
      list->numducks++;
      temp = temp->next;
    }
    temp->next = store->allDucks[i].myDucks;
  }
  free(store->allDucks);
  store->allDucks = list;
  comp c = compColor;
  sortDucks(store->allDucks->myDucks, c);
}

void clearAllDucks(DuckStore* store) {
  DuckItem *temp = NULL;
  DuckItem *prev = NULL;
  for (int i = 0; i < store->numDuckTypes; i++) {
    temp = store->allDucks[i].myDucks;
    while (temp != NULL) {
      prev = temp;
      temp = temp->next;
      free(prev->duck);
      free(prev);
    }
  }
  free(store->allDucks);
  free(store);
}
