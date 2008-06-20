#ifndef T_TAGUTIL_H
#define T_TAGUTIL_H


#include <stdio.h>

#include <taglib/tag_c.h>

#include "config.h"


/*
 * you should not modifiy them, eval_tag() implementation might be depend.
 */
#define kTITLE      "%t"
#define kALBUM      "%a"
#define kARTIST     "%A"
#define kYEAR       "%y"
#define kTRACK      "%T"
#define kCOMMENT    "%c"
#define kGENRE      "%g"


/*
 * tagutil_f is the type of function that implement actions in tagutil.
 * 1rst arg: the current file's name
 * 2nd  arg: the TagLib_File of the current file
 * 3rd  arg: the arg supplied to the action (for example, if -y is given as
 * option then action is tagutil_year and arg is the new value for the
 * year tag.
 */
typedef bool (*tagutil_f)(const char *__restrict__, TagLib_File *__restrict__, const char *__restrict__);

/**********************************************************************/


/*
 * show usage and exit.
 */
void usage(void) __attribute__ ((__noreturn__));


/*
 * parse argv to find the tagutil_f to use and apply_arg is a pointer to its argument.
 * first_fname is updated to the index of the first file name in argv.
 */
tagutil_f parse_argv(int argc, char *argv[], int *first_fname, char **apply_arg)
    __attribute__ ((__nonnull__ (2, 3, 4)));


/* FILE FUNCTIONS */

/*
 * rename path to new_path. err(3) if new_path already exist.
 */
void safe_rename(const char *__restrict__ oldpath, const char *__restrict__ newpath)
    __attribute__ ((__nonnull__ (1, 2)));


/*
 * create a temporary file in $TMPDIR. if $TMPDIR is not set, /tmp is
 * used. return the full path to the temp file created.
 *
 * returned value has to be freed.
 */
char* create_tmpfile(void);


/* TAG FUNCTIONS */

/*
 * return a char* that contains all tag infos.
 *
 * returned value has to be freed.
 */
char* printable_tag(const TagLib_Tag *__restrict__ tag)
    __attribute__ ((__nonnull__ (1)));


/*
 * call "$EDITOR path" (the environment variable $EDITOR must be set).
 */
bool user_edit(const char *__restrict__ path)
    __attribute__ ((__nonnull__ (1)));


/*
 * read fp and tag. the format of the text should bethe same as tagutil_print.
 */
void update_tag(TagLib_Tag *__restrict__ tag, FILE *__restrict__ fp)
    __attribute__ ((__nonnull__(1, 2)));


/*
 * replace each tagutil keywords by their value. see k* keywords.
 */
char* eval_tag(const char *__restrict__ pattern, const TagLib_Tag *__restrict__ tag)
    __attribute__ ((__nonnull__(1, 2)));

/* TAGUTIL FUNCTIONS */

/*
 * print the given file's tag to stdin.
 */
bool tagutil_print(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2)));


/*
 * print the given file's tag and prompt to ask if tag edit is needed. if
 * answer is yes create a tempfile, fill is with infos, run $EDITOR, then
 * parse the tempfile and update the file's tag.
 */
bool tagutil_edit(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2)));


/*
 * rename the file at path with the given pattern arg. the pattern can use
 * some keywords for tags (see usage()).
 */
bool tagutil_rename(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));

/* functions below are generated by the _MAKE_TAGUTIL_FUNC macro. */
bool tagutil_title(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));
bool tagutil_album(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));
bool tagutil_artist(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));
bool tagutil_year(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));
bool tagutil_track(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));
bool tagutil_comment(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));
bool tagutil_genre(const char *__restrict__ path, TagLib_File *__restrict__ f, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));


#endif /* !T_TAGUTIL_H */
