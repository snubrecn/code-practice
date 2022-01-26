/*
 * Title is an unlimited string.
 * (Production) Year is an integer in the range [0, 2020]
 * Rating is an integer in the range [0, 10]
 * Running time is an integer.
 *
 * API requirements
 * 1. Add a movie in the database.
 * 2. Given a title, show the production year, rating and running time.
 * 3. Given a year, show all movies in descending order of rating
 *    If ratings are the same, show in ascending order of running time.
 * 4. Given a rating, show all movies in ascending order of year.
 *    If years are the same, show in ascending order of running time.
 */

#include <malloc.h>

#include <iostream>
#define MAX_TABLE 10
#define MAX_YEAR 2020
#define MAX_RATING 10

int StrCmp(const char* str_1, const char* str_2) {
  int i = 0;
  while (str_1[i]) {
    if (str_1[i] != str_2[i]) {
      break;
    }
    i++;
  }
  if (str_1[i] > str_2[i]) {
    return 1;
  } else if (str_1[i] < str_2[i]) {
    return -1;
  }
  return 0;
}

void StrCpy(char* dst, const char* src) {
  while (*dst++ = *src++)
    ;
}

int StrLen(const char* str) {
  int i = 0;
  while (str[i++])
    ;
  return i - 1;
}

struct Movie {
  Movie(const char* title, int year, int rating, int running_time)
      : year_(year), rating_(rating), running_time_(running_time) {
    title_ = new char[StrLen(title) + 1];
    StrCpy(title_, title);
  }
  ~Movie() {
    if (title_) {
      delete[] title_;
      title_ = NULL;
    }
  }
  Movie(const Movie& movie)
      : year_(movie.year_), rating_(movie.rating_), running_time_(movie.running_time_) {
    title_ = new char[StrLen(movie.title_) + 1];
    StrCpy(title_, movie.title_);
  }
  Movie& operator=(const Movie& movie) {
    year_ = movie.year_;
    rating_ = movie.rating_;
    running_time_ = movie.running_time_;

    title_ = new char[StrLen(movie.title_) + 1];
    StrCpy(title_, movie.title_);

    return *this;
  }

  char* title_;
  int year_;
  int rating_;
  int running_time_;
};

struct Node {
  Movie* movie;
  Node* prev;
  Node* next;
};

struct List {
  Node* head;
  Node* tail;
};

List* titles[MAX_TABLE];
List* years[MAX_YEAR + 1];
List* ratings[MAX_RATING + 1];

unsigned long Hash(const char* str) {
  unsigned long hash = 5381;
  int c;
  while (c = *str++) {
    hash = (((hash << 5) + hash) + c) % MAX_TABLE;
  }
  return hash % MAX_TABLE;
}

void InitList(List** list_ptr, int length) {
  for (size_t i = 0; i < length; i++) {
    list_ptr[i] = new List;
    list_ptr[i]->head = new Node;
    list_ptr[i]->tail = new Node;

    list_ptr[i]->head->next = list_ptr[i]->tail;
    list_ptr[i]->head->prev = NULL;
    list_ptr[i]->tail->prev = list_ptr[i]->head;
    list_ptr[i]->tail->next = NULL;
  }
}

void Init() {
  InitList(titles, MAX_TABLE);
  InitList(years, MAX_YEAR + 1);
  InitList(ratings, MAX_RATING + 1);
}

void LinkAtFront(Node* new_node, Node* curr) {
  new_node->next = curr;
  new_node->prev = curr->prev;
  curr->prev->next = new_node;
  curr->prev = new_node;
}

