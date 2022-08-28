/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"
#include "scanner.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void skipBlank() { // loai bo cac dau cach
  while ((currentChar != EOF) && (charCodes[currentChar] == CHAR_SPACE))
    readChar();
}

void skipComment() { // loai bo cac chu thich
  int state = 0;
  while ((currentChar != EOF) && (state < 2)) {
    switch (charCodes[currentChar]) {
    case CHAR_TIMES:  // dấu *
      state = 1;
      break;
    case CHAR_RPAR: // dau )
      if (state == 1) state = 2;
      else state = 0;
      break;
    default:
      state = 0;
    }
    readChar();
  }
  if (state != 2) 
    error(ERR_ENDOFCOMMENT, lineNo, colNo);
}

Token* readIdentKeyword(void) { // doc vao mot tu khoa ident
  Token *token = makeToken(TK_NONE, lineNo, colNo);
  int count = 1;

  token->string[0] = (char)currentChar;
  readChar();

  while ((currentChar != EOF) && 
	 ((charCodes[currentChar] == CHAR_LETTER) || (charCodes[currentChar] == CHAR_DIGIT))) {
    if (count <= MAX_IDENT_LEN) token->string[count++] = (char)currentChar;
    readChar();
  }

  if (count > MAX_IDENT_LEN) {
    error(ERR_IDENTTOOLONG, token->lineNo, token->colNo);
    return token;
  }

  token->string[count] = '\0';
  token->tokenType = checkKeyword(token->string);

  if (token->tokenType == TK_NONE)
    token->tokenType = TK_IDENT;

  return token;
}

Token* readNumber(void) {       // doc vao mot so
  Token *token = makeToken(TK_NUMBER, lineNo, colNo);
  int count = 0;

  while ((currentChar != EOF) && (charCodes[currentChar] == CHAR_DIGIT)) {
    token->string[count++] = (char)currentChar;
    readChar();
  }

  token->string[count] = '\0';
  token->value = atoi(token->string);
  return token;
}

Token* readConstChar(void) {
  Token *token = makeToken(TK_CHAR, lineNo, colNo);

  readChar();
  if (currentChar == EOF) {
    token->tokenType = TK_NONE;
    error(ERR_INVALIDCHARCONSTANT, token->lineNo, token->colNo);
    return token;
  }
    
  token->string[0] = currentChar;
  token->string[1] = '\0';

  readChar();
  if (currentChar == EOF) {
    token->tokenType = TK_NONE;
    error(ERR_INVALIDCHARCONSTANT, token->lineNo, token->colNo);
    return token;
  }

  if (charCodes[currentChar] == CHAR_SINGLEQUOTE) {   // ki hieu \
    readChar();
    return token;
  } else {
    token->tokenType = TK_NONE;
    error(ERR_INVALIDCHARCONSTANT, token->lineNo, token->colNo);
    return token;
  }
}

