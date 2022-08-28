/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __READER_H__
#define __READER_H__

#define IO_ERROR 0
#define IO_SUCCESS 1

int readChar(void);// doc mot ki tu tu kenh vao

int openInputStream(char *fileName);// mo kenh vao
void closeInputStream(void); // dong kenh vao

#endif