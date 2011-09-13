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
  int dpis[] = {0, 40, 50, 60, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200, 210, 220, 230, 240, 250, 260, 280, 300, 450};
  int blurs[] = {0, 2, 4, 6, 8, 10, 15, 20, 50};
  int num_dpis, num_blurs, dpi, blur;

  num_dpis = sizeof(dpis) / sizeof(*dpis);
  num_blurs = sizeof(blurs) / sizeof(*blurs);
    
  for(blur=0; !str && blur<num_blurs; blur++) {
    for(dpi=0; !str && dpi<num_dpis; dpi++) {
      /*printf("dpi=%d, blur=%d\n", dpis[dpi], blurs[blur]);*/
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
