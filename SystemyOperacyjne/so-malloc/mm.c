/*
 * mm.c - malloc with explicit free list, best-fit policy
 *
 * used block contains header and footer(end of payload)
 * free block contains header and footer similarly to used block, and also
 * pointers to succeeding and predeceding free blocks. Unfortunately succ and
 * pred are not actually pointers, because when they were pointers (word_t *),
 * sizeof(free_t) == 24, which is more than 16 (ALIGNMENT). This forced me to
 * store word_t as succ and pred, meaning offset from root (first element of
 * heap) and recalculate values from words to free_t * and vice versa. Freeing
 * block means coalescing it with adjacent free blocks and fixing free list
 * appropriately, assigning block means setting header and footer, then removing
 * it from free list.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
//#define DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

typedef int32_t word_t; /* Heap is bascially an array of 4-byte words. */

typedef struct {
  word_t header;
  /*
   * We don't know what the size of the payload will be, so we will
   * declare it as a zero-length array.  This allow us to obtain a
   * pointer to the start of the payload.
   */
  uint8_t payload[];
} block_t;

// struct for free blocks
typedef struct {
  word_t header;
  word_t pred; // offset from root pointer
  word_t succ;
  uint8_t payload[];
} free_t;

typedef enum {
  FREE = 0,     /* Block is free */
  USED = 1,     /* Block is used */
  PREVFREE = 2, /* Previous block is free (optimized boundary tags) */
} bt_flags;

const static int INF = 1e9;

static block_t *heap_start; /* Address of the first block */
static block_t *heap_end;   /* Address past last byte of last block */
static block_t *last;       /* Points at last block */

static free_t *root; // root element of explicit free list

/*
 * Various helping functions
 */

static size_t round_up(size_t size) {
  return (size + ALIGNMENT - 1) & -ALIGNMENT;
}

static size_t get_size(block_t *bt) {
  return bt->header & -4;
}
static size_t get_size_free(free_t *bt) {
  return bt->header & -4;
}
static size_t get_size_word(word_t *bt) {
  return *bt & -4;
}

static size_t get_size_footer(word_t *ft) {
  // debug("getsizefooter footer: %p, content:%d\n", ft, *ft);
  return (*ft) & ~(USED | PREVFREE);
}

/*static inline int block_used(block_t *bt) {
  return bt->header & USED;
}*/
static inline int block_free(word_t *bt) {
  return !(*bt & USED);
}

static inline int word_blockused(word_t *wt) {
  return *wt & USED;
}
static inline int word_blockfree(word_t *wt) {
  return !(*wt & USED);
}

static word_t *next_block(word_t *bt) {
  return bt + get_size_word(bt) / sizeof(word_t);
}

static word_t *prev_block(word_t *bt) {
  word_t *ft = (void *)bt - sizeof(word_t); // footer of previous block
  return (word_t *)(ft -
                    (get_size_footer(ft) - sizeof(word_t)) / sizeof(word_t));
}

static void set_header(block_t *block, size_t size, bt_flags is_allocated) {
  block->header = size | is_allocated;
}
static void set_header_free(free_t *block, size_t size, bt_flags is_allocated) {
  block->header = size | is_allocated;
}

static inline word_t *get_footer(block_t *bt) {
  return (void *)bt + get_size(bt) - sizeof(word_t);
}
static inline word_t *get_footer_free(free_t *bt) {
  return (void *)bt + get_size_free(bt) - sizeof(word_t);
}

static inline void set_footer(block_t *bt, size_t size, bt_flags is_allocated) {
  *(get_footer(bt)) = size | is_allocated;
  /*debug("set_footer bt: %p, get_footer(bt): %p, *getfooter: %d\n", bt,
        get_footer(bt), *get_footer(bt));*/
}
static inline void set_footer_free(free_t *bt, size_t size,
                                   bt_flags is_allocated) {
  *(get_footer_free(bt)) = size | is_allocated;
}

// returns pointer to free block from offset(word_t)
static free_t *ptrfromword(word_t w) {
  // debug("ptrfromword w:%d, root:%p, root + w:%p, w/sizeof(free_t):%ld, root +
  // w / sizeof(free_t):%p, ((word_t *)root + w / sizeof(word_t):%p\n", w, root,
  // root + w, w/sizeof(free_t), root + w / sizeof(free_t), ((word_t *)root + w
  // / sizeof(word_t)));
  return (free_t *)((word_t *)root + w / sizeof(word_t)); //????
}
// reversing previous function
static word_t wordfromptr(free_t *p) {
  // debug("wordfromptr p:%p, root:%p, p - root:%ld, ((word_t)((void *)p - (void
  // *)root)): %d\n", p, root, (void *)p - (void *)root, ((word_t)((void *)p -
  // (void *)root)));
  return ((word_t)((void *)p - (void *)root));
}

