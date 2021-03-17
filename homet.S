void exit1(int status) {
  asm volatile(
    "int $0x80\n"
    : : "a"(1), "b"(status)
  );
}

int read1(int fd, void* buf, int size) {
  int res;
  asm volatile (
    "int $0x80\n"
    : "=a"(res) : "a"(3), "b"(fd), "c"(buf), "d"(size)
    : "memory"
  );
  return res;
}

int write1(int fd, void* buf, int size) {
  int res;
  asm volatile(
    "int $0x80\n"
    : "=a"(res) : "a"(4), "b"(fd), "c"(buf), "d"(size)
  );
  return res;
}

void _start() {
  char c;
  int size = read1(0, &c, 1);
  while (size) {
    if ('a' <= c && c <= 'z') {
      c -= 32;
    }
    write1(1, &c, 1);
    size = read1(0, &c, 1);
  }
  exit1(0);
}

//  Решение взял с семинара
