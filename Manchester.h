unsigned long manchesterEncode(char ch) {
  unsigned long ret = 0;

  for (int i = 0; i < 8; i++) {
    ret <<= 2;
    if (ch & 0x80) {
      ret |= 0x1; // manchester-encoded 1
    } else {
      ret |= 0x2; // manchester-encoded 0
    }
    ch <<= 1;
  }

  return ret;
}

unsigned long encodeWord(char ch) {
  unsigned long val = manchesterEncode(ch);

  return 0x80000 | (val << 2) | 0x1;
}
