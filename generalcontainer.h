/*
Copyright (c) 2025-2026 Orkiin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

typedef enum {
  OK,
  ERROR_EMPTY_CONTAINER,
  ERROR_FULL_CONTAINER,
  ERROR_INVALID_VALUE,
} result;

#define TEMPLATETYPENAME(type) type##_container
#define TEMPLATETYPEOPTION(type) type##_option
#define TEMPLATETYPERESULT(type) result_##type
#define TEMPLATERESULTERRORAWARE(type)                                         \
  typedef struct {                                                             \
    result r;                                                                  \
    union {                                                                    \
      type t;                                                                  \
      const char *error;                                                       \
    } data;                                                                    \
  } TEMPLATETYPERESULT(type)
#define TEMPLATEGENERALCONTAINER(type)                                         \
  typedef struct {                                                             \
    type *data;                                                                \
    size_t capacity;                                                           \
    size_t number;                                                             \
    size_t front;                                                              \
    size_t rear;                                                               \
  } TEMPLATETYPENAME(type)
#define TEMPLATEOPTION(type)                                                   \
  typedef struct {                                                             \
    enum {                                                                     \
      OPT_VALUE,                                                               \
      OPT_NONE,                                                                \
    } option;                                                                  \
    type data;                                                                 \
  } TEMPLATETYPEOPTION(type)

#define TEMPLATESTACKPOP(type)                                                 \
  TEMPLATETYPERESULT(type) ppop_##type(TEMPLATETYPENAME(type) * container) {   \
    if (container->number == 0) {                                              \
      return (TEMPLATETYPERESULT(type)){.r = ERROR_EMPTY_CONTAINER,            \
                                        .data.error =                          \
                                            "Can't pop on empty container"};   \
    }                                                                          \
    container->number--;                                                       \
    if (container->rear == 0) {                                                \
      container->rear = container->capacity;                                   \
    }                                                                          \
    container->rear--;                                                         \
    return (TEMPLATETYPERESULT(type)){                                         \
        .r = OK, .data.t = container->data[container->rear]};                  \
  }

#define TEMPLATESTACKPOP_OPT(type)                                             \
  TEMPLATETYPEOPTION(type)                                                     \
  ppop_##type##_opt(TEMPLATETYPENAME(type) * container) {                      \
    if (container->number == 0) {                                              \
      return (TEMPLATETYPEOPTION(type)){.option = OPT_NONE, 0};                \
    }                                                                          \
    container->number--;                                                       \
    if (container->rear == 0) {                                                \
      container->rear = container->capacity;                                   \
    }                                                                          \
    container->rear--;                                                         \
    return (TEMPLATETYPEOPTION(type)){                                         \
        .option = OPT_VALUE, .data = container->data[container->rear]};        \
  }

#define TEMPLATESTACKPOP_UNSAFE(type)                                          \
  type ppop_##type##_unsafe(TEMPLATETYPENAME(type) * container) {              \
    if (container->number == 0) {                                              \
      return container->data[container->front];                                \
    }                                                                          \
    container->number--;                                                       \
    if (container->rear == 0) {                                                \
      container->rear = container->capacity;                                   \
    }                                                                          \
    container->rear--;                                                         \
    return container->data[container->rear];                                   \
  }

#define TEMPLATESTACKPEEK(type)                                                \
  TEMPLATETYPERESULT(type)                                                     \
  ppeek_##type(TEMPLATETYPENAME(type) * container) {                           \
    if (container->number == 0) {                                              \
      return (TEMPLATETYPERESULT(type)){.r = ERROR_EMPTY_CONTAINER,            \
                                        .data.error =                          \
                                            "Can't peek on empty container"};  \
    }                                                                          \
    size_t index = (container->rear == 0) ? container->capacity - 1            \
                                          : container->rear - 1;               \
    return (TEMPLATETYPERESULT(type)){.r = OK,                                 \
                                      .data.t = container->data[index]};       \
  }

#define TEMPLATESTACKPEEK_OPT(type)                                            \
  TEMPLATETYPEOPTION(type)                                                     \
  ppeek_##type##_opt(TEMPLATETYPENAME(type) * container) {                     \
    if (container->number == 0) {                                              \
      return (TEMPLATETYPEOPTION(type)){.option = OPT_NONE, 0};                \
    }                                                                          \
    size_t index = (container->rear == 0) ? container->capacity - 1            \
                                          : container->rear - 1;               \
    return (TEMPLATETYPEOPTION(type)){.option = OPT_VALUE,                     \
                                      .data = container->data[index]};         \
  }

#define TEMPLATESTACKPEEK_UNSAFE(type)                                         \
  TEMPLATETYPERESULT(type)                                                     \
  ppeek_##type##_unsafe(TEMPLATETYPENAME(type) * container) {                  \
    size_t index = (container->rear == 0) ? container->capacity - 1            \
                                          : container->rear - 1;               \
    return (TEMPLATETYPERESULT(type)){.r = OK,                                 \
                                      .data.t = container->data[index]};       \
  }

#define TEMPLATEPUSHEND(type)                                                  \
  result push_##type(type value, TEMPLATETYPENAME(type) * container) {         \
    if (container->number == container->capacity)                              \
      return ERROR_FULL_CONTAINER;                                             \
    container->data[container->rear++] = value;                                \
    container->number++;                                                       \
    if (container->rear == container->capacity) {                              \
      container->rear = 0;                                                     \
    }                                                                          \
    return OK;                                                                 \
  }

#define TEMPLATEPUSHEND_OPT(type)                                              \
  result push_##type##_opt(TEMPLATETYPEOPTION(type) optional_value,            \
                           TEMPLATETYPENAME(type) * container) {               \
    switch (optional_value.option) {                                           \
    case OPT_NONE:                                                             \
      return ERROR_INVALID_VALUE;                                              \
    case OPT_VALUE:                                                            \
      if (container->number == container->capacity)                            \
        return ERROR_FULL_CONTAINER;                                           \
      container->data[container->rear++] = optional_value.data;                \
      container->number++;                                                     \
      if (container->rear == container->capacity) {                            \
        container->rear = 0;                                                   \
      }                                                                        \
      return OK;                                                               \
    }                                                                          \
  }

#define TEMPLATEQUEUEPOP(type)                                                 \
  TEMPLATETYPERESULT(type) qpop_##type(TEMPLATETYPENAME(type) * container) {   \
    if (container->number == 0) {                                              \
      return (TEMPLATETYPERESULT(type)){                                       \
          .r = ERROR_EMPTY_CONTAINER,                                          \
          .data.error = "Can't dequeue on empty container"};                   \
    }                                                                          \
    container->number--;                                                       \
    TEMPLATETYPERESULT(type)                                                   \
    ret = (TEMPLATETYPERESULT(type)){                                          \
        .r = OK, .data.t = container->data[container->front++]};               \
    if (container->front == container->capacity) {                             \
      container->front = 0;                                                    \
    }                                                                          \
    return ret;                                                                \
  }

#define TEMPLATEQUEUEPOP_UNSAFE(type)                                          \
  type qpop_##type##_unsafe(TEMPLATETYPENAME(type) * container) {              \
    container->number--;                                                       \
    type ret = container->data[container->front++];                            \
    if (container->front == container->capacity) {                             \
      container->front = 0;                                                    \
    }                                                                          \
    return ret;                                                                \
  }

#define TEMPLATEQUEUEPOP_OPT(type)                                             \
  TEMPLATETYPEOPTION(type)                                                     \
  qpop_##type##_opt(TEMPLATETYPENAME(type) * container) {                      \
    if (container->number == 0) {                                              \
      return (TEMPLATETYPEOPTION(type)){.option = OPT_NONE, 0};                \
    }                                                                          \
    container->number--;                                                       \
    TEMPLATETYPEOPTION(type)                                                   \
    ret = (TEMPLATETYPEOPTION(type)){                                          \
        .option = OK, .data = container->data[container->front++]};            \
    if (container->front == container->capacity) {                             \
      container->front = 0;                                                    \
    }                                                                          \
    return ret;                                                                \
  }

#endif // !STACK_QUEUE_H
