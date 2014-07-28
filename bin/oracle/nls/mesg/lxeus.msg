/ 
/ $Header: lxeus.msg@@/main/2 \
/ Checked in on Fri Nov 10 00:39:51 PST 1995 by lveltri \
/ Copyright (c) 1995, 1997 by Oracle Corporation. All Rights Reserved. \
/ $ 
/
/ Copyright (c) 1994, 1995, 1997 by Oracle Corporation
/ 
/   NAME
/     lxeus.msg : Message TaBle
/   FUNCTION
/ 
/   NOTES
/     
/ 	List of  errors
/	
/ 	This file is converted to header/message files using lmsgen.c.
/
/ 	The first col is the NLSRTL (calendar support) error number.
/ 	The second column is reserved and must (for now) be x00000
/ 	The remainder of the line is the error text
/
/   MODIFIED
/    chaowang   04/21/97 -  add an error message when end_date is less than sta
/    lveltri    11/10/95 -  y
/    tlai       09/20/95 -  Remove banner messages
/    tlai       06/11/94 -  Creation 
/    fchen      03/03/94 -  Creation 
/    Scheng     01/28/94 - Creation
/
//  
// General Messages
//

/
110,0, "Working...\n"
// *Cause:
// *Action:
130,0, "Usage: lxegen \tdirectory = <directory path>"
// *Cause:
// *Action:
131,0, "\t\t file = <text file name>"
// *Cause:
// *Action:
140,0, "Cannot build file name"
// *Cause:
// *Action:
//
// messages from tokenizer(lxetok.c)
//
150, 1, "End-of-file in comment in line %d"
// MANUAL: end-of-file in comment
// INDEX:	
// RELEASE: 
// CAUSE: An \/\*....\*\/ style comment was started, but an End-Of-File was
//   encountered before the comment terminator.
// ACTION: Remove comment initiator or add a comment terminator.  The line and
//   column given in the error message refer to the beginning of the last legal
//   token before the comment initiator.
//
151, 1, "End-of-line in quoted identifier in %d"
// MANUAL: end-of-line in quoted identifier
// INDEX:	
// RELEASE: 
// CAUSE: A quoted identifier was started ("), but not completed before the
//   end of the source line.
// ACTION: Remove quote, or properly finish quoted identifier.  The line and
//   column given in the error message refer to the beginning of the quoted
//   identifier.
//
152, 1, "identifier '%s'is too long in line %d column %d"
// MANUAL: identifier is too long
// INDEX:
// RELEASE: 
// CAUSE: The implementation requires identifiers to be at most 30 chars long.
// ACTION:
//
153, 1, "Null strings are not allowed in line %d column %d"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
//
154, 1, "Exponent notation must use an uppercase 'E' in line %d column %d"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
//
//
//
//
// messages from conversion(lxecvt.c)
//
200, 1, "Cannot open calendar external file"
// MANUAL: 
// INDEX:  LXE_CANNOT_OPEN_FILE
// RELEASE: 
// CAUSE: 
// ACTION: 
//
201, 1, "Invalid or duplicated value '%s' in line %d column %d"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
//
202, 1, "Invalid hex value in line %d column %d"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
//
203, 1, "Keyword '%s' mismatched between DEFINE and ENDDEFINE in line %d"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
//
204, 1, "Out of memory"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
//
// 205, 1, "Cannot create loadable binary file"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
206, 1, "Invalid calendar '%s' in line %d, available calendar are:\n"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
207, 0, "          %s"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
208, 1, "Can not write object data into loadable calendar"
// MANUAL: 
// INDEX:	
// RELEASE: 
// CAUSE: 
// ACTION: 
209, 1, "Era's end day is less than start day: '%s' in line %d.\n"
// MANUAL: 
// INDEX:
// RELEASE: 
// CAUSE: 
// ACTION: 
