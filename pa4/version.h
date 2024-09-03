/*
 * This file is used to determine if your version of a file is used or the one
 * in the solution library is used
 *
 * For each of the 4 files you need to complete and turn in for a grade there is
 * compiled working version of that file in the library libpa4.a
 *
 * So libpa4.a contains: csv.o, setorder.o, splitrow.o, wrtrow.o
 *
 * when a line is commented out in the list below the solution version
 * of that file (from libpa4.a) is used in build the executable  file csv.
 *
 * When you want to test your version of a file, uncomment
 * the line that referes to the file you want to test. 
 */
#define MYCSV       // when defined will use your version of csv.c
#define MYSETORDER  // when defined will use your version of setorder.c
#define MYSPLITROW  // when defined will use your version of splitrow.c
#define MYWRTROW    // when defined will use your version of wrtrow.c
