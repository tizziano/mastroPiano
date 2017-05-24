/*
 * kbd_controller.ino
 * 
 * Copyright 2016 tiziano <tiziano.detogni@gmail.com>
 * 
 * Controller matrice 8x8 della tastiera viscount
 * 
 * Versione 1: arduino UNO R3, banco di prova scansione tastiera
 * 
 * Possibilità:
 *    usa tutti i pin disponbili di arduino
 *      impiega se possibile due porte da 8 bit...
 *        impossibile. PB0..5=6, PD2..7=6, PC0..3=4, totale 18 pin
 *        potresti farlo, ma con un arduino Mega (PortA0-7 e PortC0-7)
 * 
 * siamo abbastanza veloci?
 * sarebbe opportuno usare un'interrupt?
 * 
 * Is a scanning frequency of 1000Hz too low? 
 * I've heard somewhere commercial keyboard use 2000Hz. 
 * Perhaps someone can measure one with a scope?
 * 
 * todo:
 *    elimina i cicli for nel loop
 * 
 *    midinote=12*col+36*row=12*(col+3*row)
 *    ma dovresti incrementare un contatore durante la scansione in modo
 *    da evitare queste moltiplicazioni che rallentano le cose.   ok
 * 
 *    prove antirimbalzo???
 * 
 *    prova a sostituire la seriale con TWI e fai un confronto
 *      devi avere un TWI VCO mozzi su un secondo arduino. ok
 *      todo: quanti VCO mozzi posso connettere sul bus TWI?
 *            come faccio a sapere chi c'è sul bus?
 * 
 *    prova a trasmettere sia sulla seriale che su TWI, 
 *    potresti controllare sia MIDI che Mozzi. ok
 * 
 *    modalità MIDI control sull'ottava bassa 
 *          per inviare comandi all'expander MIDI
 *          per inviare comandi ai VCO
 * 
 *    se riuscissi a mettere il tutto sotto il controllo di GIT...
 * 
 *    todo: 
 *      rilevazione velocità dei tasti? è un altro progetto
 *      merge da raspi-test.ino: interfaccia LCD TWI e analogKeypad
 * 
 *    
 */
#define DEBUGSERIALno
#define TWI
#define KBDOFFSET 36    // offset DO-2
#define TESTBOUNCEno
//~ unsigned long debounceTime;
//~ unsigned long startTime=millis();

#ifdef TWI
  #include <Wire.h>
#endif
 
//uint8_t keyToMidiMap[64];
uint8_t colpins[]={6,7,8,9,10,11,12,13};  // connettore viscount Tx 0..7
uint8_t rowpins[]={2,3,4,5,A0,A1,A2,A3};  // connettore viscount Rx 0..7
 
boolean keyPressed[64];
int noteVelocity = 64;     // se non rilevi la velocità devi usare questo valore prefissato 
 
void noteOn(int cmd, int pitch, int velocity) {

    #ifdef DEBUGSERIAL
      String s="noteon:";
      Serial.println(s+cmd+" "+pitch+" "+velocity);
    #else
      #ifdef TWI
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write(cmd);           // note on/off command (gain 0)
        Wire.write(pitch);         // sends note byte
        Wire.endTransmission();    // stop transmitting
//      #else
        Serial.write(cmd);
        Serial.write(pitch);
        Serial.write(velocity);
      #endif
    #endif
}

/*
 * inizializazione porte A/D sul MU10 via MIDI out
 * serve solo quando vuoi usare il mu10 al posto del respberry
 */
void initM10_AD() {

  // F0 43 1n 4c 08 00 03 20 F7        part 1= Multi part1 = Program number 0x20
  Serial.write(0xf0);
  Serial.write(0x43);
  Serial.write(0x10);
  Serial.write(0x4c);
  Serial.write(0x08);
  Serial.write(0x00);
  Serial.write(0x03);
  Serial.write(0x11);
  Serial.write(0xf7);
  delay(10);

  // F0 43 1n 4c 08 00 0b 10 F7        part 1= Multi part1 = Program number 0x20
  Serial.write(0xf0);
  Serial.write(0x43);
  Serial.write(0x10);
  Serial.write(0x4c);
  Serial.write(0x08);
  Serial.write(0x00);
  Serial.write(0x0b);
  Serial.write(0x50);
  Serial.write(0xf7);
  delay(10);

  // F0 43 1n 4c 10 00 00 01 F7        A/D input gain=line
  Serial.write(0xf0);
  Serial.write(0x43);
  Serial.write(0x10);
  Serial.write(0x4c);
  Serial.write(0x10);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x01);
  Serial.write(0xf7);
  delay(10);

//      un feedback all'avvio
//~   noteOn(0x90, 50, noteVelocity);
//~   delay(100);
//~   noteOn(0x80, 50, noteVelocity);
//~   delay(1000);
}


//
//  per quando avrai voglia di provare l'antirimbalzo sui tasti...
//
#ifdef TESTBOUNCE

void debounce(buttonPin) {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
}
#endif

void scankeyboard() {
  static uint8_t scanrow=0;
  static uint8_t scancol=0;
  static uint8_t midinote=KBDOFFSET;  

  // attiva la colonna (scancol)
  digitalWrite(colpins[scancol], LOW);

  int xrow=digitalRead(rowpins[scanrow]);
  //todo: controllo antirimbalzo!!!
  
  // noteon
  if ( !xrow && !keyPressed[scancol+(scanrow*8)] ) {
    keyPressed[scancol+(scanrow*8)]=true;
    noteOn(0x90, midinote, noteVelocity);
  }
  
  //noteoff
  if ( xrow && keyPressed[scancol+(scanrow*8)] ) {
    keyPressed[scancol+(scanrow*8)]=false;
    noteOn(0x80, midinote, 0);
  }

  digitalWrite(colpins[scancol], HIGH);

  midinote++;
  if (++scanrow==8) {
     scanrow=0;
     if (++scancol==8) {
        scancol=0;
        midinote=KBDOFFSET;   // offset DO-2
      } //else midinote+=8;
  }
}
 
void setup() {

    // azzeramento array keyPressed
    for(int i = 0; i < 64; i++){
      keyPressed[i]=false;
    }

    // configurazione pin in uscita, ingresso e pullup interno 
    for(int i = 0; i < 8; i++){
      pinMode(colpins[i],OUTPUT);
      pinMode(rowpins[i],INPUT_PULLUP);
    };
    
 
    #ifdef DEBUGSERIAL
      // 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
      // 14400 e 28800 non vanno!
      Serial.begin(57600);
      Serial.println("debug keyscan startup");
    #else
      Serial.begin(31250);    // velocità secondo lo standard MIDI
                              // la seriale lavora come MIDI OUT
      // initM10_AD();                 // se è il caso, inizializza il MU10
    #endif
    
    Wire.begin();                // join i2c bus

//  prove TWI VCO mozzi
//~     for (int i=1; i<5; i++) {
//~       Wire.beginTransmission(4); // transmit to device #4
//~       Wire.write(0x07);           // note command 
//~       Wire.write(73+i*2);              // sends one byte
//~       Wire.endTransmission();    // stop transmitting
//~       delay(1000);
//~     }

//~     delay(500);
}

void loop() {
  scankeyboard(); 
//~   delay(500);
 
}
