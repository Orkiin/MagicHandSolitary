#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

typedef enum {
  OK,
  ERROR_EMPTY_CONTAINER,
  ERROR_FULL_CONTAINER,
}result;

#define TEMPLATETYPENAME(type) type ## _container
#define TEMPLATERESULT(type) result_ ## type
#define TEMPLATERESULTERRORAWARE(type) typedef struct {\
  result r; \
  union { \
    type t;\
    const char *error;\
  } data; \
} TEMPLATERESULT(type)
#define TEMPLATEGENERALCONTAINER(type) typedef struct {\
  type *data;\
  size_t capacity;\
  size_t number;\
  size_t front;\
  size_t rear;\
} TEMPLATETYPENAME(type)

#define TEMPLATEPOP(type) TEMPLATERESULT(type) pop_ ## type (TEMPLATETYPENAME(type) *container){ \
  if (container->number == 0) {\
    return (TEMPLATERESULT(type)){ .r = ERROR_EMPTY_CONTAINER, .data.error = "Can't pop on empty continer"};\
  }\
  container->number--;\
  if (container->rear == 0) {\
    container->rear = container->capacity;\
  }\
  container->rear--;\
  return (TEMPLATERESULT(type)){ .r = OK , .data.t = container->data[container->rear]};\
}

#endif // !STACK_QUEUE_H
