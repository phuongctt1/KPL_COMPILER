/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __CHARCODE_H__
#define __CHARCODE_H__

typedef enum {
  CHAR_SPACE,   // khoang trong
  CHAR_LETTER,   // chu cai
  CHAR_DIGIT,     // chu so
  CHAR_PLUS,    // dau '+'
  CHAR_MINUS,   // dau '-'
  CHAR_TIMES,   // dau '*'
  CHAR_SLASH,   // dau '/'
  CHAR_LT,      // dau '<'
  CHAR_GT,      // dau '>'
  CHAR_EXCLAIMATION,    // dau '!'
  CHAR_EQ,          // dau '='
  CHAR_COMMA,   // dau ','
  CHAR_PERIOD,   // dau '.'
  CHAR_COLON,     // dau ':'
  CHAR_SEMICOLON, // dau ';'
  CHAR_SINGLEQUOTE,   // dau '\'
  CHAR_LPAR,      // dau '('
  CHAR_RPAR,      // dau ')'
  CHAR_UNKNOWN    // ki tu ngoai bang chu cai, chua duoc dinh nghia
} CharCode;

#endif
