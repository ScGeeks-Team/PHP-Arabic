/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2014 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Rui Hirokawa <rui_hirokawa@ybb.ne.jp>                       |
   |          Stig Bakken <ssb@php.net>                                   |
   +----------------------------------------------------------------------+
 */

/* $Id: 1389d7a993601b9fa5475c7761baa6afcb667b0f $ */

#ifndef PHP_ICONV_H
#define PHP_ICONV_H

#ifdef PHP_WIN32
# ifdef PHP_ICONV_EXPORTS
#  define PHP_ICONV_API __declspec(dllexport)
# else
#  define PHP_ICONV_API __declspec(dllimport)
# endif 
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_ICONV_API __attribute__ ((visibility("default")))
#else
# define PHP_ICONV_API
#endif

#ifdef PHP_ATOM_INC
#include "ext/iconv/php_have_iconv.h"
#include "ext/iconv/php_have_libiconv.h"
#include "ext/iconv/php_iconv_aliased_libiconv.h"
#include "ext/iconv/php_have_glibc_iconv.h"
#include "ext/iconv/php_have_bsd_iconv.h"
#include "ext/iconv/php_have_ibm_iconv.h"
#include "ext/iconv/php_iconv_supports_errno.h"
#include "ext/iconv/php_php_iconv_impl.h"
#include "ext/iconv/php_php_iconv_h_path.h"
#endif

#ifdef HAVE_ICONV
extern zend_module_entry iconv_module_entry;
#define iconv_module_ptr &iconv_module_entry

PHP_MINIT_FUNCTION(miconv);
PHP_MSHUTDOWN_FUNCTION(miconv);
PHP_MINFO_FUNCTION(miconv);

PHP_NAMED_FUNCTION(php_if_iconv);
PHP_FUNCTION(ob_iconv_handler);
PHP_FUNCTION(iconv_get_encoding);
PHP_FUNCTION(iconv_set_encoding);
PHP_FUNCTION(iconv_strlen);
PHP_FUNCTION(iconv_substr);
PHP_FUNCTION(iconv_strpos);
PHP_FUNCTION(iconv_strrpos);
PHP_FUNCTION(iconv_mime_encode);
PHP_FUNCTION(iconv_mime_decode);
PHP_FUNCTION(iconv_mime_decode_headers);

ZEND_BEGIN_MODULE_GLOBALS(iconv)
	char *input_encoding;
	char *internal_encoding;
	char *output_encoding;
ZEND_END_MODULE_GLOBALS(iconv)

#ifdef ZTS
# define ICONVG(v) TSRMG(iconv_globals_id, zend_iconv_globals *, v)
#else
# define ICONVG(v) (iconv_globals.v)
#endif

#ifdef HAVE_IBM_ICONV
# define ICONV_ASCII_ENCODING "IBM-850"
# define ICONV_UCS4_ENCODING "UCS-4"
#else
# define ICONV_ASCII_ENCODING "ASCII"
# define ICONV_UCS4_ENCODING "UCS-4LE"
#endif

#ifndef ICONV_CSNMAXLEN
#define ICONV_CSNMAXLEN 64
#endif

/* {{{ typedef enum php_iconv_err_t */
typedef enum _php_iconv_err_t {
	PHP_ICONV_ERR_SUCCESS           = SUCCESS,
	PHP_ICONV_ERR_CONVERTER         = 1,
	PHP_ICONV_ERR_WRONG_CHARSET     = 2,
	PHP_ICONV_ERR_TOO_BIG           = 3,
	PHP_ICONV_ERR_ILLEGAL_SEQ       = 4,
	PHP_ICONV_ERR_ILLEGAL_CHAR      = 5,
	PHP_ICONV_ERR_UNKNOWN           = 6,
	PHP_ICONV_ERR_MALFORMED         = 7,
	PHP_ICONV_ERR_ALLOC             = 8
} php_iconv_err_t;
/* }}} */

PHP_ICONV_API php_iconv_err_t php_iconv_string(const char * in_p, size_t in_len, char **out, size_t *out_len, const char *out_charset, const char *in_charset);

#else

#define iconv_module_ptr NULL

#endif /* HAVE_ICONV */

#define phpext_iconv_ptr iconv_module_ptr

#endif	/* PHP_ICONV_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
