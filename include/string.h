#ifndef _STRING_H
#define _STRING_H

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);

void *_vmemcpy (void *restrict volatile, const void *restrict volatile, size_t);
void *_vmemmove (void * volatile, const void * volatile, size_t);
void *_vmemset (void * volatile, int, size_t);

#endif
