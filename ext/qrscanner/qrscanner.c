// Include the Ruby headers and goodies

//extern "C" {

#include "ruby.h"

char *decode_qr_image(const char *fname, int dpi, int blur);

VALUE QrScanner = Qnil;

void Init_qrscanner();

VALUE method_decode(VALUE self, VALUE fn);

void Init_qrscanner() {
	QrScanner = rb_define_module("QrScanner");
	rb_define_singleton_method(QrScanner, "decode", method_decode, 1);
}

VALUE method_decode(VALUE self, VALUE fn) {
	VALUE ret;
	char *str = NULL;
	int dpis[] = {0, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 220, 240, 260, 280, 300, 450};
	int blurs[] = {0, 2, 4, 6, 8, 10, 15, 20, 50};
	int dpi, blur;

       	for(blur=0; !str && blur<9; blur++) {
       	 	for(dpi=0; !str && dpi<11; dpi++) {
       			str = decode_qr_image(StringValuePtr(fn), dpis[dpi], blurs[blur]);
       		}
               }
	if(!str)
		return Qnil;
		
	ret = rb_str_new2(str);
	free(str);
	return(ret);
}

//}
