#include "book.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/**
 * \brief Initializes a book for the collection.
 *
 * \param p_book The book to be initialized.
 * \param p_id The book identifier string
 * \param p_title The book title string
 * \param p_author The book author string
 * \param release The release date of the book
 * \returns 0 if the book identifier is not valid. The identifier is invalid
 * 			  if the stated book identifier has more than 9 characters.
 * \returns 1 if the book can be initialized.
 */
int init_book(struct book *p_book,
			  const char *p_id,
			  const char *p_title,
			  const char *p_author,
			  struct date release)
{
  p_book = malloc(sizeof(struct book));
  if(strlen(p_id) > 9)
    return 0;

  p_book->title = malloc(strlen(p_title)+1);
  strcpy(p_book->title, p_title);

  //p_book->author = malloc(strlen(p_author)+1);
  strcpy(p_book->author, p_author);

  strcpy(p_book->id, p_id);
  p_book->release_date=release;

  return 1;
}

/**
 * \brief Adds a book to the collection. The collection is an array, and the
 * array should be reallocated to store the new book.
 *
 * \param collection The array of books representing the collection
 * \param size The number of books in the current collection
 * \param new_book The new book to be copied to the collection
 * \return A pointer to enlarged collection
 */
struct book *add_to_collection(struct book *collection,
							   unsigned int size,
							   struct book new_book)
{
  struct book* new_collection = NULL;
  new_collection = malloc(size*sizeof(struct book));
  new_collection = realloc(collection, (sizeof(struct book)*(size+1)));  
  new_collection[size] = new_book;
  return new_collection;
}
