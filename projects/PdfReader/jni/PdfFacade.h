/*
 * File:    PdfFacade.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   Pdf Facade
 *
 * Copyright (c) 2009 Li XianJing<xianjimli@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-09-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef PDF_FACADE_H
#define PDF_FACADE_H

int   PdfOpen(const char* filename, const char* cache_dir, const char* upwd, const char* opwd);
int   PdfGetPageCount(int docPtr);
char* PdfDecodeText(int docPtr, int pageIndex, int flags);
char* PdfDecodeImage(int docPtr, int pageIndex, int flags);
void  PdfClose(int docPtr);

#endif/*PDF_FACADE_H*/

