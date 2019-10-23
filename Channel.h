#include <util/atomic.h>

#define CHANNEL_SIZE 100

class Channel {
  private:
    char buf[CHANNEL_SIZE + 1];
    int head, tail;

  public:
    Channel();
    int available();
    bool put(char ch);
    bool get(char *ch);
};

Channel::Channel() : head(0), tail(0) {
}

int Channel::available() {
  if (head < tail) {
    return tail - head;
  } else if (tail < head) {
    return tail + (CHANNEL_SIZE - head);
  }
  return 0;
}

bool Channel::put(char ch) {
  if ((tail + 1) % (CHANNEL_SIZE + 1) == head) {
    return false; // buffer is full
  }

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    buf[tail] = ch;
    tail = (tail + 1) % (CHANNEL_SIZE + 1);
  }
  return true;
}

bool Channel::get(char *ch = NULL) {
  if (head == tail) {
    return false;
  }

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    if (ch) {
      *ch = buf[head];
    }
    head = (head + 1) % (CHANNEL_SIZE + 1);
  }
  return true;
}