// deleting free block from list
static void del_freeblock(free_t *bt) {
  free_t *succbt = ptrfromword(bt->succ);
  free_t *predbt = ptrfromword(bt->pred);
  predbt->succ = wordfromptr(succbt);
  succbt->pred = wordfromptr(predbt);
}

// adding free block to list
static void add_freeblock(free_t *bt) {
  free_t *succroot = ptrfromword(root->succ);
  root->succ = wordfromptr(bt);
  succroot->pred = wordfromptr(bt);
  bt->succ = wordfromptr(succroot);
  bt->pred = wordfromptr(root);
}

// coalescing free block (after freeing bt) and adding/deleting free blocks from
// list
static void coalesce(free_t *bt) {
  word_t *nextbt = next_block((word_t *)bt);
  word_t *prevbt = prev_block((word_t *)bt);
  size_t prevsize = get_size_word(prevbt);
  size_t nextsize = get_size_word(nextbt);
  size_t btsize = get_size_free(bt);
  // free_t *succbt = (free_t *)bt->succ;
  // free_t *predbt = (free_t *)bt->pred;

  if (word_blockused(prevbt) && word_blockused(nextbt)) {
    debug("obydwa obok zajete\n");
    add_freeblock(bt);
  }

  if (word_blockfree(prevbt) && word_blockused(nextbt)) {
    del_freeblock((free_t *)prevbt);
    set_header_free((free_t *)prevbt, prevsize + btsize, FREE);
    set_footer_free((free_t *)prevbt, prevsize + btsize, FREE);
    add_freeblock((free_t *)prevbt);
  }

  if (word_blockused(prevbt) && word_blockfree(nextbt)) {
    del_freeblock((free_t *)nextbt);
    set_header_free(bt, btsize + nextsize, FREE);
    set_footer_free(bt, btsize + nextsize, FREE);
    add_freeblock(bt);
  }

  if (word_blockfree(prevbt) && word_blockfree(nextbt)) {
    del_freeblock((free_t *)prevbt);
    del_freeblock((free_t *)nextbt);
    set_header_free((free_t *)prevbt, prevsize + btsize + nextsize, FREE);
    set_footer_free((free_t *)prevbt, prevsize + btsize + nextsize, FREE);
    add_freeblock((free_t *)prevbt);
  }
}

// explicit free list initialization
static inline void initlist() {
  size_t listheadsize = round_up(sizeof(free_t));
  root = mem_sbrk(listheadsize);
  set_header_free(root, listheadsize, FREE);
  set_footer_free(root, listheadsize, FREE);
  root->succ = 0;
  root->pred = 0;
}

// heap printing
static inline void printheap() {
  debug("[PRINT]heap blocks:\n");
  word_t *p = (word_t *)heap_start;
  while (get_size_word(p) != 0) {
    debug("%p - %p, %d, header:%d\n", p, p + get_size_word(p) / sizeof(word_t),
          *p & USED, *p);
    p = next_block(p);
  }

  debug("[ehh]sizeof(free_t):%ld, sizeof(word_t *):%ld, sizeof(void *):%ld\n",
        sizeof(free_t), sizeof(word_t *), sizeof(void *));
  debug("[PRINT]free list:\n");
  free_t *f = root;
  do {
    debug("%p - %p, %d, header:%d, successor:%p, predecessor:%p\n", f,
          f + get_size_free(f) / sizeof(word_t), *p & USED, f->header,
          ptrfromword(f->succ), ptrfromword(f->pred));
    f = ptrfromword(f->succ);
  } while (f != root);
}

/*
 * mm_init - Called when a new trace starts.
 */
int mm_init(void) {
  /* Pad heap start so first payload is at ALIGNMENT. */
  if ((long)mem_sbrk(ALIGNMENT - offsetof(block_t, payload)) < 0)
    return -1;

  // initializing explicit free list
  initlist();

  // make prologue block
  size_t prologue_size = round_up(2 * sizeof(word_t));
  heap_start = mem_sbrk(prologue_size);
  set_header(heap_start, prologue_size, USED);
  set_footer(heap_start, prologue_size, USED);
  last = heap_start;

  heap_end = mem_sbrk(round_up(sizeof(word_t)));
  set_header(heap_end, 0, USED); // epilogue block
  heap_end = mem_sbrk(0);

  return 0;
}

