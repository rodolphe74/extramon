#ifndef EXTRAMGR_H
#define EXTRAMGR_H

#define GR_EXTRA 0xEC0C
#define GR_RESETW 01

#define PSETXY 25
#define LINE 26
#define XL 0x61A5	/* fenetre de travail X0*/
#define XR 0x61A9	/* fenetre de travail X1*/
#define YB 0x61A7	/* fenetre de travail Y0*/
#define YT 0x61AB	/* fenetre de travail Y1*/
#define XXXX 0x61A1	/* coords dernier point trace */
#define YYYY 0x61A3	/* coords dernier point trace */

void declare_window(int x0, int y0, int x1, int y1);
void pset(int x, int y);
void line(int x0, int y0, int x1, int y1);

#endif
