// Include the Ruby headers and goodies

//extern "C" {

#include "ruby.h"

char *decode_qr_image(const char *fname);

VALUE QrScanner = Qnil;

void Init_qrscanner();

VALUE method_decode(VALUE self, VALUE fn);

void Init_qrscanner() {
	QrScanner = rb_define_module("QrScanner");
	rb_define_singleton_method(QrScanner, "decode", method_decode, 1);
}

VALUE method_decode(VALUE self, VALUE fn) {
	VALUE ret;
	char *str;
	str = decode_qr_image(StringValuePtr(fn));
	if(!str)
		return Qnil;
		
	ret = rb_str_new2(str);
	free(str);
	return(ret);
}

//}