/*
 * malloc - Allocate a block by incrementing the brk pointer.
 *      Always allocate a block whose size is a multiple of the alignment.
 */
void *malloc(size_t size) {
  // mm_checkheap(1);

  size = round_up(sizeof(block_t) + sizeof(word_t) + size);

  // search for free block
  free_t *currentblock = ptrfromword(root->succ);
  free_t *bestblock = currentblock;
  size_t bestblocksize = (int)INF;
  do {
    size_t cursize = get_size_free(currentblock);
    if (size <= cursize) // free block with enough space
    {
      if (cursize < bestblocksize) {
        bestblocksize = cursize;
        bestblock = currentblock;
      }
    }
    currentblock = ptrfromword(currentblock->succ);
  } while (currentblock != root);
  debug("na koniec currentblock: %p, bestblock:%p, bestblocksize:%ld, "
        "heap_end: %p\n",
        currentblock, bestblock, bestblocksize, heap_end);

  if (bestblocksize != INF) // if some bestblock found
    currentblock = bestblock;

  block_t *block;

  // no free block found
  if (currentblock == root) {
    debug("nowy blok!\n");

    block = mem_sbrk(size - round_up(sizeof(word_t))) -
            round_up(sizeof(word_t)); // not mem_sbrk(size) because of epilogue
                                      // block on end, which needs to be
    if ((long)block < 0)
      return NULL;

    set_header(block, size, USED);
    set_footer(block, size, USED);
    last = block;

    // epilogue block
    heap_end = mem_sbrk(round_up(sizeof(word_t)));
    set_header(heap_end, 0, USED);
    heap_end = mem_sbrk(0);
  } else // some free block found
  {
    block = (block_t *)currentblock;
    size_t prevsize = get_size(block);
    size_t leftspace = prevsize - size;

    debug("dodawanie do free bloka\nblock: %p, size: %ld, block + size / "
          "sizeof(wordt): %p, leftspace: %ld\n",
          block, size, block + size / sizeof(word_t), prevsize - size);

    // some space left in free block, so we have to move header and succ,pred
    if (leftspace > sizeof(free_t)) // a moze 16?
    {
      free_t *fblock =
        (free_t *)((word_t *)currentblock + size / sizeof(word_t));
      fblock->succ = currentblock->succ;
      fblock->pred = currentblock->pred;
      set_header_free(fblock, leftspace, FREE);
      set_footer_free(fblock, leftspace, FREE);

      free_t *predblock = ptrfromword(currentblock->pred);
      predblock->succ = wordfromptr(fblock);
      free_t *nextblock = ptrfromword(currentblock->succ);
      nextblock->pred = wordfromptr(fblock);

      set_header(block, size, USED);
      set_footer(block, size, USED);
      debug("fblock:%p, header:%d\n", fblock, fblock->header);
    } else // no space left, we have to delete that block
    {
      del_freeblock(currentblock);
      set_header(block, prevsize, USED);
      set_footer(block, prevsize, USED);
      if ((word_t *)currentblock == (word_t *)last)
        last = block;
    }
  }

  // mm_checkheap(1);

  return block->payload;
}

void free(void *ptr) { // ptr jest z payload wiec trzeba zmniejszyc
  debug("robimy free\n");
  if (ptr == 0x0) // illegall call
    return;
  block_t *bptr = ptr - sizeof(word_t);
  size_t bsize = get_size(bptr);
  debug("ptr: %p, bptr: %p, bsize:%ld\n", ptr, bptr, bsize);
  set_header(bptr, bsize, FREE);
  set_footer(bptr, bsize, FREE);
  coalesce((free_t *)bptr);
}

/*
 * realloc - Change the size of the block by mallocing a new block,
 *      copying its data, and freeing the old block.
 **/