Node* Search(const char* title) {
  int key = Hash(title);
  Node* curr = titles[key]->head->next;
  while (curr->next) {
    curr->movie->title_;
    if (StrCmp(title, curr->movie->title_) == 0) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

void Add(const Movie& movie) {
  if (Search(movie.title_)) {
    std::cout << movie.title_ << " already in the DB.\n";
    return;
  }

  int key = Hash(movie.title_);

  Movie* new_movie = new Movie(movie);
  Node* new_title_node = new Node;
  Node* new_year_node = new Node;
  Node* new_rating_node = new Node;

  new_title_node->movie = new_movie;
  new_year_node->movie = new_movie;
  new_rating_node->movie = new_movie;

  // Add to the Title Table
  Node* curr = titles[key]->head->next;
  LinkAtFront(new_title_node, curr);

  // Add to the Year Table
  curr = years[movie.year_]->head->next;

  while (curr->next) {
    if (movie.rating_ > curr->movie->rating_) {
      LinkAtFront(new_year_node, curr);
      break;
    } else if (movie.rating_ == curr->movie->rating_) {
      while (curr->next) {
        if (movie.running_time_ <= curr->movie->running_time_ ||
            movie.rating_ != curr->movie->rating_) {
          LinkAtFront(new_year_node, curr);
          break;
        }
        curr = curr->next;
      }
      break;
    }
    curr = curr->next;
  }
  if (curr->next == NULL) {  // curr is tail
    LinkAtFront(new_year_node, curr);
  }

  // Add to the Rating Table
  curr = ratings[movie.rating_]->head->next;
  while (curr->next) {
    if (movie.year_ < curr->movie->year_) {
      LinkAtFront(new_rating_node, curr);
      break;
    } else if (movie.year_ == curr->movie->year_) {
      while (curr->next) {
        if (movie.running_time_ <= curr->movie->running_time_ ||
            movie.year_ != curr->movie->year_) {
          LinkAtFront(new_rating_node, curr);
          break;
        }
        curr = curr->next;
      }
      break;
    }
    curr = curr->next;
  }
  if (curr->next == NULL) {  // curr is tail
    LinkAtFront(new_rating_node, curr);
  }
}

void ShowMovieInfo(const char* title) {
  Node* movie_node = Search(title);

  if (movie_node) {
    std::cout << movie_node->movie->title_ << " was produced in " << movie_node->movie->year_
              << " and rated at " << movie_node->movie->rating_ << ".\n";
    std::cout << "Its running time is " << movie_node->movie->running_time_ << " minutes\n\n";
  } else {
    std::cout << "Movie " << title << " is not in the DB.\n\n";
  }
}

void ShowMoviesInYear(const int year) {
  Node* curr = years[year]->head->next;

  if (curr->next) {
    std::cout << "Movies produced in " << year << "\n";
    while (curr->next) {
      std::cout << "'" << curr->movie->title_ << " (" << curr->movie->rating_ << ", "
                << curr->movie->running_time_ << " mins)'\n";
      curr = curr->next;
    }
    std::cout << "\n";
  } else {
    std::cout << "There are no movies in year " << year << "\n\n";
  }
}

void ShowMoviesAtRating(const int rating) {
  Node* curr = ratings[rating]->head->next;
  if (curr->next) {
    std::cout << "Movies at rating " << rating << "\n";
    while (curr->next) {
      std::cout << "'" << curr->movie->title_ << " (" << curr->movie->year_ << ", "
                << curr->movie->running_time_ << " mins)'\n";
      curr = curr->next;
    }
    std::cout << "\n";
  } else {
    std::cout << "There are no movies at rating " << rating << "\n\n";
  }
}

void Free() {
  for (size_t i = 0; i < MAX_TABLE; i++) {
    Node* pos = titles[i]->head->next;
    while (pos) {
      if (pos->next) {
        free(pos->movie);
        free(pos->prev);
      } else {
        free(pos->prev);
      }
      pos = pos->next;
    }
    free(titles[i]->tail);
    free(titles[i]);
  }
  for (size_t i = 0; i <= MAX_YEAR; i++) {
    Node* pos = years[i]->head->next;
    while (pos) {
      free(pos->prev);
      pos = pos->next;
    }
    free(years[i]->tail);
    free(years[i]);
  }
  for (size_t i = 0; i <= MAX_RATING; i++) {
    Node* pos = ratings[i]->head->next;
    while (pos) {
      free(pos->prev);
      pos = pos->next;
    }
    free(ratings[i]->tail);
    free(ratings[i]);
  }
}

int main(void) {
  Init();

  Movie m1("Snowpiercer", 2013, 8, 125);
  Movie m2("Man of Steel", 2013, 8, 143);
  Movie m3("Berlin", 2013, 7, 120);

  Movie m4("John Wick 1", 2014, 8, 107);
  Movie m5("Interstellar", 2014, 10, 169);

  Movie m6("Kingsman", 2015, 9, 128);
  Movie m7("Mad Max", 2015, 8, 120);
  Movie m8("Marsian", 2015, 7, 144);
  Movie m9("Age of Ultron", 2015, 7, 141);

  Movie m10("Civil War", 2016, 9, 147);
  Movie m11("Doctor Strange", 2016, 7, 115);
  Movie m12("Zootopia", 2016, 10, 108);
  Movie m13("LalaLand", 2016, 8, 127);

  Movie m14("John Wick 2", 2017, 9, 122);
  Movie m15("Thor 3", 2017, 9, 130);

  Movie m16("Infinity War", 2018, 10, 149);
  Movie m17("Black Panther", 2018, 8, 135);

  Movie m18("Endgame", 2019, 9, 181);

  Add(m1);
  Add(m2);
  Add(m3);
  Add(m4);
  Add(m5);
  Add(m6);
  Add(m7);
  Add(m8);
  Add(m9);
  Add(m10);
  Add(m11);
  Add(m12);
  Add(m13);
  Add(m14);
  Add(m15);
  Add(m16);
  Add(m17);
  Add(m18);

  ShowMovieInfo("Mad Max");
  ShowMovieInfo("John Wick 2");
  ShowMovieInfo("Lord of War");

  for (int i = 2008; i <= 2019; i++) {
    ShowMoviesInYear(i);
  }

  for (int i = 10; i >= 0; i--) {
    ShowMoviesAtRating(i);
  }

  Free();
  return 0;
}
