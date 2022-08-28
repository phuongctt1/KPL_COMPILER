/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"
//error// thong bao loi
// danh sach cac loi trong qua trinh phan tich tu vung
typedef enum {
  ERR_ENDOFCOMMENT,     // loi chua ket thuc dong ngoac
  ERR_IDENTTOOLONG,     // ten qua dai
  ERR_INVALIDCHARCONSTANT,  // khai bao sai hang ki tu
  ERR_INVALIDSYMBOL,        // bieu tuong khong hop le ???
  ERR_INVALIDCONSTANT,    // sai hang so
  ERR_INVALIDTYPE,        // sai kieu
  ERR_INVALIDBASICTYPE,    // kieu co so khong hop le
  ERR_INVALIDPARAM,       // tham so khong hop le
  ERR_INVALIDSTATEMENT,   // cau lenh khong hop le
  ERR_INVALIDARGUMENTS,   // co qua nhieu loi
  ERR_INVALIDCOMPARATOR, // so sanh khong hop le
  ERR_INVALIDEXPRESSION,  // bieu thuc khong hop le
  ERR_INVALIDTERM,        // TERM ko hop le, TERM theo so do khoi KPL la 1 factor + toan hang * or /
  ERR_INVALIDFACTOR,      // he so khong hop le
  ERR_INVALIDCONSTDECL,    // khai bao hang so khong hop le
  ERR_INVALIDTYPEDECL,    // khai bao kieu khong hop le
  ERR_INVALIDVARDECL,     // khai bao bien khong hop le
  ERR_INVALIDSUBDECL,     // khai bao chuong trinh con khong hop le
} ErrorCode;

// cac thong bao loi
// moi mot loi co mot thong bao tuong ung
#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_INVALIDCONSTANT "Invalid constant!"
#define ERM_INVALIDTYPE "Invalid type!"
#define ERM_INVALIDBASICTYPE "Invalid basic type!"
#define ERM_INVALIDPARAM "Invalid parameter!"
#define ERM_INVALIDSTATEMENT "Invalid statement!"
#define ERM_INVALIDARGUMENTS "Invalid arguments!"
#define ERM_INVALIDCOMPARATOR "Invalid comparator!"
#define ERM_INVALIDEXPRESSION "Invalid expression!"
#define ERM_INVALIDTERM "Invalid term!"
#define ERM_INVALIDFACTOR "Invalid factor!"
#define ERM_INVALIDCONSTDECL "Invalid constant declaration!"
#define ERM_INVALIDTYPEDECL "Invalid type declaration!"
#define ERM_INVALIDVARDECL "Invalid variable declaration!"
#define ERM_INVALIDSUBDECL "Invalid subroutine declaration!"

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif
