void print_matrix() {
  byte i = 0;
  int x, y;

  if (abs((long)(millis() - lt_print_matrix)) > (long)to_print_matrix) {
    matrix_buff->dimAll(0);
    matrix_buff->clear();
    matrix->setBrightness8(255);
    matrix_buff->setFont(&LCD7x6);
    matrix_buff->setTextColor(matrix_buff->color565(r[0], g[0], b[0]));

    if (!service_mode) {

      matrix_buff->setCursor(3, 9);  matrix_buff->print("СЕРВИСНЫЙ РЕЖИМ ВЫКЛ");      

      matrix_buff->setCursor(3, 35);  matrix_buff->print("СКОРОСТЬ "); matrix_buff->print(MB_SPEED);
      matrix_buff->setCursor(3, 48);  matrix_buff->print("АДРЕС "); matrix_buff->print(MB_ADDRESS);

      matrix_buff->setTextColor(matrix_buff->color565(r[1],  g[1],  b[1]));  matrix_buff->setCursor(3, 61);  matrix_buff->print("КРАСНЫЙ ");
      matrix_buff->setTextColor(matrix_buff->color565(r[5],  g[5],  b[5]));  matrix_buff->setCursor(49, 61);  matrix_buff->print("ЗЕЛЕНЫЙ");
      matrix_buff->setTextColor(matrix_buff->color565(r[9],  g[9],  b[9]));  matrix_buff->setCursor(95, 61);  matrix_buff->print("СИНИЙ");

    } else {

      matrix_buff->setCursor(3, 9);  matrix_buff->print("СЕРВИСНЫЙ РЕЖИМ ВКЛ");
      matrix_buff->setCursor(3, 22);  matrix_buff->print("ПРОШИВКА ДОСТУПНА");

      matrix_buff->setTextColor(matrix_buff->color565(r[1],  g[1],  b[1]));  matrix_buff->setCursor(3, 61);  matrix_buff->print("КРАСНЫЙ ");
      matrix_buff->setTextColor(matrix_buff->color565(r[5],  g[5],  b[5]));  matrix_buff->setCursor(49, 61);  matrix_buff->print("ЗЕЛЕНЫЙ");
      matrix_buff->setTextColor(matrix_buff->color565(r[9],  g[9],  b[9]));  matrix_buff->setCursor(95, 61);  matrix_buff->print("СИНИЙ");
    }

    matrix_buff->show();

    lt_print_matrix = millis();
  }
}
