#if !defined(_DYLD_INTERPOSING_H_)
#define _DYLD_INTERPOSING_H_

/*
 * Example:
 *
 *  static int my_open(const char* path, int flags, mode_t mode) {
 *      int value;
 *      // do stuff before open (including changing the arguments)
 *      value = open(path, flags, mode);
 *      // do stuff after open (including changing the return value(s))
 *      return value;
 *  }
 *  DYLD_INTERPOSE(my_open, open)
 */

typedef void (*void_function_t)(void);

#define DYLD_INTERPOSE(_replacement, _replacee) \
	__attribute__((used)) \
		static struct { \
			const void* replacement; \
			const void* replacee; \
		} _interpose_##_replacee \
		__attribute__ ((section ("__DATA,__interpose"))) = { \
			(const void *)(unsigned long)&_replacement, \
			(const void*)(unsigned long)&_replacee \
		};

#endif
