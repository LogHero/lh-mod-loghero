#ifndef GLOBALDEFINES_H
#define GLOBALDEFINES_H

#include <inttypes.h>
#include <ctime>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

namespace loghero {
  typedef int64_t int64_t;
  typedef uint64_t uint64_T;
  typedef std::time_t time_t;
}

#endif // GLOBALDEFINES_H
