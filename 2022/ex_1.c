#include <string.h>
#include <stdlib.h>

Manager manager;

void init_manager() {
  manager.customers = NULL;
  manager.numCustomers = 0;
  manager.songs = NULL;
  manager.numSongs = 0;
}

int add_song(const char *name, Music_genre gn, int year) {
  for (int i = 0; i < manager.numSongs; i++) {
    if (strcmp(manager.songs[i].name, name) == 0) return -1;
  }

  Song newSong;
  newSong.name = (char*)malloc((strlen(name + 1) * sizeof(char)));
  strcpy(newSong.name, name);
  newSong.mg = gn;
  newSong.ReleaseYear = year;
  newSong.Popularity = 0;

  manager.songs = (Song*)realloc(manager.songs, (manager.numSongs + 1) * sizeof(Song));
  manager.songs[manager.numSongs] = newSong;
  manager.numSongs++;
  return 0;
}

typedef int(*compare)(Song*, Song*);

void sortPlaylist(PlayItem *playlist, compare cmp) {
  PlayItem *temp = playlist;
  Song *tempSong = NULL;

  if (temp == NULL) return NULL;
  while (temp->next != NULL) {
    if (compare(temp, temp->next) > 0) {
      tempSong = temp->mySong;
      temp->mySong = temp->next->mySong;
      temp->next->mySong = tempSong;
      temp = playlist;
    }
  }
}

int compName(Song *first, Song *second) {
  return strcmp(first, second);
}
int compYear(Song *first, Song *second) {
  return first->ReleaseYear - second->ReleaseYear;
}
int compPop(Song *first, Song *second) {
  return first->Popularity - second->Popularity;
}
PlayItem *create_Playlist(Music_genre gn, compare cmp, int *numSongs) {
  PlayItem *playlist = (PlayItem*)malloc(sizeof(PlayItem));
  playlist.next = NULL;
  PlayItem *temp = playlist;
  int songCount = 0;

  for (int i = 0; i < manager.numSongs; i++) {
    PlayItem newItem;
    Song *song = &(manager.songs[i]);
    song->Popularity++;
    if (song->mg != gn) continue;
    while (temp->next != NULL) temp = temp->next;

    newItem->mySong = song;
    newItem->next = NULL;
    temp->next = newItem;
    songCount++;
  }
  (*numSongs) = songCount;
  sortPlaylist(playlist, cmp);
  return playlist;
}

int add_user(const char *name, Music_genre gn, Param pm) {
  int numOfSongs = 0;
  compare cmp;
  Customer newCustomer;

  for (int i = 0; i < manager.numCustomers; i++) {
    if (strcmp(name, manager.customers[i]) == 0) return -1;
  }

  manager.customers = (Customer*)realloc(
    manager.customers,
    (manager.numCustomers + 1) * sizeof(Customer)
  );

  if (pm == Sname) cmp = compName;
  if (pm == Syear) cmp = compYear;
  if (pm == Spop) cmp = compPop;

  newCustomer.name = (char*)malloc((strlen(name) + 1) * sizeof(char));
  strcpy(newCustomer.name, name);
  newCustomer.id = id;
  newCustomer.playlist = create_Playlist(gn, cmp, &numOfSongs);

  manager.customers[manager.numCustomers] = newCustomer;

  manager.customers++;
  return numOfSongs;
}

int remove_customer(int ID) {
  int isFoundCustomer = 0;
  int addingCustomerIndex = 0;
  Customer *newCustomers = NULL;
  PlayItem *temp = NULL;
  PlayItem *prev = NULL;

  for (int i = 0; i < manager.numCustomers; i++) {
    if (manager.customers[i].ID == ID) isFoundCustomer = 1;
  }
  if (!isFoundCustomer) return -1;
  newCustomers = (Customer*)malloc((manager.numCustomers - 1) * sizeof(Customer));
  for (int i = 0; i < manager.numCustomers; i++) {
    if (manager.customers[i].ID == ID) {
      temp = manager.customers[i].playlist;
      while (temp != NULL) {
        temp->Popularity--;
        prev = temp;
        temp = temp->next;
        free(prev);
      }
      free(manager.customers[i].name);
      continue;
    }
    newCustomers[addingCustomerIndex] = manager.customers[i];
  }
  free(manager.customers);
  manager.customers = newCustomers;
  manager.numCustomers--;
  return 0;
}

void clear_manager() {
  for (int i = 0; i < manager.numCustomers) {
    remove_customer(manager.customers[i].ID);
  }
  free(manager.customers);
  for (int i = 0; i < manager.numSongs; i++) {
    free(manager.songs[i].name)
  }
  free(manager.songs);
  manager.numCustomers = 0;
  manager.customers = NULL;
  manager.numSongs = 0;
  manager.songs = NULL;
}
