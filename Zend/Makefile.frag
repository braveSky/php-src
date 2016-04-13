Zend/zend_execute.lo: $(srcdir)/zend_vm_execute.h $(srcdir)/zend_vm_opcodes.h

$(srcdir)/zend_execute.s: $(srcdir)/zend_execute.c
	$(CC) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) -S $(srcdir)/zend_execute.c -o $(srcdir)/zend_execute.s
	sh $(top_srcdir)/build/replace_ret.sh $(srcdir)/zend_execute.s $(ZEND_VM_SIBLING_CALL_OPT) $(AWK)

$(srcdir)/zend_execute.as: $(srcdir)/zend_execute.c
