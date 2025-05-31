uint16_t dynamic_keystroke_count_raw(void) {
  return ARRAY_SIZE(dynamic_keystrokes);
}

__attribute__((weak)) uint16_t dynamic_keystroke_count(void) {
  return dynamic_keystroke_count_raw();
}

STATIC_ASSERT(ARRAY_SIZE(dynamic_keystrokes) <= (MAX_DYNAMIC_KEYSTROKE_PAIRS), "Max dynamic keystroke pairs is 10");

dynamic_keystroke_t* dynamic_keystroke_get_raw(uint16_t index) {
  if (index >= dynamic_keystroke_count_raw()) {
    return NULL;
  }
  return &dynamic_keystrokes[index];
}

__attribute__((weak)) dynamic_keystroke_t* dynamic_keystroke_get(uint16_t index) {
  return dynamic_keystroke_get_raw(index);
}