Token* getToken(void) { // doc mot token tinh tu vi tri hien tai
  Token *token;       // bien token, con tro tro den doi tuong token
  int ln, cn;

  if (currentChar == EOF) // neu ki tu hien tai currentchar hien tai la ki tu loi
    return makeToken(TK_EOF, lineNo, colNo);  // thi tao ra 1 token end of file

  switch (charCodes[currentChar]) {     // trai lai ki tu hien tai doc duoc
  case CHAR_SPACE: skipBlank(); return getToken();    // ktra neu la dau cach thi bo qua khoang trang sau do goi lai gettoken
  case CHAR_LETTER: return readIdentKeyword();  // neu no là chữ cái thì gọi hàm đọc ident chữ cái readIdentKeyword()
  case CHAR_DIGIT: return readNumber(); // nếu nó là số thì gọi hàm đọc chữ số readNumber()
  case CHAR_PLUS:                     // nếu nó là dấu cộng
    token = makeToken(SB_PLUS, lineNo, colNo);  // tạo 1 token dấu cộng
    readChar();                 // doc 1 kí tự từ kênh vào file reader.h
    return token;             // tra lai token
  case CHAR_MINUS:          // neu no la dau tru
    token = makeToken(SB_MINUS, lineNo, colNo);   // thi tao 1 token dau tru
    readChar();           // doc 1 ki tu tu kenh vao
    return token;         // tra lai token
  case CHAR_TIMES:        // neu la dau nhân *
    token = makeToken(SB_TIMES, lineNo, colNo);     
    readChar(); 
    return token;
  case CHAR_SLASH:      // neu la dấu chia /
    token = makeToken(SB_SLASH, lineNo, colNo);
    readChar(); 
    return token;
  case CHAR_LT:       // nếu là toán tử '<'
    ln = lineNo;      
    cn = colNo;
    readChar();       // đọc vào 1 kí tự tiếp theo
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ)) {    // kí tự đó là dấu '='
      readChar();     // đọc vào 1 kí tự tiếp theo
      return makeToken(SB_LE, ln, cn);    // trả về 1 token '<='
    } else return makeToken(SB_LT, ln, cn); // còn nếu kí tự tiếp không phai dau '=' thi tra ve token '<'
  case CHAR_GT:     // nếu là toan tu '>'
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ)) { // nếu kí tự đọc vào tiếp theo là dấu =
      readChar();
      return makeToken(SB_GE, ln, cn);    // trả về token '>='
    } else return makeToken(SB_GT, ln, cn);   // ngược lại trả về >
  case CHAR_EQ:         // neu la toan tu '='
    token = makeToken(SB_EQ, lineNo, colNo);  //tao 1 token dau = la SB_EQ
    readChar(); 
    return token;
  case CHAR_EXCLAIMATION:     // nếu là dấu !
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ)) { // ktra kí tự tiếp có phải là dấu = ko
      readChar();
      return makeToken(SB_NEQ, ln, cn);   // đúng thì trả về dấu khác !=
    } else {                               // ngược lại
      token = makeToken(TK_NONE, ln, cn); // trả về 1 lỗi
      error(ERR_INVALIDSYMBOL, ln, cn);   // lỗi "Invalid symbol!"
      return token;
    }
  case CHAR_COMMA:          // nếu là dấu ','
    token = makeToken(SB_COMMA, lineNo, colNo); // tạo 1 token kí hiệu đặc biệt SB_COMMA
    readChar(); 
    return token;
  case CHAR_PERIOD:        //nếu là dấu '.'
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_RPAR)) {    // kiểm tra kí tự tiếp có phải ')'
      readChar();       // đúng thì đọc kí tự đó
      return makeToken(SB_RSEL, ln, cn);        // trả lại '.)'
    } else return makeToken(SB_PERIOD, ln, cn);   // ngược lại trả lại dấu '.'
  case CHAR_SEMICOLON:                  // nếu là dấu ';'
    token = makeToken(SB_SEMICOLON, lineNo, colNo);   // tạo 1 token 
    readChar(); 
    return token;
  case CHAR_COLON:    // dấu :
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ)) { // kiểm tra kí tự tiếp có là dấu = hay ko
      readChar();       // nếu đứng thì đọc vào
      return makeToken(SB_ASSIGN, ln, cn); // trả lại token kí hiệu gán :=
    } else return makeToken(SB_COLON, ln, cn);    // ngược lại trả về dấu :
  case CHAR_SINGLEQUOTE: return readConstChar(); // dau \ thi tra ve ham doc readConstChar()
  case CHAR_LPAR:       // nếu là dau '('
    ln = lineNo;
    cn = colNo;
    readChar();     // doc 1 ki tu tu kenh vao

    if (currentChar == EOF) // neu la ki tu ket thuc ?
      return makeToken(SB_LPAR, ln, cn);    // tra ve token kí hiệu mở ngoặc '('

    switch (charCodes[currentChar]) { // có 2 trường hợp
    case CHAR_PERIOD:                 // nếu ki tu tiep theo la dau '.'
      readChar();                     // doc ki tu đó
      return makeToken(SB_LSEL, ln, cn);    // tra ve token '(.'  kí hiệu mảng
    case CHAR_TIMES:                  // neu ki tu tiep theo la dau * => (* chú thích
      readChar();                     // doc ki tu do
      skipComment();                  // ham bo qua chu thich 
      return getToken();              // 
    default:                          // default se duoc thuc hienn neu khong co gia tri hang nao phu hop voi switch(charCode[curentChar])
      return makeToken(SB_LPAR, ln, cn);  // tra ve '('
    }
  case CHAR_RPAR:                               // ki hieu dong ngoac ')'
    token = makeToken(SB_RPAR, lineNo, colNo);   // tao token SB_RPAR
    readChar();                                   // doc ki tu do
    return token;                               // tra ve token


  default:                            // nếu ko la cac truong hop tren thi dua ra thong bao loi
    token = makeToken(TK_NONE, lineNo, colNo);    //
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar(); 
    return token;
  }
}

