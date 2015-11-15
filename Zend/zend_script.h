/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2015 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Dmitry Stogov <dmitry@zend.com>                             |
   +----------------------------------------------------------------------+
*/

/* $Id: $ */

#ifndef ZEND_SCRIPT_H
#define ZEND_SCRIPT_H

typedef struct _zend_script {
	zend_string   *filename;
	zend_op_array  main_op_array;
	HashTable      function_table;
	HashTable      class_table;
	HashTable      constant_table;
	zend_ulong     flags;
} zend_script;

static zend_always_inline zend_script* zend_script_new(zend_string *filename, int type) {
	zend_script *script = emalloc(sizeof(zend_script));	
	script->filename = zend_string_copy(filename);
	script->flags = type;
	init_op_array(op_array, type, INITIAL_OP_ARRAY_SIZE);
	zend_hash_init_ex(&script->function_table, 8, NULL, ZEND_FUNCTION_DTOR, 0, 0);
	zend_hash_init_ex(&script->class_table, 8, NULL, ZEND_CLASS_DTOR, 0, 0);
	zend_hash_init_ex(&script->constant_table, 8, NULL, zval_ptr_dtor_func, 0, 0);
	return script;
}

static zend_always_inline void zend_script_destroy(zend_script *script) {
	zend_string_release(script->filename);
	zend_hash_destroy(&script->function_table);
	zend_hash_destroy(&script->class_table);
	efree_size(script, sizeof(zend_script);
}

#endif /* ZEND_SCRIPT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
