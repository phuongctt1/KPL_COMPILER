/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <ctype.h>
#include "token.h" 
// token.c //phan loai va nhan dang token, tu khoa

struct {                          // cau truc keywords
  char string[MAX_IDENT_LEN + 1];
  TokenType tokenType;
} keywords[KEYWORDS_COUNT] = {
  {"PROGRAM", KW_PROGRAM},  // bat dau mot chuong trinh
  {"CONST", KW_CONST},      // khai bao hang so
  {"TYPE", KW_TYPE},        //khai bao kieu
  {"VAR", KW_VAR},          // khai bao bien
  {"INTEGER", KW_INTEGER},  //kieu so nguyen
  {"CHAR", KW_CHAR},        // kieu ki tu
  {"ARRAY", KW_ARRAY},      // khai bao mang
  {"OF", KW_OF},
  {"FUNCTION", KW_FUNCTION},   //khai bao ham
  {"PROCEDURE", KW_PROCEDURE},  // khai bao chuong trinh con
  {"BEGIN", KW_BEGIN},          // bat dau mot khoi
  {"END", KW_END},            // ket thuc mot khoi
  {"CALL", KW_CALL},          //loi goi mot chuong trinh con
  {"IF", KW_IF},              // cau lenh re nhanh
  {"THEN", KW_THEN},
  {"ELSE", KW_ELSE},
  {"WHILE", KW_WHILE},        // vong lap while
  {"DO", KW_DO},
  {"FOR", KW_FOR},
  {"TO", KW_TO}
};

int keywordEq(char *kw, char *string) {
  while ((*kw != '\0') && (*string != '\0')) {
    if (*kw != toupper(*string)) break;
    kw ++; string ++;
  }
  return ((*kw == '\0') && (*string == '\0'));
}

TokenType checkKeyword(char *string) {    // kiem tra mot sau co la tu khoa khong
  int i;
  for (i = 0; i < KEYWORDS_COUNT; i++)
    if (keywordEq(keywords[i].string, string)) 
      return keywords[i].tokenType;
  return TK_NONE;
}

Token* makeToken(TokenType tokenType, int lineNo, int colNo) {    // tao mot token moi voi kieu va vi tri
  Token *token = (Token*)malloc(sizeof(Token));
  token->tokenType = tokenType;
  token->lineNo = lineNo;
  token->colNo = colNo;
  return token;
}

char *tokenToString(TokenType tokenType) {
  switch (tokenType) {

  // cac kieu token, TK la viet tat cua token

  case TK_NONE: return "None";
  case TK_IDENT: return "an identification";
  case TK_NUMBER: return "a number";
  case TK_CHAR: return "a constant char";
  case TK_EOF: return "end of file";

  // cac tu khoa, KW la viet tat cua keyword

  case KW_PROGRAM: return "keyword PROGRAM";
  case KW_CONST: return "keyword CONST";
  case KW_TYPE: return "keyword TYPE";
  case KW_VAR: return "keyword VAR";
  case KW_INTEGER: return "keyword INTEGER";
  case KW_CHAR: return "keyword CHAR";
  case KW_ARRAY: return "keyword ARRAY";
  case KW_OF: return "keyword OF";
  case KW_FUNCTION: return "keyword FUNCTION";
  case KW_PROCEDURE: return "keyword PROCEDURE";
  case KW_BEGIN: return "keyword BEGIN";
  case KW_END: return "keyword END";
  case KW_CALL: return "keyword CALL";
  case KW_IF: return "keyword IF";
  case KW_THEN: return "keyword THEN";
  case KW_ELSE: return "keyword ELSE";
  case KW_WHILE: return "keyword WHILE";
  case KW_DO: return "keyword DO";
  case KW_FOR: return "keyword FOR";
  case KW_TO: return "keyword TO";

// cac ki hieu dac biet, bat dau bang SB_...

// cac toan tu, ki hieu dac biet, ky hieu kep
//(* va *) danh dau chu thich
  case SB_SEMICOLON: return "\';\'"; //ky hieu dac biet ;
  case SB_COLON: return "\':\'";      //ky hieu dac biet :
  case SB_PERIOD: return "\'.\'";     // ky hieu dac biet
  case SB_COMMA: return "\',\'";      // ky hieu dac biet
  case SB_ASSIGN: return "\':=\'";  //toan tu gan
  case SB_EQ: return "\'=\'";       // toan tu bang
  case SB_NEQ: return "\'!=\'";     // toan tu khac
  case SB_LT: return "\'<\'";       // toan tu nho hon
  case SB_LE: return "\'<=\'";       //toan tu
  case SB_GT: return "\'>\'";
  case SB_GE: return "\'>=\'";
  case SB_PLUS: return "\'+\'";
  case SB_MINUS: return "\'-\'";
  case SB_TIMES: return "\'*\'";
  case SB_SLASH: return "\'/\'";
  case SB_LPAR: return "\'(\'";   // ky hieu mo ngoac
  case SB_RPAR: return "\')\'";   // ky hieu dong ngoac
  case SB_LSEL: return "\'(.\'";   // (. va .) danh dau chi muc cua mang
  case SB_RSEL: return "\'.)\'";
  default: return "";
  }
}
