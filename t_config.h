#ifndef T_CONFIG_H
#define T_CONFIG_H

#if !defined(__TAGUTIL_VERSION__)
#  define __TAGUTIL_VERSION__ "(unknow version)"
#endif /* not __TAGUTIL_VERSION__ */

#if !defined(__TAGUTIL_AUTHORS__)
#  define __TAGUTIL_AUTHORS__ "(anonymous coward)"
#endif /* not __TAGUTIL_AUTHORS__ */

/*
 * avoid lint to complain for non C89 keywords and macros
 */
#if defined(lint)
#  define inline
#  define restrict
#  define __t__unused
#  define __t__nonnull(x)
#  define __t__dead2
#else
#  define __t__unused     __unused
#  define __t__dead2      __dead2
#  define __t__nonnull(x) __nonnull(x)
#endif /* lint */


#endif /* not T_CONFIG_H */
