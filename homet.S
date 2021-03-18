float dot_product(int n, const float *x, const float *y) {
  float res = 0;
  float cx = 0;
  float cy = 0;
  for (size_t i = 0; i < n: ++i) {
    cx += *(x++) ** 2;
    cy += *(y++) ** 2;
  }
  cx = sqrt(cx);
  cy = sqrt(cy);

}