// ***************************************************************************
// Color modes
// ***************************************************************************

//void displayStrip(RgbColor colorCode) {
void displayStrip(uint16_t colorCode) {
  //colorCode = colorGamma.Correct(colorCode);
  //for (int i = 0; i < stackptr; i++) {
    //strip.SetPixelColor(strip_ptr[i], colorCode);
  //}
  //strip.Show();
}

extern void W_LOGO();
extern void timeToStrip(uint8_t hours,uint8_t minutes);
extern time_t prevDisplay;


void Clock(uint16_t wait)
{
  //checkForRequests();
	//if (exit_func) {
	//	exit_func = false;
	//	return;
	//}

  unsigned long nu;
  nu = millis();
  /*if (Rainbow_color == 0)
  {
    //color = RgbColor(main_color.red, main_color.green, main_color.blue);
    displayStrip(color);
  }
  else if ((Rainbow_color != 0) && (nu > prevRainbow + wait))
  {
    prevRainbow = nu;
    //color = RainbowWheel(Rainbow_count&255);
    Rainbow_count += 1;
    if (Rainbow_count > 255) Rainbow_count = 0;
    displayStrip(color);
  }*/
  if (timeStatus() != timeNotSet) {
    /*uint32_t current_color = strip->getColor();
    if(current_color==0)
    {
      uint32_t new_color = strip->color_wheel(strip->get_random_wheel_index(current_color));
      strip->setColor(new_color);
    }*/
    uint16_t currentDisplayTime = now();
    if (currentDisplayTime != prevDisplay) { //update the display only if time has changed
      prevDisplay = currentDisplayTime;
      strip->strip_clear();
      timeToStrip(hour(), minute());
      if (logomode == L_ON)
      {
        W_LOGO();
      }
      if(strip) strip->show();
    }
  }
}



extern unsigned long waitUntilFastTest;
extern int testHours;
extern int testMinutes;
extern const long oneSecondDelay ;

void fastTest() {
  if (millis() >= waitUntilFastTest) {
    strip->strip_clear();
    DBG_OUTPUT_PORT.print("TESTMODE");
    waitUntilFastTest = millis();
    if (testMinutes >= 60) {
      testMinutes = 0;
      testHours++;
    }
    if (testHours >= 24) {
      testHours = 0;
    }

    //Array empty
    //resetAndBlack();
    timeToStrip(testHours, testMinutes);
    if(strip) strip->show();
    testMinutes++;
    waitUntilFastTest += oneSecondDelay;
  }
}
