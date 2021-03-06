#ifndef T_TUNE_H
#define T_TUNE_H
/*
 * t_tune.h
 *
 * A tune represent a music file with tags (or comments) attributes.
 */
#include <stdlib.h>

#include "t_config.h"
#include "t_toolkit.h"
#include "t_backend.h"
#include "t_taglist.h"


/* abstract music file */
struct t_tune;

/*
 * allocate memory for a new t_tune.
 *
 * @return
 *   a pointer to a fresh t_tune on success, NULL on error (malloc(3) failed).
 */
struct t_tune	*t_tune_new(const char *path);

/*
 * get all the tags of a tune.
 *
 * @return
 *   A complete and ordered t_taglist on success, NULL on error. The caller
 *   should pass the returned t_taglist to t_taglist_delete() after use.
 */
struct t_taglist	*t_tune_tags(struct t_tune *tune);

/*
 * get the tune's path.
 *
 * @return
 *   the path given at tune initialization.
 */
const char	*t_tune_path(struct t_tune *tune);

/*
 * get the tune's backend.
 *
 * @return
 *   the backend used for this tune.
 */
const struct t_backend	*t_tune_backend(struct t_tune *tune);

/*
 * set the tags for a tune.
 *
 * @return
 *   0 on success, -1 on error.
 */
int	t_tune_set_tags(struct t_tune *tune, const struct t_taglist *tlist);

/*
 * Save (write) the file to the storage with its new tags.
 *
 * @return
 *   0 on success, -1 on error.
 */
int	t_tune_save(struct t_tune *tune);

/*
 * clear the t_tune and pass it to free(3). The pointer should not be used
 * afterward.
 */
void	t_tune_delete(struct t_tune *tune);
#endif /* ndef T_TUNE_H */