void *realloc(void *old_ptr, size_t size) {
  /* If size == 0 then this is just free, and we return NULL. */
  if (size == 0) {
    free(old_ptr);
    return NULL;
  }

  /* If old_ptr is NULL, then this is just malloc. */
  if (!old_ptr)
    return malloc(size);

  // if current block has more space than requested return it
  block_t *bptr = old_ptr - sizeof(word_t);
  size_t bsize = get_size(bptr);
  size_t realsize = round_up(sizeof(block_t) + sizeof(word_t) + size);
  if (bsize >= realsize)
    return old_ptr;

  // if realloced block is last block extend heap and return (doesnt work
  // currently)
  /*if( bptr == last )
  {
    block_t *block = mem_sbrk(round_up(realsize - bsize -
  round_up(sizeof(word_t))) - round_up(sizeof(word_t))); if ((long)block < 0)
      return NULL;

    set_header(bptr, realsize, USED);
    set_footer(bptr, realsize, USED);

    // epilogue block
    heap_end = mem_sbrk(round_up(sizeof(word_t)));
    set_header(heap_end, 0, USED);
    heap_end = mem_sbrk(0);

    return old_ptr;
  }*/

  // next block is free, so we can try to extend (also doesnt work)

  /*word_t *succeedingblock = next_block((word_t *)bptr);
  if( block_free(succeedingblock) )
  {
    free_t *nblock = (free_t *)succeedingblock;
    size_t nblocksize = get_size_free( nblock );
    if( bsize + nblocksize <= realsize ) //it fits
    {
      if( (word_t *)nblock == (word_t *)last )
        last = bptr;

      free_t *fblock =
        (free_t *)(nblock + size / sizeof(word_t));
      fblock->succ = nblock->succ;
      fblock->pred = nblock->pred;
      set_header_free(fblock, realsize - bsize - nblocksize, FREE);
      set_footer_free(fblock, realsize - bsize - nblocksize, FREE);

      free_t *predblock = ptrfromword(nblock->pred);
      predblock->succ = wordfromptr(fblock);
      free_t *nextblock = ptrfromword(nblock->succ);
      nextblock->pred = wordfromptr(fblock);

      set_header(bptr, realsize, USED);
      set_footer(bptr, realsize, USED);
    }
  }*/

  void *new_ptr = malloc(size);

  /* If malloc() fails, the original block is left untouched. */
  if (!new_ptr)
    return NULL;

  /* Copy the old data. */
  block_t *block = old_ptr - offsetof(block_t, payload);
  size_t old_size = get_size(block);
  if (size < old_size)
    old_size = size;
  memcpy(new_ptr, old_ptr, old_size);

  /* Free the old block. */
  free(old_ptr);

  return new_ptr;
}

/*
 * calloc - Allocate the block and set it to zero.
 */
void *calloc(size_t nmemb, size_t size) {
  size_t bytes = nmemb * size;
  void *new_ptr = malloc(bytes);

  /* If malloc() fails, skip zeroing out the memory. */
  if (new_ptr)
    memset(new_ptr, 0, bytes);

  return new_ptr;
}

/*
 * mm_checkheap - checking properties of heap
 */
void mm_checkheap(int verbose) {
  printheap();
  // all blocks on free list are free
  bool ok = true;
  free_t *c = root;
  do {
    if (word_blockused((word_t *)c)) {
      ok = false;
      break;
    }
    c = ptrfromword(c->succ);
  } while (c != root);

  if (!ok && verbose)
    debug("[CHECK]not all blocks on free list are free, wrong block address:%p",
          c);

  // all free blocks are on the list

  // no two adjacent free blocks
  ok = true;
  word_t *w = (word_t *)heap_start;
  bool prevfree = false;
  while (get_size_word(w) != 0) {
    if (prevfree && block_free(w)) {
      ok = false;
      break;
    }
    if (block_free(w))
      prevfree = true;
    else
      prevfree = false;
    w = next_block(w);
  }

  if (!ok && verbose)
    debug("[CHECK] there are at least two adjacent blocks, example: %p and "
          "previous\n",
          w);

  // pointers on next and previous block are referring to elements of heap
  ok = true;
  c = root;
  do {
    free_t *s = ptrfromword(c->succ);
    free_t *p = ptrfromword(c->pred);
    if ((s < 0 || (word_t *)s > (word_t *)heap_end) ||
        (p < 0 || (word_t *)p > (word_t *)heap_end)) {
      ok = false;
      break;
    }

    c = ptrfromword(c->succ);
  } while (c != root);

  if (!ok && verbose)
    debug("[CHECK] some next and previous pointers are not reffering to "
          "elements of heap, example: block=%p, pred:%p, succ:%p\n",
          c, ptrfromword(c->pred), ptrfromword(c->succ));

  // pointers on free block list point to free blocks
  ok = true;
  c = root;
  do {
    word_t *s = (word_t *)ptrfromword(c->succ);
    word_t *p = (word_t *)ptrfromword(c->pred);
    if (!block_free(s) || !block_free(p)) {
      ok = false;
      break;
    }
    c = ptrfromword(c->succ);
  } while (c != root);

  if (!ok && verbose)
    debug("[CHECK] some next and previous pointers are not reffering to free "
          "blocks, example: block=%p, pred:%p, succ:%p\n",
          c, ptrfromword(c->pred), ptrfromword(c->succ));
}
