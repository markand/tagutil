#ifndef T_FILE_H
#define T_FILE_H
/*
 * t_file.h
 *
 * tagutil Tag File
 *
 * You can rely on the fact that this header include the t_tag.h and t_error.h
 * header.
 */
#include <stdbool.h>

#include "t_config.h"
#include "t_error.h"
#include "t_tag.h"



/* abstract music file, with method members */
struct t_file {
    const char *path;
    const char *lib;
    void *data;

    /*
     * constructor.
     *
     * return NULL if it couldn't create the struct.
     * returned value has to be free()d (use file->destroy(file)).
     */
    struct t_file * (*create)(const char *restrict path);

    /*
     * write the file.
     *
     * return true if no error, false otherwise.
     * On success t_error_msg(file) is NULL, otherwise it contains an error
     * message.
     */
    bool (*save)(struct t_file *restrict file);

    /*
     * free the struct
     */
    void (*destroy)(struct t_file *restrict file);

    /*
     * return a the values of the tag key.
     *
     * If key is NULL, all the tags are returned.
     * If there is no values fo key, ret->tcount is 0.
     *
     * On error, NULL is returned and t_error_msg(file) contains an error
     * message, otherwise t_error_msg(file) is NULL.
     *
     * returned value has to be free()d (use t_taglist_destroy()).
     */
    struct t_taglist * (*get)(struct t_file *restrict file,
            const char *restrict key);

    /*
     * clear the given key tag (all values).
     *
     * if T is NULL, all tags will be cleared.
     *
     * On success true is returned, otherwise false is returned and
     * t_error_msg(file) contains an error message.
     */
    bool (*clear)(struct t_file *restrict file, const struct t_taglist *restrict T);

    /*
     * add the tags of given t_taglist in file.
     *
     * On success true is returned, otherwise false is returned and
     * t_error_msg(file) contains an error message.
     */
    bool (*add)(struct t_file *restrict file, const struct t_taglist *restrict T);


    ERROR_MSG_MEMBER;
};

#endif /* not T_FILE_H */
