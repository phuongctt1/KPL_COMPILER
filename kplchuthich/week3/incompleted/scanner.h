/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __SCANNER_H__
#define __SCANNER_H__

#include "token.h"

Token* getToken(void); // doc vao 1 token tinh tu vi tri hien tai
Token* getValidToken(void); // lay gia tri token
void printToken(Token *token);  // in token

#endif
