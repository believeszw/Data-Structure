//
// Created by believe on 2020/1/21.
//

/*

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

 Example 1:        Example 2:          Example 3:        Example 4:        Example 5:
  Input: "()"       Input: "()[]{}"     Input: "(]"       Input: "([)]"     Input: "{[]}"
  Output: true      Output: true        Output: false     Output: false     Output: true

 */

#include <iostream>
#include "array_stack.h"

bool isValid(std::string s) {
  ArrayStack<char> array_stack;
  for (char c : s) {
    if (c == '(' || c == '{' || c == '[')
      array_stack.Push(c);
    else
    {
      if (array_stack.IsEmpty())
        return false;
      char top_char = array_stack.Peek();
      if (top_char == '(' && c != ')')
        return false;
      if (top_char == '{' && c != '}')
        return false;
      if (top_char == '[' && c != ']')
        return false;
      array_stack.Pop();
    }
  }
  return array_stack.IsEmpty();
}