/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#define MAX_IDENT_LEN 15
#define KEYWORDS_COUNT 20

typedef enum {
  // cac kieu Token, TK la viet tat cua token
  TK_NONE,      // dai dien cho mot loi
  TK_IDENT,      // dinh danh
  TK_NUMBER,      //so
  TK_CHAR,        // hang ki tu
  TK_EOF,         // ket thuc chuong trinh

// cac tu khoa(da duoc dinh nghia truoc do roi, file token.c), bat dau bang KW (keyword)
  KW_PROGRAM, 
  KW_CONST, 
  KW_TYPE, 
  KW_VAR,
  KW_INTEGER, 
  KW_CHAR, 
  KW_ARRAY, 
  KW_OF, 
  KW_FUNCTION, 
  KW_PROCEDURE,
  KW_BEGIN, 
  KW_END, 
  KW_CALL,
  KW_IF, 
  KW_THEN, 
  KW_ELSE,
  KW_WHILE, 
  KW_DO, 
  KW_FOR, 
  KW_TO,
// cac ki hieu dac biet, bat dau bang SB_sau do la ten ki hieu
  SB_SEMICOLON, 
  SB_COLON, 
  SB_PERIOD, 
  SB_COMMA,
  SB_ASSIGN, 
  SB_EQ, 
  SB_NEQ, 
  SB_LT, 
  SB_LE, 
  SB_GT, 
  SB_GE,
  SB_PLUS, 
  SB_MINUS, 
  SB_TIMES, 
  SB_SLASH,
  SB_LPAR, 
  SB_RPAR, 
  SB_LSEL, 
  SB_RSEL
} TokenType; 

// cau truc luu tru mot token co dang nhu sau

typedef struct {
  char string[MAX_IDENT_LEN + 1]; //kieu chuoi[do dai toi da + ki tu ket thuc '\n']
  int lineNo, colNo;              // vi tri dong, cot ma token do xuat hien
  TokenType tokenType;          // kieu token ma ta dinh nghia o tren VD nhu SB_..., KW_...,...TK_...
  int value;                    // gia tri
} Token;

TokenType checkKeyword(char *string); // kiem tra mot sau co la tu khoa khong
Token* makeToken(TokenType tokenType, int lineNo, int colNo); // tao mot token moi voi kieu va vi tri
char *tokenToString(TokenType tokenType);


#endif