Token* getValidToken(void) { // lay gia tri token
  Token *token = getToken();    // getToken() de lay 1 token
  while (token->tokenType == TK_NONE) { // neu ma token ma ta lay duoc la TK_NONE(bi loi)
    free(token);                        // thi ta giai phong token
    token = getToken();                 // doc token tiep theo
  }
  return token;                         // doc tiep nhu vay cho den khi co 1 token co nghia thi se tra ve token
}


/******************************************************************/

void printToken(Token *token) {

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case TK_NONE: printf("TK_NONE\n"); break;
  case TK_IDENT: printf("TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: printf("TK_NUMBER(%s)\n", token->string); break;
  case TK_CHAR: printf("TK_CHAR(\'%s\')\n", token->string); break;
  case TK_EOF: printf("TK_EOF\n"); break;

  case KW_PROGRAM: printf("KW_PROGRAM\n"); break;
  case KW_CONST: printf("KW_CONST\n"); break;
  case KW_TYPE: printf("KW_TYPE\n"); break;
  case KW_VAR: printf("KW_VAR\n"); break;
  case KW_INTEGER: printf("KW_INTEGER\n"); break;
  case KW_CHAR: printf("KW_CHAR\n"); break;
  case KW_ARRAY: printf("KW_ARRAY\n"); break;
  case KW_OF: printf("KW_OF\n"); break;
  case KW_FUNCTION: printf("KW_FUNCTION\n"); break;
  case KW_PROCEDURE: printf("KW_PROCEDURE\n"); break;
  case KW_BEGIN: printf("KW_BEGIN\n"); break;
  case KW_END: printf("KW_END\n"); break;
  case KW_CALL: printf("KW_CALL\n"); break;
  case KW_IF: printf("KW_IF\n"); break;
  case KW_THEN: printf("KW_THEN\n"); break;
  case KW_ELSE: printf("KW_ELSE\n"); break;
  case KW_WHILE: printf("KW_WHILE\n"); break;
  case KW_DO: printf("KW_DO\n"); break;
  case KW_FOR: printf("KW_FOR\n"); break;
  case KW_TO: printf("KW_TO\n"); break;

  case SB_SEMICOLON: printf("SB_SEMICOLON\n"); break;
  case SB_COLON: printf("SB_COLON\n"); break;
  case SB_PERIOD: printf("SB_PERIOD\n"); break;
  case SB_COMMA: printf("SB_COMMA\n"); break;
  case SB_ASSIGN: printf("SB_ASSIGN\n"); break;
  case SB_EQ: printf("SB_EQ\n"); break;
  case SB_NEQ: printf("SB_NEQ\n"); break;
  case SB_LT: printf("SB_LT\n"); break;
  case SB_LE: printf("SB_LE\n"); break;
  case SB_GT: printf("SB_GT\n"); break;
  case SB_GE: printf("SB_GE\n"); break;
  case SB_PLUS: printf("SB_PLUS\n"); break;
  case SB_MINUS: printf("SB_MINUS\n"); break;
  case SB_TIMES: printf("SB_TIMES\n"); break;
  case SB_SLASH: printf("SB_SLASH\n"); break;
  case SB_LPAR: printf("SB_LPAR\n"); break;
  case SB_RPAR: printf("SB_RPAR\n"); break;
  case SB_LSEL: printf("SB_LSEL\n"); break;
  case SB_RSEL: printf("SB_RSEL\n"); break;
  }
}

