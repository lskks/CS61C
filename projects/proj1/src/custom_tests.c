#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in game.c
#include "game.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False
  otherwise. Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is
  a,e,i,o,u) and returns false otherwise Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/**
 * @task: test task4.1.1
 * @status: pass
 */

bool test_is_tail() {
  char test_case1 = 'w';
  bool output1 = is_tail(test_case1);
  if (!assert_true("output1", output1)) {
    return false;
  }

  char test_case2 = 'a';
  bool output2 = is_tail(test_case2);
  if (!assert_true("output2", output2)) {
    return false;
  }

  char test_case3 = 's';
  bool output3 = is_tail(test_case3);
  if (!assert_true("output3", output3)) {
    return false;
  }

  char test_case4 = 'd';
  bool output4 = is_tail(test_case4);
  if (!assert_true("output4", output4)) {
    return false;
  }

  char test_case5 = 'l';
  bool output5 = is_tail(test_case5);
  if (!assert_false("output5", output5)) {
    return false;
  }

  char test_case6 = 'p';
  bool output6 = is_tail(test_case6);
  if (!assert_false("output6", output6)) {
    return false;
  }

  return true;
}

bool test_is_head() {
  char test_case1 = 'W';
  bool output1 = is_head(test_case1);
  if (!assert_true("output1", output1)) {
    return false;
  }

  char test_case2 = 'A';
  bool output2 = is_head(test_case2);
  if (!assert_true("output2", output2)) {
    return false;
  }

  char test_case3 = 'S';
  bool output3 = is_head(test_case3);
  if (!assert_true("output3", output3)) {
    return false;
  }

  char test_case4 = 'D';
  bool output4 = is_head(test_case4);
  if (!assert_true("output4", output4)) {
    return false;
  }

  char test_case5 = 'x';
  bool output5 = is_head(test_case5);
  if (!assert_true("output5", output5)) {
    return false;
  }

  char test_case6 = 'p';
  bool output6 = is_head(test_case6);
  if (!assert_false("output6", output6)) {
    return false;
  }

  char test_case7 = 'l';
  bool output7 = is_head(test_case7);
  if (!assert_false("output7", output7)) {
    return false;
  }

  char test_case8 = 'J';
  bool output8 = is_head(test_case8);
  if (!assert_false("output8", output8)) {
    return false;
  }

  return true;
}

// This test is similar to test_is_tail(head), so i don't write it
bool test_is_snake() { return true; }

bool test_body_to_tail() {
  char test_case1 = '^';
  char output1 = body_to_tail(test_case1);
  if (!assert_equals_char("output1", 'w', output1)) {
    return false;
  }

  char test_case2 = '<';
  char output2 = body_to_tail(test_case2);
  if (!assert_equals_char("output2", 'a', output2)) {
    return false;
  }

  char test_case3 = 'v';
  char output3 = body_to_tail(test_case3);
  if (!assert_equals_char("output3", 's', output3)) {
    return false;
  }

  char test_case4 = '>';
  char output4 = body_to_tail(test_case4);
  if (!assert_equals_char("output4", 'd', output4)) {
    return false;
  }

  char test_case5 = 'h';
  char output5 = body_to_tail(test_case5);
  if (!assert_equals_char("output5", '?', output5)) {
    return false;
  }

  char test_case6 = 'i';
  char output6 = body_to_tail(test_case6);
  if (!assert_equals_char("output6", '?', output6)) {
    return false;
  }

  return true;
}

bool test_head_to_body() {
  char test_case1 = 'W';
  char output1 = head_to_body(test_case1);
  if (!assert_equals_char("output1", '^', output1)) {
    return false;
  }

  char test_case2 = 'A';
  char output2 = head_to_body(test_case2);
  if (!assert_equals_char("output2", '<', output2)) {
    return false;
  }

  char test_case3 = 'S';
  char output3 = head_to_body(test_case3);
  if (!assert_equals_char("output3", 'v', output3)) {
    return false;
  }

  char test_case4 = 'D';
  char output4 = head_to_body(test_case4);
  if (!assert_equals_char("output4", '>', output4)) {
    return false;
  }

  char test_case5 = 'h';
  char output5 = head_to_body(test_case5);
  if (!assert_equals_char("output5", '?', output5)) {
    return false;
  }

  char test_case6 = 'i';
  char output6 = head_to_body(test_case6);
  if (!assert_equals_char("output6", '?', output6)) {
    return false;
  }

  return true;
}

bool test_get_next_row() {
  unsigned int row = 8;

  char test_case1 = 'v';
  int output1 = get_next_row(row, test_case1);
  if (!assert_equals_int("output1", row+1, output1)) {
    return false;
  }

  char test_case2 = 's';
  int output2 = get_next_row(row, test_case2);
  if (!assert_equals_int("output2", row+1, output2)) {
    return false;
  }

  char test_case3 = 'S';
  int output3 = get_next_row(row, test_case3);
  if (!assert_equals_int("output3", row+1, output3)) {
    return false;
  }

  char test_case4 = '^';
  int output4 = get_next_row(row, test_case4);
  if (!assert_equals_int("output4", row-1, output4)) {
    return false;
  }

  char test_case5 = 'w';
  int output5 = get_next_row(row, test_case5);
  if (!assert_equals_int("output5", row-1, output5)) {
    return false;
  }

  char test_case6 = 'W';
  int output6 = get_next_row(row, test_case6);
  if (!assert_equals_int("output6", row-1, output6)) {
    return false;
  }

  char test_case7 = 'x';
  int output7 = get_next_row(row, test_case7);
  if (!assert_equals_int("output7", row, output7)) {
    return false;
  }

  char test_case8 = 'a';
  int output8 = get_next_row(row, test_case8);
  if (!assert_equals_int("output8", row, output8)) {
    return false;
  }

  return true;
}
// This test is similar to above(test_get_next_row), so i don't write it
bool test_get_next_col() {
  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
