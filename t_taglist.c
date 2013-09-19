/*
 * t_tag.c
 *
 * tagutil's tag routines.
 */
#include <string.h>

#include "t_config.h"
#include "t_error.h"
#include "t_tag.h"
#include "t_taglist.h"


struct t_taglist *
t_taglist_new(void)
{
	struct t_taglist *ret;

	ret = malloc(sizeof(struct t_taglist) + sizeof(struct t_tagQ));
	if (ret == NULL)
		return (NULL);

	ret->tags = (struct t_tagQ *)(ret + 1);
	ret->count = 0;
	t_error_init(ret);
	TAILQ_INIT(ret->tags);

	return (ret);
}

struct t_taglist *
t_taglist_clone(const struct t_taglist *tlist)
{
	struct t_taglist *clone;
	struct t_tag *t;

	if (tlist == NULL)
		return (NULL);

	clone = t_taglist_new();
	if (clone == NULL)
		return (NULL);
	TAILQ_FOREACH(t, tlist->tags, entries) {
		if (t_taglist_insert(clone, t->key, t->val) != 0) {
			t_taglist_delete(clone);
			return (NULL);
		}
	}

	return (clone);
}

int
t_taglist_insert(struct t_taglist *tlist, const char *key, const char *val)
{
	struct t_tag *t;

	assert_not_null(tlist);
	assert_not_null(key);
	assert_not_null(val);

	t = t_tag_new(key, val);
	if (t == NULL)
		return (-1);

	TAILQ_INSERT_TAIL(tlist->tags, t, entries);
	tlist->count++;
	return (0);
}


struct t_taglist *
t_taglist_find_all(const struct t_taglist *tlist, const char *key)
{
	struct t_taglist *r;
	const struct t_tag *t;

	assert_not_null(tlist);
	assert_not_null(key);
	if ((r = t_taglist_new()) == NULL)
		goto error;

	TAILQ_FOREACH(t, tlist->tags, entries) {
		if (t_tag_keycmp(t->key, key) == 0) {
			if (t_taglist_insert(r, t->key, t->val) != 0)
				goto error;
		}
	}

	return (r);
	/* NOTREACHED */
error:
	t_taglist_delete(r);
	return (NULL);
}


struct t_tag *
t_taglist_tag_at(const struct t_taglist *tlist, unsigned int index)
{
	struct t_tag *t;

	assert_not_null(tlist);

	t = TAILQ_FIRST(tlist->tags);
	while (t != NULL && index-- > 0)
		t = TAILQ_NEXT(t, entries);

	return (t);
}


char *
t_taglist_join(const struct t_taglist *tlist, const char *glue)
{
	struct sbuf *sb;
	struct t_tag *t, *last;
	char *ret;

	assert_not_null(tlist);
	assert_not_null(glue);

	if (tlist->count == 0)
		return (calloc(1, sizeof(char)));
	sb = sbuf_new_auto();
	if (sb == NULL)
		return (NULL);

	last = TAILQ_LAST(tlist->tags, t_tagQ);
	TAILQ_FOREACH(t, tlist->tags, entries) {
		(void)sbuf_cat(sb, t->val);
		if (t != last)
			(void)sbuf_cat(sb, glue);
	}

	if (sbuf_finish(sb) == -1) {
		sbuf_delete(sb);
		return (NULL);
	}
	ret = strdup(sbuf_data(sb));
	sbuf_delete(sb);

	return (ret);
}


void
t_taglist_delete(struct t_taglist *tlist)
{
	struct t_tag *t1, *t2;

	if (tlist == NULL)
		return;

	t1 = TAILQ_FIRST(tlist->tags);
	while (t1 != NULL) {
		t2 = TAILQ_NEXT(t1, entries);
		free(t1);
		t1 = t2;
	}
	t_error_clear(tlist);
	free(tlist);
}